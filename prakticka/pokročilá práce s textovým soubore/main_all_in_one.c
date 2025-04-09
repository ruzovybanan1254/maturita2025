//
//  main.c
//  slovnik
//
//  Created by kuba on 21.04.2021.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

void menu(void);
int pocet(void);
void novy(void);
void vypis(void);
char male(char slovo[]);
void preklad(void);
void zkouseni(void);
void nah_zkouseni(int pocet);

int main() {
    int vyber=1,count;
    do{
        count=pocet();
        menu();
        scanf("%d",&vyber);
        switch (vyber) {
            case 1: novy();
                break;
            case 2: vypis();
                break;
            case 3: preklad();
                break;
            case 4: zkouseni();
                break;
            case 5: nah_zkouseni(count);
                break;
                
            default: break;
        }
    }while(vyber!=0);
    return 0;
}

void nah_zkouseni(int pocet){
    FILE *f;
    char tok[50],*token,cz[20],en[20],odp[20];
    int lek,zkous,pole[30],spravne=0,i,k=1;
    do{
        printf("Zadej pocet slovicek z kterych chces byt zkouseny:");
        scanf("%d",&zkous);
        if(zkous>pocet || zkous<=0) printf("Ale notak xdd");
    }while(zkous>pocet || zkous<=0);
    srand( (unsigned) time(NULL));
    for(i=0;i<zkous;i++){
        pole[i]=1+rand()%pocet;
        //while(pole[i]==0) pole[i]=rand()%pocet;
        for(int j=0;j<i;j++) while(pole[j]==pole[i]) pole[i]=rand()%pocet;
    }
    for(i=0;i<zkous;i++){
        f=fopen("slovnik.txt","r");
        k=0;
            while(fgets(tok, 40, f)){
            token=strtok(tok,"|");
            strcpy(cz, token);
            token=strtok(NULL,"|");
            strcpy(en, token);
            token=strtok(NULL,"|");
            lek=atoi(token);
            if(k==pole[i]){
                printf("\nCesky:%s  Anglicky:",cz);
                fflush(stdin);
                gets(odp);
                male(odp);
                if(!strcmp(odp,en)){
                    printf("\n\tSpravne\n");
                    spravne++;
                }
                else printf("\n\tSpatne\n");
            }
            k++;
        }
        fclose(f);
    }
    if(zkous!=0) printf("Z %d slovicek mas %d spravne, to znamena %.0f%% uspesnost",zkous,spravne,((float)spravne/zkous)*100);
    else printf("V teto lekci nejsou zadna slovicka");
    
}

void zkouseni(void){
    FILE *f;
    char tok[50],*token,cz[20],en[20],odp[20];
    int lek,i=0,zkous,pocet=0;
    printf("Zadej cislo lekce z ktere chces byt zkouseny:");
    scanf("%d",&zkous);
    f=fopen("slovnik.txt","r");
    while(fgets(tok, 40, f)){
        token=strtok(tok,"|");
        strcpy(cz, token);
        token=strtok(NULL,"|");
        strcpy(en, token);
        token=strtok(NULL,"|");
        lek=atoi(token);
        if(lek==zkous){
            printf("\nCesky:%s  Anglicky:",cz);
            fflush(stdin);
            gets(odp);
            male(odp);
            if(!strcmp(odp,en)){
                printf("\n\tSpravne\n");
                i++;
            }
            else printf("\n\tSpatne\n");
            pocet++;
        }
    }
    if(pocet!=0) printf("Z %d slovicek mas %d spravne, to znamena %.0f%% uspesnost",pocet,i,((float)i/pocet)*100);
    else printf("V teto lekci nejsou zadna slovicka");
    fclose(f);
}

void preklad(void){
    FILE *f;
    char volba[20],tok[50],*token,cz[20],en[20];
    int lek,i=0;
    printf("Zadej slovo na preklad:");
    fflush(stdin);
    gets(volba);
    f=fopen("slovnik.txt","r");
    while(fgets(tok, 40, f)){
        token=strtok(tok,"|");
        strcpy(cz, token);
        token=strtok(NULL,"|");
        strcpy(en, token);
        token=strtok(NULL,"|");
        lek=atoi(token);
        if(!strcmp(cz, volba)){
            printf("\nCeske slovo %s ma anglicky predklad %s v %d. lekci",cz,en,lek);
            i++;
        }
        if(!strcmp(en, volba)){
            printf("\nAnglicke slovo %s ma cesky predklad %s v %d. lekci",cz,en,lek);
            i++;
        }
    }
    if(i==0) printf("TAKE SLOVO TU NENI");
    fclose(f);
}


void menu(void){
    printf("\n1-Nove slovo\n");
    printf("2-Vypis\n");
    printf("3-Preklad\n");
    printf("4-Zkouseni z jedne lekce\n");
    printf("5-Nahodne zkouseni\n");
    printf("Vyber->");
}

void novy(){
    FILE *f;
    char cz[20],en[20],sl_cz[20],sl_en[20],*token,tok[50];
    int lek,k=0,sl_lek,test=0;
    printf("Zadej CZ:");
    fflush(stdin);
    gets(cz);
    male(cz);
    printf("Zadej EN:");
    gets(en);
    male(en);
    printf("Zadej lekce:");
    fflush(stdin);
    scanf("%d",&lek);
    f=fopen("slovnik.txt","r");
    if(f==NULL) k=1;
    else{
        while(fgets(tok, 40, f)){
            token=strtok(tok,"|");
            strcpy(sl_cz, token);
            token=strtok(NULL,"|");
            strcpy(sl_en, token);
            token=strtok(NULL,"|");
            sl_lek=atoi(token);
            if(!strcmp(cz, sl_cz) && !strcmp(en, sl_en)){
                printf("Toto slovicko uz zde je");
                test++;
            }
        }
    }
    fclose(f);
    if(test==0){
    f=fopen("slovnik.txt","a");
    if(k==1) fprintf(f,"%s|%s|%d|",cz,en,lek);
    else fprintf(f,"\n%s|%s|%d|",cz,en,lek);
    fclose(f);
    }
}

int pocet(void){
    FILE *f;
    char tok[50],*token;
    int pocet=0;
    f=fopen("slovnik.txt","r");
    while(fgets(tok, 40, f)){
        token=strtok(tok,"|");
        while(token!=NULL){
            token = strtok(NULL,"|");
        }
        pocet++;
    }
    fclose(f);
    return pocet;
}

void vypis(void){
    FILE *f;
    char tok[50],*token;
    f=fopen("slovnik.txt","r");
    printf("\tCZ\t\tEN\t\tLEKCE\n");
    while(fgets(tok, 40, f)){
        token=strtok(tok,"|");
        while(token!=NULL){
            printf("   %s",token);
            token = strtok(NULL,"|");
        }
    }
    fclose(f);
}

char male(char slovo[]){
    int i=0;
    while(slovo[i]){
        if(slovo[i]>='A' && slovo[i]<='Z') slovo[i]+=32;
        i++;
    }
    return *slovo;
}
