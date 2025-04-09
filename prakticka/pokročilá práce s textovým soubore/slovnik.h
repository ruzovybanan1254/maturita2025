#ifndef SLOVNIK_H
#define SLOVNIK_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


void preklad(char cesta[10]){
	int volba;
	FILE *f;
	char cesky[30], angl[30];
	char *cesky_ov, *angl_ov, *cis;
	int cisilko;
	char radek[100];
	while(1){
		while(1){
			printf("Zvolte moznost\n");
			printf("0\tZpet\n");
			printf("1\tCJ->AJ\n");
			printf("2\tAJ->CJ\n");
			scanf("%d", &volba);
			if(volba==0)return;
			if(volba==1||volba==2)break;
			system("pause"); 
			system("cls");
		}
		if(volba==1){
			system("cls");
			fflush(stdin);
			printf("Zadejte slovicko cesky\n");
			gets(cesky);
		}
		if(volba==2){
			system("cls");
			fflush(stdin);
			printf("Zadejte slovicko anglicky\n");
			gets(angl);
		}
		
		f=fopen(cesta, "r");
		if(f==NULL){
			printf("System nemuze otevrit soubor\n\n");
			system("pause");
			return;
		}
		while(fgets(radek, 100, f)!=NULL){
			cesky_ov=strtok(radek, ";");
			angl_ov=strtok(NULL, ";");
			cis = strtok(NULL, ";");
			cisilko = atoi(cis);
			if((strcmp(cesky, cesky_ov)==0)||(strcmp(angl, angl_ov)==0)){
				switch (volba) {
				case 1:
					printf("Cesky: %s \tAnglicky: %s\tCislo lekce: %d\n", cesky_ov, angl_ov, cisilko);
					break;
				case 2:
					printf("Anglicky: %s \tCesky: %s\tCislo lekce: %d\n", angl_ov, cesky_ov, cisilko);
					break;
				default:
					//TODO
					break;
				}
				break;
			}
		}
		fclose(f);
		system("pause");
		system("cls");
	}
}


void vypis(char cesta[10]){
	FILE *f;
	char radek[100];
	
	f=fopen(cesta, "r");
	
	if(f==NULL){
		printf("System nemuze otevrit soubor\n\n");
		system("pause");
		return;
	}
	
	while(fgets(radek, 100, f)!=NULL){
		printf("%s", radek);
	}
	fclose(f);
}



int check(char cesta[10], char word[30]){
	FILE *f;
	
	char *cesky_ov, *angl_ov;
	char radek[100];
	strlwr(word);
	f=fopen(cesta, "r");
	if(f==NULL){
		printf("System nemuze otevrit soubor\n\n");
		system("pause");
		return 1;
	}
	while(fgets(radek, 100, f)!=NULL){
		cesky_ov=strtok(radek, ";");
		angl_ov=strtok(NULL, ";");
		if((strcmp(word, cesky_ov)==0)||(strcmp(word, angl_ov)==0)){
			fclose(f);
			return 0;
		}
	}
	return 1;
}



void addWord(char cesta[10]){
	FILE *f;
	char cesky[30]="", angl[30]="", cislo[5];
	int cis;
	
	do{
		system("cls");
		fflush(stdin);
		printf("Pro ukonceni napis 000\n");
		printf("Zadejte slovicko cesky\n");
		gets(cesky);
		if(check(cesta, cesky))break;
		printf("Toto slovicko uz ve slovniku je\n");
		system("pause");
	}while(1);
	if(strcmp(cesky, "000")==0)return;
	
	do{
		system("cls");
		fflush(stdin);
		printf("Pro ukonceni napis 000\n");
		printf("Zadejte slovicko anglicky\n");
		gets(angl);
		if(check(cesta,  angl))break;
		printf("Toto slovicko uz ve slovniku je\n");
		system("pause");
	}while(1);
	if(strcmp(angl, "000")==0)return;
	
	
	
	
	printf("Zadejte cislo lekce\n");
	
	while(1){
		fflush(stdin);
		if(scanf("%d", &cis)==1)break;
		system("cls");
		printf("Zadejte cislo lekce");
	}
	f = fopen(cesta, "a");
	if(f==NULL){
		printf("System nemuze otevrit soubor\n\n");
		system("pause");
		return;
	}
	sprintf(cislo, "%d", cis);
	strlwr(angl);
	strlwr(cesky);
	strcat(cesky,";");
	strcat(cesky, angl);
	strcat(cesky,";");
	strcat(cesky, cislo);
	strcat(cesky,";");
	fputs(cesky, f);
	fprintf(f, "\n");
	fclose(f);
}


void zkouseniLekce(char cesta[10]){
	int cLekce;
	FILE *f;
	int counter=0, good=0;
	char angl[30]="";
	float result;
	
	char *cesky_ov, *angl_ov, *cis;
	char radek[100];
	int cisilko;
	do{
		printf("Zadejte cislo lekce\n");	
	}while(scanf("%d", &cLekce)!=1);
	
	
	f=fopen(cesta, "r");
	if(f==NULL){
		printf("System nemuze otevrit soubor\n\n");
		system("pause");
		return;
	}
	
	while(fgets(radek, 100, f)!=NULL){
		
		cesky_ov=strtok(radek, ";");
		angl_ov=strtok(NULL, ";");
		cis = strtok(NULL, ";");
		cisilko = atoi(cis);
		if(cisilko==cLekce){
			counter ++;
			printf("Zadejte preklad slova %s:\t", cesky_ov);
			fflush(stdin);
			gets(angl);
			strlwr(angl);
			if(strcmp(angl, angl_ov)==0){
				good ++;
				printf("\nGREAT ANSWER\n");
			}else{
				printf("\nNeed to lear more\n");
			}
			system("pause");
			system("cls");
		}
		
	}
	
	system("cls");
	result = (float)good/(float)counter;
	result*=100;
	printf("Mel jsi dobre %d z %d slovicek, to je %.1f procent\n\n\n", good, counter, result);
	
	
	
	system("pause");
	system("cls");
	
	
}


#endif
