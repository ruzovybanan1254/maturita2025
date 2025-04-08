#ifndef OBJEKTY_H
#define OBJEKTY_H

#include <iostream>  // Pro vstup/výstup
#include <fstream>   // Pro práci se soubory
#include <sstream>   // Pro práci se stringy a streamy
#include <string.h>  // Knihovna pro práci s řetězci (doporučováno spíše <string>)

using namespace std; // Používáme standardní jmenný prostor

// Třída reprezentující jedno pivo v seznamu
class Node {
private:
	int number; // ID piva
	string name; // Název piva
	double price; // Cena piva
	int ibu; // IBU (hořkost piva)
	Node *prev, *next; // Ukazatele na předchozí a následující pivo v seznamu (dvojlinkední seznam)
	
public:
	// Konstruktor pro inicializaci uzlu
	Node(); 
	Node(int cislo); // Konstruktor pouze s ID
	Node(int cislo, string nazev); // Konstruktor s ID a názvem
	Node(int cislo, string nazev, double cena); // Konstruktor s ID, názvem a cenou
	Node(int cislo, string nazev, double cena, int ibucko); // Konstruktor s ID, názvem, cenou a IBU
	
	// Settery pro nastavení hodnot atributů
	void setNumber(int c); 
	void setName(string nazev); 
	void setPrevNode(Node *p); // Nastaví ukazatel na předchozí uzel
	void setNextNode(Node *n); // Nastaví ukazatel na následující uzel
	
	// Setter pro cenu
	void setPrice(double cena) {
		if(cena > 0 && cena < 10000) { // Kontrola rozsahu ceny
			price = cena; // Nastavení ceny, pokud je v platném rozsahu
		}
	}
	
	// Setter pro IBU (hořkost piva)
	void setIbu(int ibucko) {
		if(ibucko <= 0 || ibucko > 100) { // Kontrola rozsahu IBU
			system("cls"); // Vymaže obrazovku
			cout << "Ibu musi byt v rozsahu 0 az 100" << endl; // Chybové hlášení
			system("pause"); // Pauza pro uživatele
			return;
		} else {
			ibu = ibucko; // Nastavení hodnoty IBU, pokud je platná
		}
	}
	
	// Gettery pro získání hodnot atributů
	double getPrice() { return price; } // Vrací cenu piva
	int getIbu() { return ibu; } // Vrací IBU piva
	Node* getPrevNode(); // Vrací ukazatel na předchozí uzel
	Node* getNextNode(); // Vrací ukazatel na následující uzel
	int getNumber(); // Vrací ID piva
	string getName(); // Vrací název piva
	
	// Přetížení operátoru << pro výpis objektu Node (pro výstup na obrazovku)
	friend ostream& operator<<(ostream& out, Node& n);
};

// Třída reprezentující seznam piv
class List {
	Node* first = nullptr; // Ukazatel na první prvek seznamu
	
public:
	// Konstruktor pro inicializaci seznamu
	List() {
		first = nullptr; // Inicializace jako prázdný seznam
	}
	List(Node* n) {
		first = n; // Konstruktor pro seznam s prvním uzlem
	}
	
	// Destruktor
	~List() {
		Node* current = first;
		while (current != nullptr) {
			Node* nextNode = current->getNextNode(); // Uloží ukazatel na další uzel
			delete current; // Uvolní paměť pro aktuální uzel
			current = nextNode; // Pokračuje na další uzel
		}
	}
	
	// Getter pro získání prvního prvku seznamu
	Node* getFirst() { return first; }
	
	// Metody pro přidání nového piva do seznamu
	void addNodeToStart(Node n); // Přidá nové pivo na začátek seznamu
	void addNodeToStart2(int c, string nazev, double cena, int ibu); // Alternativní metoda pro přidání na začátek
	void addNodeToEnd(Node n); // Přidá nové pivo na konec seznamu
	
	// Přetížení operátoru << pro výpis celého seznamu piv
	friend ostream& operator<<(ostream& out, List& n);
	
	// Metody pro získání informací o seznamu
	double average(); // Vypočítá průměrnou cenu piva v seznamu
	Node* min(); // Najde pivo s nejnižší cenou
	Node* max(); // Najde pivo s nejvyšší cenou
	
	// Hledání piva v seznamu podle různých kritérií
	Node* findById(int cislo); // Najde pivo podle ID
	Node* findByName(string nazev); // Najde pivo podle názvu
	Node* findByIbu(int ibucko); // Najde pivo podle IBU
	Node* findByPrice(double cena); // Najde pivo podle ceny
	
	// Metody pro práci se soubory
	void loadFromFile(); // Načte seznam piv ze souboru
	void saveToFile(); // Uloží seznam piv do souboru
	
	// Metody pro úpravu seznamu
	void remove(Node* n); // Odstraní pivo ze seznamu
	void edit(Node* n); // Umožní upravit pivo v seznamu
	
	// Metody pro řazení seznamu piv podle různých atributů
	void sortByNumber(); // Seřadí seznam podle ID
	void sortByPrice(); // Seřadí seznam podle ceny
	void sortByName(); // Seřadí seznam podle názvu
	void sortByIbu(); // Seřadí seznam podle IBU
	
	// Metoda pro hledání piva v seznamu (např. podle názvu)
	void find();
	
	// Pomocná metoda pro výměnu dvou uzlů v seznamu (např. při řazení)
	void zamena(Node* a, Node* b);
};

#endif

