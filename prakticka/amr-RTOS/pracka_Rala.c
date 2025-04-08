/**
 * @file   pracka_Rala.c
 * @author Vojtěch Lisztwan
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/button.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/chrono.h"
#include "string.h"
#include "stdio.h"
//Nastavení mapy pro přiřazení znaků pro jednotlivé tlačítka
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
};

//výběr pinů pro interní led
enum pin interni[]={
	LED_IN_0,
	LED_IN_1,
	LED_IN_2,
	LED_IN_3
};

//výběr pinů pro externí led
enum pin externi[]={
	LED_EX_3,
	LED_EX_2,
	LED_EX_1,
	LED_EX_0
};

//deklarace úloh
OS_TID id_task,id_task1,id_task2;

//deklarace globálních proměnných
int odStartu=0;
int doKonceCyklu=0;
int doKonceFaze=0;
int faze = 5;
int locked =0;
int opened=0;

//definici datového typu Tcyklus
typedef struct{
	int casCelkem;
	int namaceni;
	int prani;
	int oplachnuti;
	int suseni;
	char nazev[20];
}Tcyklus;


//Deklarace a inicializace programů pro praní, realizováno jako pole cyklů
Tcyklus cykly[] = {
    {120,0,0,0,0, "Kratky"},
    {300,0,0,0,0, "Dlouhy"},
    {60,0,0,0,0, "Test"}
};

//funkce pro jednodužší zapínání led
//použití Inverzní logiky pro externí led, jsou zapojeny s PULL_UP rezistorem
void led_set(pin_t pin, int value){
	//proměnná pro inverzní logiku
	int on = 1;
	if(io_port(pin)==io_port(LED_EX_0))on =0;
	io_set(pin, on ? value : !value);
}

//funkce pro výběr programu pro praní, vrátí index z pole cykly
int vyber(){
	int position=0;
	int prev=2;
	uint8_t znak;
	char buff[21];
	LCD_set(LCD_CLR);

	//smyčka, díky které se uživatel může pohybovat v menu
	//pro pohyb použita klávesnice a znaky '*' a '#'
	do{
		if(prev!=position){
			LCD_set(LCD_CLR);
			LCD_set(LCD_LINE1);
			sprintf(buff, "%s",cykly[position].nazev);
			LCD_print(buff);
			LCD_set(LCD_LINE2);
			sprintf(buff, "%02d:%02d",(cykly[position].casCelkem/60),cykly[position].casCelkem%60);
			LCD_print(buff);
			prev = position;
		}
		znak = KBD_read();
		if(znak=='#')position++;
		if(znak=='*')position=position - 1;
		if(position < 0)position = /*((sizeof(cykly)/sizeof(cykly[0]))-1)*/ 2;
		if(position>=sizeof(cykly)/sizeof(cykly[0])) position=0;
		
		delay_ms(100);
	}while(znak!='0');
	return position;
}


//Úloha, která zajišťuje výběr programu pro praní a přechod mezi fázemi programu
//zapíná a vypíná kontrolní ledky
__task void Task() {
	for (;;) {
		int index = vyber();
		int end;
		int konecFaze;
		char buff[20];
		char action[20];
		
		//kontrola, jetli není pračka otevřená před spuštěním praní
		if(opened){
			//kontrola zavřené pračky před spuštěním praní
			LCD_set(LCD_CLR);
			LCD_set(LCD_LINE1);
			LCD_print("Zavrete pracku");
			while(opened){;}//nekonečná smyčka čekající na zavření pračky
		}

		end = odStartu+cykly[index].casCelkem;//výpočet konce programu
		locked =1; //uzamčení pračky
		led_set(interni[3], 1); // zapnutí led diody signalizující praní

		//smyčka pro fáze programu
		for(faze = 1;faze<5;faze++){
			
			switch(faze){
				case 1:
					konecFaze = odStartu+cykly[index].namaceni;
					sprintf(action, "namaceni");
					break;
				case 2:
					konecFaze = odStartu+cykly[index].prani;
					sprintf(action, "prani");
					break;
				case 3:
					konecFaze = odStartu+cykly[index].oplachnuti;
					sprintf(action, "oplachnuti");
					break;
				case 4:
					konecFaze = odStartu+cykly[index].suseni;
					sprintf(action, "suseni");
					break;
				default:
					break;
			}
			LCD_set(LCD_CLR);
			do{
				LCD_set(LCD_LINE1);
				sprintf(buff, "%02d:%02d %s", (end-odStartu)/60,(end-odStartu)%60, cykly[index].nazev);
				LCD_print(buff);
				LCD_set(LCD_LINE2);
				sprintf(buff, "%02d:%02d %s", (konecFaze-odStartu)/60,(konecFaze-odStartu)%60, action);
				LCD_print(buff);
				delay_ms(80);
			}while(konecFaze>odStartu);//aktualizace výpisů časů na LCD.
		}
		//vynulování časů-konec programu praní
		odStartu=0;
		doKonceCyklu=0;
		doKonceFaze=0;
		led_set(interni[3], 0); //zhasnutí signalizace praní
		//výpis na LCD
		LCD_set(LCD_CLR);
		LCD_set(LCD_LINE1);
		sprintf(buff, "%s KONEC",cykly[index].nazev);
		LCD_print(buff);
		
		delay_ms(1000);
		locked=0; //odemčení pračky
		
	}
}

__task void Timer() {
	for (;;) {
			delay_ms(1000); //čekání 1 vteřiny
			odStartu++; //inkrementace čítače vteřin
		
		//nulování čítačů, kdybychom nenulovali, po nějaké době by mohly přetéct
		if(odStartu>500000&&doKonceCyklu==0){
			odStartu=0;
			doKonceCyklu=0;
			doKonceFaze=0;
		}
		//signalizace zamknutí pračky a čekání v nekočné smyčce, doku ji znovu nepustíme
		if(io_read((USER_BUTTON)==1)&&(locked ==1)){
			led_set(interni[1], 1);
			led_set(interni[3], 0);
			delay_ms(1000);
			while(1){
				if(io_read(USER_BUTTON)==1){
					led_set(interni[1], 0);
					led_set(interni[3], 1);
					break;
				}
			}
		}
		
	}
}

//úloha pro správu LED diod
__task void Leds() {
	for (;;) {
		for(int i=0;i<4;i++){
			io_set(externi[i],((faze-1)==i)? 0:1);//signalizace aktuální fáze praní
		}
		io_set(interni[2], locked); //signalizace zamknuté pračky led diodou(červená)
		
		
		uint8_t znak;
		//čtení klávesnice, jestli není zmáčknuto D pro otevření pračky
		znak=KBD_read();
		if(znak=='D'&&!locked){
			opened = !opened;
			delay_ms(100);
		}
		io_set(interni[0], opened); //signalizace zelenou diodou otevření pračky
		
	}
}



//inicializace úloh, nastavení periferií a jejich knihoven
//po proběhnutí úlohy se úloha sama smaže
__task void setup() {
	LCD_setup();
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LED_setup();
	BTN_setup();
	KBD_setup();
	for(int i=0;i<(sizeof(cykly)/sizeof(cykly[0]));i++){
		cykly[i].prani=(int)((double)cykly[i].casCelkem*0.6);
		cykly[i].oplachnuti=(int)((double)cykly[i].casCelkem*0.2);
		cykly[i].suseni=(int)((double)cykly[i].casCelkem*0.15);
		cykly[i].namaceni=cykly[i].casCelkem-cykly[i].oplachnuti-cykly[i].suseni-cykly[i].prani;
	}
	
	id_task = os_tsk_create(Task, 0);
	id_task1 = os_tsk_create(Timer, 0);
	id_task2 = os_tsk_create(Leds, 0);
	os_tsk_delete_self();
}


//hlavní program, který spustí úlohu setup, zbytek se odehrává v jednotlivý úlohách
int main () {
	os_sys_init(setup);
	
}