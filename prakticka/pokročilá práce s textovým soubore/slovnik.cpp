#include "slovnik.h"


/*
void vypis(char cesta[10]){
	FILE *f;
	int counter=0;
	char radek[100];
	
	f=fopen(cesta, "r");
	
	if(f==NULL){
		printf("System nemuze otevrit soubor\n\n");
		system("pause");
		return;
	}
	
	while(fgets(radek, 100, f)!=NULL){
			
	}
	 
}

void addWord(char cesta[10]){
	FILE *f;
	char cesky[30], angl[30], cislo[5];
	int cis;
	
	do{
		system("cls");
		fflush(stdin);
		printf("Pro ukonceni napis 000\n");
		printf("Zadejte slovicko cesky\n");
		gets(cesky);
		if(1)break;//pripravena podminka pro overeni duplikatu
		printf("Toto slovicko uz ve slovniku je\n");
		system("pause");
	}while(1);

	do{
		system("cls");
		fflush(stdin);
		printf("Pro ukonceni napis 000\n");
		printf("Zadejte slovicko anglicky\n");
		gets(angl);
		if(1)break;//pripravena podminka pro overeni duplikatu
		printf("Toto slovicko uz ve slovniku je\n");
		system("pause");
	}while(1);
	if(strcmp(angl, "000")==0)return;
	
	printf("Zaadejte cislo lekce\n");
	
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
	fprintf(f, "\n");
	puts(cesky);
	fclose(f);
	
}
*/
