
#include <iostream>
#include "objekty.h"  // Zahrnuje externí knihovnu, která obsahuje definice tříd a funkcí pro práci se seznamem piv

using namespace std;

// Funkce pro zobrazení hlavního menu
void showMenu() {
	cout << "\n===== Pivni seznam =====" << endl;
	cout << "1. Pridat pivo na zacatek" << endl;
	cout << "2. Pridat pivo na konec" << endl;
	cout << "3. Vypsat seznam" << endl;
	cout << "4. Ulozit do souboru" << endl;
	cout << "5. Nacist ze souboru" << endl;
	cout << "6. Najit nejmensi cenu" << endl;
	cout << "7. Najit nejvetsi cenu" << endl;
	cout << "8. Vypocitat prumernou hodnotu ceny piva" << endl;
	cout << "9. Seradit podle ID" << endl;
	cout << "10. Seradit podle ceny" << endl;
	cout << "11. Seradit podle nazvu" << endl;
	cout << "12. Seradit podle IBU" << endl;
	cout << "13. Upravit pivo" << endl;
	cout << "14. Odstranit pivo" << endl;
	cout << "15. Hledat pivo" << endl;
	cout << "0. Konec" << endl;
	cout << "Vyber moznost: ";  // Vyzve uživatele k zadání volby z menu
}

// Funkce pro čtení nového piva zadaného uživatelem
Node readNew(){
	int cislo, ibucko;
	string nazev;
	double cena;
	
	// Získání údajů o novém pivu od uživatele
	cout << "Zadej ID piva: ";
	cin >> cislo;
	cout << "Zadej nazev piva: ";
	cin.ignore();  // Vyprázdní buffer
	getline(cin, nazev);  // Načte název piva
	cout << "Zadejte cenu piva: ";
	cin >> cena;
	cout << "Zadejte IBU piva: ";
	cin >> ibucko;
	return Node(cislo, nazev, cena, ibucko);  // Vytvoří a vrátí nový objekt typu Node (pivo)
}

int main() {
	List seznam;  // Vytvoří instanci třídy List pro uchování seznamu piv
	int volba, cislo;
	string nazev;
	Node* p = new Node();  // Vytvoří ukazatel na nový objekt Node (pivo)
	do {
		showMenu();  // Zobrazí hlavní menu
		cin >> volba;  // Načte volbu uživatele
		switch (volba) {
		case 1:
			seznam.addNodeToStart(readNew());  // Přidá nové pivo na začátek seznamu
			break;
		case 2:
			seznam.addNodeToEnd(readNew());  // Přidá nové pivo na konec seznamu
			break;
		case 3:
			cout << seznam;  // Vypíše celý seznam piv
			break;
		case 4:
			seznam.saveToFile();  // Uloží seznam piv do souboru
			break;
		case 5:
			seznam.loadFromFile();  // Načte seznam piv ze souboru
			break;
		case 6:
			p = seznam.min();  // Najde pivo s nejmenší cenou
			cout << "Nejmensi cena:" << endl;
			cout << *p;  // Vypíše pivo s nejmenší cenou
			break;
		case 7:
			p = seznam.max();  // Najde pivo s největší cenou
			cout << "Nejvetsi cena:" << endl;
			cout << *p;  // Vypíše pivo s největší cenou
			break;
		case 8:
			cout << "Prumerna cena: " << seznam.average() << endl;  // Vypočítá a vypíše průměrnou cenu piv
			break;
		case 9:
			seznam.sortByNumber();  // Seřadí seznam podle ID piva
			cout << "Seznam serazen podle ID." << endl;
			break;
		case 10:
			seznam.sortByPrice();  // Seřadí seznam podle ceny piva
			cout << "Seznam serazen podle ceny." << endl;
			break;
		case 11:
			seznam.sortByName();  // Seřadí seznam podle názvu piva
			cout << "Seznam serazen podle jmena." << endl;
			break;
		case 12:
			seznam.sortByIbu();  // Seřadí seznam podle IBU piva
			cout << "Seznam serazen podle IBU." << endl;
			break;	
			case 13: {
				cout << "Zadej ID piva k uprave: ";
				cin >> cislo;
				Node* pivo = seznam.findById(cislo);  // Najde pivo podle ID
				if (pivo) seznam.edit(pivo);  // Umožní úpravu piva, pokud je nalezeno
				else cout << "Pivo nenalezeno." << endl;
				break;
			}
			case 14: {
				cout << "Zadej ID piva k odstraneni: ";
				cin >> cislo;
				Node* pivo = seznam.getFirst();  // Začne hledat pivo od prvního
				while (pivo && pivo->getNumber() != cislo) {
					pivo = pivo->getNextNode();  // Prohledá seznam, dokud nenajde požadované pivo
				}
				if (pivo) seznam.remove(pivo);  // Odstraní pivo, pokud je nalezeno
				else cout << "Pivo nenalezeno." << endl;
				break;
			}
		case 15:
			seznam.find();  // Funkce pro hledání piva v seznamu
			break;
		case 0:
			cout << "Ukonceni programu." << endl;
			cout << "prejete si ulozit databazi do souboru? 0/1" << endl;
			int volbicka;
			cin >> volbicka;
			if (volbicka == 1) {
				seznam.saveToFile();  // Uloží seznam do souboru při ukončení programu
				return 0;
			}
			break;
		default:
			cout << "Neplatna volba, zkus to znovu." << endl;  // Pokud je volba neplatná, uživatel je informován
		}
		system("pause");  // Pauza před opětovným zobrazením menu
		system("cls");  // Vyčistí obrazovku
	} while (volba != 0);  // Program pokračuje, dokud uživatel nezvolí možnost 0 pro ukončení
	
	return 0;  // Konec programu
}
