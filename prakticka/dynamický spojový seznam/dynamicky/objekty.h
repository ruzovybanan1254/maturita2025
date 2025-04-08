#ifndef OBJEKTY_H
#define OBJEKTY_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <sstream>

using namespace std;
class Uzel {
private:
	int cislo;
	string nazev;
	Uzel *pred, *nasl;
public:
	Uzel();
	Uzel(int c);
	Uzel(int c, string n);
	
	void setCislo(int c);
	void setNazev(string n);
	void setPred(Uzel *u);
	void setNasl(Uzel *u);
	
	int getCislo();
	string getNazev();
	Uzel* getPred();
	Uzel* getNasl();
	friend ostream &operator<<(ofstream &os, Uzel const *u);

};

class Seznam {
	Uzel* prvni=nullptr;
	
public:
	Uzel* getPrvni(){
		return prvni;
	}
	Seznam(){
		
	}
	void addUzel1(Uzel u);
	void addUzel2(int c, string n);
	void addUzelToEnd(Uzel u);
	friend ostream &operator<<(ostream &os, Seznam  *s);
	double prumer();
	Uzel *min();
	Uzel *max();
	void loadFromFile();
	void saveToFile();
	void remove(Uzel *u);
	void edit(Uzel *u);
	void sortByNumber();


};

#endif
