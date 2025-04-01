/**
 * @file   luxmetr.c
 * @author Vojtech Lisztwan
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/button.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/adc.h"
#include "stm32_kit/led.h"
#include "stm32_kit/chrono.h"
#include <stdio.h>
#include <math.h>

static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
};
enum pin interni[]={
	LED_IN_0,
	LED_IN_1,
	LED_IN_2,
	LED_IN_3
};

enum pin externi[]={
	LED_EX_3,
	LED_EX_2,
	LED_EX_1,
	LED_EX_0
};

void led_set(pin_t pin, int value){
	int on = 1;
	if(io_port(pin)==io_port(LED_EX_0))on =0;
	io_set(pin, on ? value : !value);
}


BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000); 
	LCD_setup();
	KBD_setup();
	ADC_setup();
	BTN_setup();
	LED_setup();
};



int main(void) {
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	uint16_t value;
	double mili;
	double sum;
	double luxes;
	double candela;
	char buff[20];
	int jednotka;
	int zdroj;
	uint8_t znak;
	char jedn[20];
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	LCD_print("1-LUX");
	LCD_set(LCD_LINE2);
	LCD_print("2-Candel");
	
	do{
		znak = KBD_read();
		if(znak=='1'){
			jednotka = 0;
			break;
		}
		if(znak=='2'){
			jednotka = 1;
			break;
		}
	}while(1);
	
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	LCD_print("1 zarovka");
	LCD_set(LCD_LINE2);
	LCD_print("2-slunce");
	do{
		znak = KBD_read();
		if(znak=='1'){
			zdroj = 0;
			break;
		}
		if(znak=='2'){
			zdroj = 1;
			break;
		}
	}while(1);
	
	while (1) {
		
		
		sum=0;
		for(int i = 0;i<128;i++){
			value = ADC_read();
			sum+=value;
			delay_ms(1);
		}
		
		mili = ((sum/128)*3000)/4096;
		luxes = 12.8*exp(0.0025*mili);
		luxes *= zdroj? 0.95:1.05;
		candela =luxes* 0.009290304;
		
		sprintf(buff, "%4.0f mV", mili);
		LCD_set(LCD_LINE1);
		LCD_print(buff);
		
		if(jednotka){
			sprintf(jedn, "Can");
		}else{
			sprintf(jedn, "Lux");
		}
		
		sprintf(buff, "%4.0f %s", jednotka? candela:luxes, jedn);
		LCD_set(LCD_LINE2);
		LCD_print(buff);
		delay_ms(200);
		if(luxes>400){
			for(int i=0;i<4; i++){
				led_set(interni[i],1);
				led_set(externi[i],1);
			}
			}else{
				for(int i=0;i<4; i++){
					led_set(interni[i],0);
					led_set(externi[i],0);
				}
			}
		}
	
}

