#include "objekty.h"
#include <iostream>
using namespace std;



int main() {
	Seznam seznam;
	int volba;
	string nazev;
	Uzel* pom=new Uzel();
	do {
		cout << "\n--- Uzivatelska nabidka ---\n";
		cout << "1. Pridat uzel (objekt)\n";
		cout << "2. Pridat uzel (hodnoty)\n";
		cout << "3. Pridat uzel na konec\n";
		cout << "4. Vypsat seznam\n";
		cout << "5. Vypocitat prumer cisel\n";
		cout << "6. Najit minimum\n";
		cout << "7. Najit maximum\n";
		cout << "8. Ulozit do souboru\n";
		cout << "9. Nacist ze souboru\n";
		cout << "10. Odstranit uzel\n";
		cout << "11. Editovat uzel\n";
		cout << "12. Seradit seznam podle cisla\n";
		cout << "0. Konec\n";
		cout << "Zadejte volbu: ";
		cin >> volba;
		
		switch (volba) {
			case 1: {
				int cislo;
				string nazev;
				cout << "Zadejte cislo: ";
				cin >> cislo;
				cout << "Zadejte nazev: ";
				cin.ignore();
				getline(cin, nazev);
				Uzel u(cislo, nazev);
				seznam.addUzel1(u);
				break;
			}
			case 2: {
				int cislo;
				string nazev;
				cout << "Zadejte cislo: ";
				cin >> cislo;
				cout << "Zadejte nazev: ";
				cin.ignore();
				getline(cin, nazev);
				seznam.addUzel2(cislo, nazev);
				break;
			}
			case 3: {
				int cislo;
				string nazev;
				cout << "Zadejte cislo: ";
				cin >> cislo;
				cout << "Zadejte nazev: ";
				cin.ignore();
				getline(cin, nazev);
				Uzel u(cislo, nazev);
				seznam.addUzelToEnd(u);
				break;
			}
		case 4:
			cout << &seznam;
			
			break;
		case 5:
			cout << "Prumer: " << seznam.prumer() << endl;
			break;
		case 6:
			
			pom = seznam.min();
			cout << "Minimum: " << pom->getCislo() << endl;
			break;
		case 7:
			pom = seznam.max();
			cout << "Maximum: " << pom->getCislo() << endl;
			break;
		case 8:
			seznam.saveToFile();
			cout << "Seznam ulozen." << endl;
			break;
		case 9:
			while (seznam.getPrvni() != nullptr) {
				seznam.remove(seznam.getPrvni());
			}
			seznam.loadFromFile();
			cout << "Seznam nacten ze souboru." << endl;
			break;
		case 10: {
			int cislo;
			cout << "Zadejte cislo uzlu k odstraneni: ";
			cin >> cislo;
			Uzel *uzel = seznam.getPrvni();
			while (uzel != nullptr) {
				if (uzel->getCislo() == cislo) {
					seznam.remove(uzel);
					cout << "Uzel odstranen." << endl;
					break;
				}
				uzel = uzel->getNasl();
			}
			break;
		}
		case 11: {
			int cislo;
			cout << "Zadejte cislo uzlu k editaci: ";
			cin >> cislo;
			Uzel *uzel = seznam.getPrvni();
			while (uzel != nullptr) {
				if (uzel->getCislo() == cislo) {
					seznam.edit(uzel);
					cout << "Uzel editovan." << endl;
					break;
				}
				uzel = uzel->getNasl();
			}
			break;
		}
		case 12:
			seznam.sortByNumber();
			cout << "Seznam serazen." << endl;
			break;
		case 0:
			cout << "Konec programu." << endl;
			break;
		default:
			cout << "Neplatna volba, zkuste to znovu." << endl;
		}
		system("pause");
		system("cls");
		
	} while (volba != 0);

	delete pom;
	return 0;
}

