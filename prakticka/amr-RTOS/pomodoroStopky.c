/**
 * @file   pomodoroStopky.c
 * @author <Vojtech Lisztwan>
 * 
 * Tento soubor implementuje Pomodoro timer pomoci mikrokontroleru STM32.
 * Obsahuje funkce pro pracovni intervaly, kratke a dlouhe prestavky, 
 * pocitani ukolu a interakci s uzivatelem pomoci tlacitek a LCD displeje.
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "string.h"
#include "stdio.h"
#include "stm32_kit/button.h"
#include <rtl.h>
#include <stdbool.h>
#include "stm32_kit/uart.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/led.h"
#include "stm32_kit/pin.h"

// Definice konstant pro casovani Pomodoro
#define WORK 120       // Pracovni interval v sekundach
#define PAUSE 30       // Kratka prestavka v sekundach
#define LONGPAUSE 50   // Dlouha prestavka v sekundach

// Mapovani klavesnice pro vstup od uzivatele
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
};

// Definice pinu pro LED diody
enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3,
    P_INVALID
};

// Funkce pro nastaveni stavu jedne LED diody
void led_set(pin_t pin, int value) {
    int on = 1;
    if (io_port(pin) == io_port(LED_EX_0)) {
        on = 0; // Reverze logiky pro externi LED
    }
    io_set(pin, on ? value : !value);
}

// Funkce pro nastaveni stavu vsech LED v poli
void led_set_all(enum pin leds[], int value) {
    for (int i = 0; leds[i] != P_INVALID; i++) {
        led_set(leds[i], value);
    }
}

// Funkce pro prepinani stavu LED diody
void opak(pin_t ledka) {
    led_set(ledka, !io_get(ledka));
}

// ID jednotlivych uzlu ukolu
OS_TID id_task1, id_task2, id_task3, id_task4, id_task5, id_task6;

// Semaphore pro pristup k LCD
OS_SEM semaphore1;

// Promenne pro sledovani stavu Pomodoro cyklu a ukolu
int counterCtveric = 1; // Pocet dokonceni Pomodoro cyklu
int counterPrace = 1;  // Pocet dokonceni pracovnich intervalu v ramci cyklu
int cyklus = 1;        // Typ aktualniho cyklu (1: prace, 2: kratka prestavka, 3: dlouha prestavka)
int sec = 0;           // Globalni casove pocitadlo v sekundach
int prev = 1;          // Predchozi typ cyklu
char stav[10];         // Popis stavu
int sekundy_start, minuty = 0; // Startovaci cas a zbyvajici minuty
int sekundy_end = WORK;        // Konecny cas aktualniho intervalu
int sekundy_do_konce;          // Zbyvajici sekundy do konce intervalu
char buff[17];                 // Buffer pro zobrazeni na LCD
char type[10] = "prace";       // Typ aktualniho cyklu
int ukoly[4] = {0, 0, 0, 0};   // Pole pro ulozeni poctu ukolu

// Funkce pro vypocet zbyvajiciho casu a formatovani textu
void vypocet() {
    sekundy_do_konce = sekundy_end - sec;
    minuty = (sekundy_do_konce - (sekundy_do_konce % 60)) / 60;
    sekundy_do_konce = sekundy_do_konce % 60;
    snprintf(buff, 17, "%d %02d:%02d ", counterPrace, minuty, sekundy_do_konce);
}

/**
 * Ukol pro spravu pracovniho intervalu a prestavek.
 */
__task void job1() {
    for (;;) {
        if (prev != cyklus) { // Kontrola zmeny cyklu
            if (cyklus == 1) counterPrace++; // Zvyseni poctu pracovnich intervalu
            if (counterPrace > 4) { // Reset po dokonceni cyklu
                for (int i = 0; i < 4; i++) {
                    ukoly[i] = 0;
                }
                counterPrace = 1;
            }
            prev = cyklus;
            sekundy_start = sec;
            minuty = 0;

            // Vycisteni LCD pro novy cyklus
            os_sem_wait(semaphore1, 0xffff);
            LCD_set(LCD_CLR);
            os_sem_send(semaphore1);

            // Nastaveni delky intervalu a typu cyklu
            switch (cyklus) {
                case 1:
                    sekundy_end = sec + WORK;
                    strcpy(type, " prace");
                    break;
                case 2:
                    sekundy_end = sec + PAUSE;
                    strcpy(type, " pause");
                    break;
                case 3:
                    sekundy_end = sec + LONGPAUSE;
                    strcpy(type, " big pause");
                    break;
            }

            // Aktualizace LED indikatoru
            led_set_all(ledky, 0);
            led_set(ledky[cyklus - 1], 1);
        }

        delay_ms(300);
        vypocet(); // Vypocet zbyvajiciho casu
        strcat(buff, type);

        // Zobrazeni zbyvajiciho casu a typu cyklu na LCD
        os_sem_wait(&semaphore1, 0xffff);
        LCD_set(LCD_LINE1);
        LCD_print(buff);
        LCD_set(LCD_LINE2);
        os_sem_send(&semaphore1);

        // Prechod na dalsi cyklus po skonceni intervalu
        if (sekundy_end < sec) {
            if (cyklus == 1) {
                if (counterPrace == 4) cyklus = 3;
                else cyklus = 2;
            } else {
                cyklus = 1;
            }
        }
    }
}

/**
 * Ukol pro zpracovani vstupu od uzivatele pomoci klavesnice.
 */
__task void job2() {
    for (;;) {
        uint16_t znak;
        char text[8];
        znak = KBD_read();
        if (znak) {
            if (znak >= '0' && znak <= '9') {
                ukoly[counterPrace - 1] = ukoly[counterPrace - 1] * 10 + (znak - '0');
            }
        }
        os_sem_wait(semaphore1, 0xffff);
        snprintf(text, 8, " %d ", ukoly[counterPrace - 1]);
        LCD_set(LCD_LINE2);
        LCD_print("pocet ukolu:");
        LCD_print(text);
        os_sem_send(semaphore1);
        delay_ms(30);
    }
}

/**
 * Ukol pro odeslani shrnutych dat na UART kanal.
 */
__task void job3() {
    for (;;) {
        int sum = 0;
        char text[50];
        if (counterPrace == 4 && cyklus == 3) {
            for (int i = 0; i < 4; i++) {
                sum += ukoly[i];
            }
            snprintf(text, 50, "%d: %d 1-%d;2-%d;3-%d;4-%d\n\r", counterCtveric, sum, ukoly[0], ukoly[1], ukoly[2], ukoly[3]);
            os_sem_wait(semaphore1, 0xffff);
            UART_write(text, 50);
            os_sem_send(semaphore1);
            counterCtveric++;
            while (cyklus == 3) {
                // Cekani na zmenu cyklu
            }
        }
    }
}

/**
 * Ukol pro inkrementaci globalniho casoveho pocitadla.
 */
__task void job4() {
    for (;;) {
        sec++;
        delay_ms(800);
    }
}

/**
 * Ukol pro ovladani tlacitka uzivatele pro reset timeru.
 */
__task void job5() {
    for (;;) {
        if (io_read(USER_BUTTON)) {
            os_sem_wait(&semaphore1, 0xffff);
            sec = 0;
            cyklus = 1;
            counterPrace = 0;
            prev = 0;
            for (int i = 0; i < 4; i++) {
                ukoly[i] = 0;
            }
            counterCtveric = 1;
            led_set_all(ledky, 1);
            delay_ms(250);
            led_set_all(ledky, 0);
            delay_ms(250);
            os_sem_send(&semaphore1);
        }
    }
}

/**
 * Ukol pro zpracovani specialniho vstupu z klavesnice pro manualni zmenu cyklu.
 */
__task void job6() {
    for (;;) {
        uint8_t znak = KBD_read();
        if (znak == '*') {
            if (cyklus == 1) {
                if (counterPrace == 4) cyklus = 3;
                else cyklus = 2;
            } else {
                cyklus = 1;
            }
        }
        delay_ms(200);
    }
}

/**
 * Inicializacni ukol pro nastaveni periferii a vytvoreni ostatnich ukolu.
 */
__task void setup() {
    LCD_setup();
    BTN_setup();
    UART_setup();
    KBD_setup();
    LED_setup();

    for (int i = 0; i < 4; i++) {
        ukoly[i] = 0;
    }

    os_sem_init(&semaphore1, 0);
    os_sem_send(&semaphore1);

    LCD_set(LCD_CUR_NO_BLINK);
    LCD_set(LCD_CUR_OFF);

    id_task1 = os_tsk_create(job1, 0);
    id_task2 = os_tsk_create(job2, 0);
    id_task3 = os_tsk_create(job3, 0);
    id_task4 = os_tsk_create(job4, 0);
    id_task5 = os_tsk_create(job5, 0);
    id_task6 = os_tsk_create(job6, 0);
    os_tsk_delete_self();
}

/**
 * Hlavni funkce pro spusteni RTOS a inicializacniho ukolu.
 */
int main() {
    os_sys_init(setup);
}