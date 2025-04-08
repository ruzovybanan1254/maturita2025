#include "objekty.h"

// Konstruktor pro Node
Node::Node() {
	number = 0;           // Inicializace čísla piva na 0
	name = "pivo";        // Inicializace názvu piva na "pivo"
	price = 0;            // Inicializace ceny piva na 0
	next = nullptr;       // Inicializace ukazatele na další prvek seznamu jako nullptr
	prev = nullptr;       // Inicializace ukazatele na předchozí prvek seznamu jako nullptr
}

// Konstruktor pro Node s parametrem čísla piva
Node::Node(int cislo) {
	number = cislo;       // Nastavení čísla piva
	name = "pivo";        // Nastavení názvu piva na "pivo"
	price = 0;            // Cena piva je nastavena na 0
	next = nullptr;       // Inicializace ukazatele na další prvek seznamu jako nullptr
	prev = nullptr;       // Inicializace ukazatele na předchozí prvek seznamu jako nullptr
}

// Konstruktor pro Node s parametrem čísla a názvu piva
Node::Node(int cislo, string nazev) {
	number = cislo;       // Nastavení čísla piva
	name = nazev;         // Nastavení názvu piva
	price = 0;            // Cena piva je nastavena na 0
	next = nullptr;       // Inicializace ukazatele na další prvek seznamu jako nullptr
	prev = nullptr;       // Inicializace ukazatele na předchozí prvek seznamu jako nullptr
}

// Konstruktor pro Node s parametry čísla, názvu a ceny piva
Node::Node(int cislo, string nazev, double cena) {
	number = cislo;       // Nastavení čísla piva
	name = nazev;         // Nastavení názvu piva
	price = cena;         // Nastavení ceny piva
	next = nullptr;       // Inicializace ukazatele na další prvek seznamu jako nullptr
	prev = nullptr;       // Inicializace ukazatele na předchozí prvek seznamu jako nullptr
}

// Konstruktor pro Node s parametry čísla, názvu, ceny a ibu piva
Node::Node(int cislo, string nazev, double cena, int ibucko) {
	number = cislo;       // Nastavení čísla piva
	name = nazev;         // Nastavení názvu piva
	price = cena;         // Nastavení ceny piva
	next = nullptr;       // Inicializace ukazatele na další prvek seznamu jako nullptr
	prev = nullptr;       // Inicializace ukazatele na předchozí prvek seznamu jako nullptr
	ibu = ibucko;         // Nastavení hodnoty IBU (bitter units) piva
}

// Settery pro atributy Node
void Node::setNumber(int c) {
	this->number = c;     // Nastavení čísla piva
}

void Node::setName(string nazev) {
	this->name = nazev;   // Nastavení názvu piva
}

void Node::setPrevNode(Node *p) {
	this->prev = p;       // Nastavení předchozího prvku seznamu
}

void Node::setNextNode(Node *n) {
	this->next = n;       // Nastavení následujícího prvku seznamu
}

// Gettery pro atributy Node
Node* Node::getPrevNode() {
	return this->prev;    // Vrací ukazatel na předchozí prvek seznamu
}

Node* Node::getNextNode() {
	return this->next;    // Vrací ukazatel na následující prvek seznamu
}

int Node::getNumber() {
	return this->number;  // Vrací číslo piva
}

string Node::getName() {
	return this->name;    // Vrací název piva
}

// Operátor << pro výpis Node do streamu
ostream& operator<<(ostream& out, Node& n) {
	out << "\t|\t" << n.getNumber() << "\t|\t" << n.getName() << "\t|\t" << n.getPrice() << "\t|\t" << n.getIbu() << endl;
	return out;
}

// Funkce pro přidání Node na začátek seznamu
void List::addNodeToStart(Node n) {
	Node* pom = new Node(n);  // Vytvoření nového uzlu
	if (findById(n.getNumber()) != nullptr) {
		cout << "Pivo s takovymto ID uz existuje" << endl; // Pokud pivo s tímto ID již existuje, nebudeme přidávat
		return;
	}
	if (this->first == nullptr) {  // Pokud je seznam prázdný
		first = pom;
	} else {
		pom->setNextNode(this->first);  // Nastavení nového uzlu na začátek seznamu
		this->first->setPrevNode(pom);  // Nastavení předchozího ukazatele na nový uzel
		this->first = pom;              // Nastavení začátku seznamu na nový uzel
	}
}

// Funkce pro přidání Node na začátek seznamu s parametry
void List::addNodeToStart2(int c, string nazev, double cena, int ibu) {
	Node n = Node(c, nazev, cena, ibu);  // Vytvoření uzlu
	addNodeToStart(n);  // Přidání uzlu na začátek seznamu
}

// Funkce pro přidání Node na konec seznamu
void List::addNodeToEnd(Node n) {
	if (first == nullptr) {  // Pokud je seznam prázdný
		addNodeToStart(n);    // Přidání na začátek
		return;
	}
	if (findById(n.getNumber()) != nullptr) {  // Pokud pivo s tímto ID již existuje
		cout << "Pivo s takovymto ID uz existuje" << endl;
		return;
	}
	Node *novy = new Node(n);  // Vytvoření nového uzlu
	Node *pom = first;         // Dočasný ukazatel pro procházení seznamu
	while (pom->getNextNode() != nullptr) {  // Procházení seznamu až na konec
		pom = pom->getNextNode();
	}
	pom->setNextNode(novy);     // Nastavení ukazatele posledního uzlu na nový uzel
	novy->setPrevNode(pom);     // Nastavení předchozího ukazatele nového uzlu
}

// Operátor << pro výpis List do streamu
ostream& operator<<(ostream& out, List& n) {
	Node *pom = n.getFirst();  // Dočasný ukazatel na první uzel seznamu
	if (n.getFirst() == nullptr) {  // Pokud je seznam prázdný
		out << "Seznam je prazdny." << endl;
		return out;
	}
	out << "\t|\tID\t|\tNazev piva\t|\tCena\t|\tIBU" << endl << endl;
	while (pom != nullptr) {  // Procházení seznamu a výpis jednotlivých uzlů
		out << *pom << endl;
		pom = pom->getNextNode();
	}
	return out;
}

// Funkce pro výpočet průměrné ceny piva v seznamu
double List::average() {
	Node *pom = new Node();  // Dočasný uzel pro procházení seznamu
	double sum = 0;          // Suma cen piv
	double count = 0;        // Počet piv
	if (first == nullptr) {  // Pokud je seznam prázdný
		cout << "Seznam je prazdny" << endl;
		return -1;
	}
	for (pom = this->getFirst(); pom != nullptr; pom = pom->getNextNode()) {  // Procházení seznamu
		count++;
		sum += pom->getPrice();  // Sčítání cen piv
	}
	return sum / count;  // Vrací průměrnou cenu
}

// Funkce pro nalezení Node s minimální cenou
Node* List::min() {
	if (first == nullptr) {  // Pokud je seznam prázdný
		cout << "Seznam je prazdny" << endl;
		return nullptr;
	}
	Node *pom = new Node();
	int min = this->first->getPrice();  // Inicializace minimální ceny
	Node *minNode = this->first;        // Inicializace uzlu s minimální cenou
	for (pom = this->getFirst(); pom != nullptr; pom = pom->getNextNode()) {  // Procházení seznamu
		if (pom->getPrice() < min) {  // Pokud je cena uzlu menší než aktuální minimum
			min = pom->getPrice();
			minNode = pom;  // Nastavení uzlu s novým minimem
		}
	}
	return minNode;  // Vrací uzel s minimální cenou
}

// Funkce pro nalezení Node s maximální cenou
Node* List::max() {
	if (first == nullptr) {  // Pokud je seznam prázdný
		cout << "Seznam je prazdny" << endl;
		return nullptr;
	}
	Node *pom = new Node();
	int max = this->first->getPrice();  // Inicializace maximální ceny
	Node *maxNode = this->first;        // Inicializace uzlu s maximální cenou
	for (pom = this->getFirst(); pom != nullptr; pom = pom->getNextNode()) {  // Procházení seznamu
		if (pom->getPrice() > max) {  // Pokud je cena uzlu větší než aktuální maximum
			max = pom->getPrice();
			maxNode = pom;  // Nastavení uzlu s novým maximem
		}
	}
	return maxNode;  // Vrací uzel s maximální cenou
}

// Funkce pro nalezení Node podle ID
Node* List::findById(int cislo) {
	Node *pom = first;
	while (pom != nullptr) {  // Procházení seznamu
		if (pom->getNumber() == cislo) return pom;  // Pokud nalezne uzel s odpovídajícím ID
		pom = pom->getNextNode();
	}
	return nullptr;  // Pokud není nalezeno
}

// Funkce pro nalezení Node podle názvu
Node* List::findByName(string nazev) {
	Node *pom = first;
	while (pom != nullptr) {  // Procházení seznamu
		if (pom->getName() == nazev) return pom;  // Pokud nalezne uzel s odpovídajícím názvem
		pom = pom->getNextNode();
	}
	return nullptr;  // Pokud není nalezeno
}

// Funkce pro nalezení Node podle IBU
Node* List::findByIbu(int ibucko) {
	Node *pom = first;
	while (pom != nullptr) {  // Procházení seznamu
		if (pom->getIbu() == ibucko) return pom;  // Pokud nalezne uzel s odpovídajícím IBU
		pom = pom->getNextNode();
	}
	return nullptr;  // Pokud není nalezeno
}

// Funkce pro nalezení Node podle ceny
Node* List::findByPrice(double cena) {
	Node *pom = first;
	while (pom != nullptr) {  // Procházení seznamu
		if (pom->getPrice() == cena) return pom;  // Pokud nalezne uzel s odpovídající cenou
		pom = pom->getNextNode();
	}
	return nullptr;  // Pokud není nalezeno
}

// Funkce pro načtení piv ze souboru
void List::loadFromFile() {
	ifstream file;
	file.open("pivecka.txt");  // Otevření souboru
	if (!file.is_open()) {  // Pokud se soubor nepodařilo otevřít
		cout << "soubor se nepodarilo otevrit" << endl;
		return;
	}
	string radek;  // Dočasná proměnná pro čtení řádků ze souboru
	string cislo, nazev, cena, ibucko;
	double cen;
	int c;
	int ibuc;
	
	// Vymazání stávajícího seznamu
	while (first != nullptr) {
		Node* temp = first;
		first = first->getNextNode();
		delete temp;
		temp = nullptr;
	}
	this->first = nullptr;
	
	Node x;  // Dočasný uzel pro vytvoření nových piv
	// Načítání piv z každého řádku souboru
	while (getline(file, radek)) {
		stringstream radecek = stringstream(radek);
		getline(radecek, cislo, '$');  // Čtení ID piva
		c = stoi(cislo);
		getline(radecek, nazev, '$');  // Čtení názvu piva
		getline(radecek, cena, '$');  // Čtení ceny piva
		getline(radecek, ibucko, '$');  // Čtení IBU
		cen = stod(cena);
		ibuc = stoi(ibucko);
		x = Node(c, nazev, cen, ibuc);  // Vytvoření uzlu piva
		addNodeToEnd(x);  // Přidání uzlu do seznamu
	}
	cout << "Uspesne nacteno ze souboru pivecka.txt" << endl;
}

// Funkce pro uložení piv do souboru
void List::saveToFile() {
	ofstream file;
	file.open("pivecka.txt");  // Otevření souboru pro zápis
	if (!file.is_open()) {  // Pokud se soubor nepodařilo otevřít
		cout << "soubor se nepodarilo otevrit" << endl;
		return;
	}
	Node *pom = new Node();
	for (pom = this->getFirst(); pom != nullptr; pom = pom->getNextNode()) {  // Procházení seznamu
		file << pom->getNumber() << "$" << pom->getName() << "$" << pom->getPrice() << "$" << pom->getIbu() << "$" << endl;
	}
	cout << "Saved to file pivecka.txt" << endl;  // Informace o úspěšném uložení
	file.close();  // Zavření souboru
}

// Funkce pro odstranění uzlu ze seznamu
void List::remove(Node *n) {
	// Případ, kdy uzel k odstranění je první uzel
	if (n == first) {
		first = first->getNextNode();  // Nastavíme první uzel na následující uzel
		delete n;                      // Smažeme aktuální uzel
		n = nullptr;                   // Nastavíme ukazatel na nullptr (dobrá praxe, ale není nutné)
		return;
	}
	// Případ, kdy uzel je poslední
	if (n->getNextNode() == nullptr) {
		n->getPrevNode()->setNextNode(nullptr); // Nastavíme ukazatel na následující uzel předchozího uzlu na nullptr
		delete n;                             // Smažeme aktuální uzel
		n = nullptr;                          // Nastavíme ukazatel na nullptr
		return;
	}
	
	// Případ, kdy uzel je někde uprostřed
	Node *pre;
	Node *nex;
	pre = n->getPrevNode();          // Získáme předchozí uzel
	nex = n->getNextNode();          // Získáme následující uzel
	pre->setNextNode(nex);           // Nastavíme ukazatel na následující uzel předchozího uzlu
	nex->setPrevNode(pre);           // Nastavíme ukazatel na předchozí uzel následujícího uzlu
}

// Funkce pro úpravu detailů piva (uzlu)
void List::edit(Node *n) {
	double cena;        // Cena piva
	string nam;         // Název piva
	int ibucko;         // IBU (International Bitterness Units)
	int volba;          // Uživatelská volba pro to, co upravit
	
	do {
		system("cls");  // Vyčistí obrazovku (Windows)
		cout << "--------------------------------" << endl;
		cout << "Zadejte co byste radi upravili" << endl; // Výzva pro volbu
		cout << "0. Zpet" << endl;
		cout << "1. Nazev piva" << endl;
		cout << "2. Nova cena" << endl;
		cout << "3. Nove ibu" << endl;
		cin >> volba;    // Získáme uživatelský vstup pro volbu
		
		switch (volba) {
			case 1:  // Upravit název piva
			system("cls");
			cout << "Zadejte novy nazev piva" << endl;
			cin.ignore();  // Vyčistí vstupní buffer
			getline(cin, nam);  // Získáme nový název piva
			n->setName(nam);    // Aktualizujeme název
			break;
			case 2:  // Upravit cenu piva
			cout << "Zadejte novou cenu piva" << endl;
			cin >> cena;      // Získáme novou cenu piva
			n->setPrice(cena); // Aktualizujeme cenu
			break;
			case 3:  // Upravit IBU
			cout << "Zadejte nove ibu piva" << endl;
			cin >> ibucko;    // Získáme novou hodnotu IBU
			n->setIbu(ibucko); // Aktualizujeme IBU
			break;
			case 0:  // Ukončit
			break;
		default:
			cout << "zkus to znovu";  // Pokud je volba neplatná
			break;
		}
	} while (volba != 0);  // Opakujeme, dokud uživatel nevybere možnost ukončení
}

// Funkce pro seřazení seznamu podle čísla u uzlů
void List::sortByNumber() {
	if (first == nullptr || first->getNextNode() == nullptr) return; // Pokud je seznam prázdný nebo obsahuje pouze jeden uzel
	
	bool swapped;
	do {
		swapped = false;
		Node* pom = first; // Dočasný ukazatel pro procházení seznamu
		
		while (pom->getNextNode() != nullptr) {
			if (pom->getNumber() > pom->getNextNode()->getNumber()) {
				zamena(pom, pom->getNextNode()); // Vyměníme uzly, pokud je číslo aktuálního uzlu větší než číslo následujícího
				swapped = true; // Označíme, že došlo k výměně
			} else {
				pom = pom->getNextNode(); // Posuneme se na další uzel, pokud nedošlo k výměně
			}
		}
	} while (swapped);  // Opakujeme, dokud nedojde k žádné výměně
}

// Funkce pro seřazení seznamu podle ceny u uzlů
void List::sortByPrice() {
	if (first == nullptr || first->getNextNode() == nullptr) return; // Pokud je seznam prázdný nebo obsahuje pouze jeden uzel
	
	bool swapped;
	do {
		swapped = false;
		Node* pom = first;
		
		while (pom->getNextNode() != nullptr) {
			if (pom->getPrice() > pom->getNextNode()->getPrice()) {
				zamena(pom, pom->getNextNode()); // Vyměníme uzly, pokud je cena aktuálního uzlu větší než cena následujícího
				swapped = true;  // Označíme, že došlo k výměně
			} else {
				pom = pom->getNextNode();  // Posuneme se na další uzel, pokud nedošlo k výměně
			}
		}
	} while (swapped);  // Opakujeme, dokud nedojde k žádné výměně
}

// Funkce pro seřazení seznamu podle názvu u uzlů
void List::sortByName() {
	if (first == nullptr || first->getNextNode() == nullptr) return; // Pokud je seznam prázdný nebo obsahuje pouze jeden uzel
	
	bool swapped;
	do {
		swapped = false;
		Node* pom = first;
		
		while (pom->getNextNode() != nullptr) {
			if (pom->getName() > pom->getNextNode()->getName()) {
				zamena(pom, pom->getNextNode()); // Vyměníme uzly, pokud je název aktuálního uzlu lexikograficky větší než název následujícího
				swapped = true;  // Označíme, že došlo k výměně
			} else {
				pom = pom->getNextNode();  // Posuneme se na další uzel, pokud nedošlo k výměně
			}
		}
	} while (swapped);  // Opakujeme, dokud nedojde k žádné výměně
}

// Funkce pro seřazení seznamu podle IBU (hořkosti) u uzlů
void List::sortByIbu() {
	if (first == nullptr || first->getNextNode() == nullptr) return; // Pokud je seznam prázdný nebo obsahuje pouze jeden uzel
	
	bool swapped;
	do {
		swapped = false;
		Node* pom = first;
		
		while (pom->getNextNode() != nullptr) {
			if (pom->getIbu() > pom->getNextNode()->getIbu()) {
				zamena(pom, pom->getNextNode()); // Vyměníme uzly, pokud je IBU aktuálního uzlu větší než IBU následujícího
				swapped = true;  // Označíme, že došlo k výměně
			} else {
				pom = pom->getNextNode();  // Posuneme se na další uzel, pokud nedošlo k výměně
			}
		}
	} while (swapped);  // Opakujeme, dokud nedojde k žádné výměně
}

// Funkce pro výměnu dat mezi dvěma uzly
void List::zamena(Node* a, Node* b) {
	// Dočasně uložíme data prvního uzlu
	int numberFirst = a->getNumber();
	string nameFirst = a->getName();
	double priceFirst = a->getPrice();
	int firstIbu = a->getIbu();
	
	// Vyměníme data mezi dvěma uzly
	a->setName(b->getName());
	a->setNumber(b->getNumber());
	a->setPrice(b->getPrice());
	a->setIbu(b->getIbu());
	
	b->setPrice(priceFirst);
	b->setName(nameFirst);
	b->setNumber(numberFirst);
	b->setIbu(firstIbu);
}

// Funkce pro hledání uzlu podle různých kritérií
void List::find() {
	double cena;        // Cena piva
	string nam;         // Název piva
	int ibucko;         // Hodnota IBU
	int volba;          // Uživatelská volba pro kritéria hledání
	int idecko;         // ID piva pro hledání
	Node *x = new Node();  // Dočasný uzel pro uložení výsledku
	
	do {
		system("cls");  // Vyčistí obrazovku
		cout << "--------------------------------" << endl;
		cout << "Podle ceho chcete hledat" << endl;  // Zeptáme se uživatele, podle čeho hledat
		cout << "0. Zpet" << endl;
		cout << "1. ID piva" << endl;
		cout << "2. Nazev" << endl;
		cout << "3. Cena" << endl;
		cout << "4. IBU" << endl;
		cin >> volba;  // Získáme uživatelský vstup pro kritérium hledání
		
		x = nullptr;  // Resetujeme dočasný uzel
		switch (volba) {
			case 1:  // Hledat podle ID
			system("cls");
			cout << "Zadejte ID piva" << endl;
			cin >> idecko;
			x = findById(idecko);  // Zavoláme funkci pro hledání podle ID
			break;
			case 2:  // Hledat podle názvu
			system("cls");
			cout << "Zadejte nazev piva" << endl;
			cin.ignore();  // Vyčistí vstupní buffer
			getline(cin, nam);  // Získáme název piva
			x = findByName(nam);  // Zavoláme funkci pro hledání podle názvu
			break;
			case 3:  // Hledat podle ceny
			cout << "Zadejte cenu piva" << endl;
			cin >> cena;
			x = findByPrice(cena);  // Zavoláme funkci pro hledání podle ceny
			break;
			case 4:  // Hledat podle IBU
			cout << "Zadejte IBU piva" << endl;
			cin >> ibucko;
			x = findByIbu(ibucko);  // Zavoláme funkci pro hledání podle IBU
			break;
			case 0:  // Ukončit
			delete x;  // Uvolníme dočasný uzel
			x = nullptr;
			return;
			break;
		default:
			cout << "zkus to znovu" << endl;  // Pokud je volba neplatná
			break;
		}
		
		if (x != nullptr) cout << *x << endl;  // Pokud byl uzel nalezen, vypíšeme ho
		else cout << "nenalezeno" << endl;  // Pokud nebyl uzel nalezen
		
		system("pause");  // Pauza před pokračováním
	} while (volba != 0);  // Opakujeme, dokud uživatel nevybere možnost ukončení
}
