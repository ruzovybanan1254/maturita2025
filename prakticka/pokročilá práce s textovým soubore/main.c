#include "slovnik.h"

int main(int argc, char *argv[]) {
	int volba;
	int random;
	char cesta[10];
	strcpy(cesta, "prek.txt");
	while(1){
		printf("Zvolte moznost\n");
		printf("1\tPridat nove slovo\n");
		printf("2\tVypis slovniku\n");
		printf("3\tPreklad\n");
		printf("4\tZkouseni z jedne lekce\n");
		scanf("%d", &volba);
		switch (volba) {
		case 0:
			return 0;
			break;
		case 1:
			addWord(cesta);
			break;
		case 2:
			vypis(cesta);
			break;
		case 3:
			preklad(cesta);
			break;
		case 4:
			zkouseniLekce(cesta);
			break;
		case 5:
			srand(time(0));
			random = (rand());
			printf("\n%d \n%d\n", random, RAND_MAX);
			break;
		default:
			printf("\n\nZadejte spravnou moznost\n");
			break;
		}
		
		system("pause");
		system("cls");
	}	
	
	
	
	
	return 0;
}
