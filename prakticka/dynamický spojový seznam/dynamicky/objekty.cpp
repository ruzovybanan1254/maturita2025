#include "objekty.h"


//konstruktory
Uzel::Uzel(){
	cislo =0;
	nazev = "";
	pred=nullptr;
	nasl=nullptr;
}
Uzel::Uzel(int c){
	cislo=c;
	pred=nullptr;
	nasl=nullptr;
}
Uzel::Uzel(int c, string n){
	cislo=c;
	nazev = n;
	pred=nullptr;
	nasl=nullptr;
}

//settery
void Uzel::setCislo(int c){
	cislo = c;
}
void Uzel::setNazev(string n){
	nazev = n;
}
void Uzel::setPred(Uzel *u){
	pred = u;
}
void Uzel::setNasl(Uzel *u){
	nasl = u;
}


//gettery
int Uzel::getCislo(){
	return cislo;
}
string Uzel::getNazev(){
	return nazev;
}
Uzel* Uzel::getPred(){
	return pred;
}
Uzel* Uzel::getNasl(){
	return nasl;
}

//vypis
ostream &operator<<(ofstream &os, Uzel *u){
	cout << "Cislo:" << u->getCislo() << "  Nazev:"<<u->getNazev()<<endl;
	return os;
}




void Seznam::addUzel1(Uzel u){
	Uzel *novy = new Uzel(u);
	novy->setCislo(u.getCislo());
	novy->setNazev(u.getNazev());
	if(this->prvni==nullptr){
		this->prvni = novy;
	}else{
		novy->setNasl(this->prvni);
		this->prvni->setPred(novy);
		this->prvni=novy;
	}
}
void Seznam::addUzel2(int c, string n){
	Uzel *novy = new Uzel(c, n);
	if(this->prvni==nullptr){
		this->prvni = novy;
	}else{
		novy->setNasl(this->prvni);
		this->prvni->setPred(novy);
		this->prvni=novy;
	}
}
void Seznam::addUzelToEnd(Uzel u){
	Uzel *novy = new Uzel(u);
	novy->setCislo(u.getCislo());
	novy->setNazev(u.getNazev());
	if(this->prvni==nullptr){
		this->prvni = novy;
	}else{
		Uzel* p;
		for(p = this->getPrvni();p!=nullptr; p=p->getNasl()){
			Uzel* r = p->getNasl();
			if(r==nullptr)break;
		}
		p->setNasl(novy);
		novy->setPred(p);
	}
}
ostream &operator<<(ostream &os, Seznam  *s) {
	if (s->getPrvni() == nullptr) {
		os << "Seznam je prazdny" << endl;
	} else {
		os << "\tcislo \tnazev" << endl;
		for (Uzel* p = s->getPrvni(); p != nullptr; p = p->getNasl()) {
			os << p->getCislo() << "\t" << p->getNazev() << endl;
		}
	}
	return os;
}


double Seznam::prumer(){
	double prumer=0;
	int pocet=0;
	for(Uzel* p = this->getPrvni();p!=nullptr; p=p->getNasl()){
		prumer+=p->getCislo();
		pocet++;
	}
	return prumer/pocet;
}
Uzel* Seznam::min(){
	int min = this->getPrvni()->getCislo();
	Uzel* minUzel = this->getPrvni();
	for(Uzel* p = this->getPrvni();p!=nullptr; p=p->getNasl()){
		if(p->getCislo()<min){
			min = p->getCislo();
			minUzel = p;
		}
	}

	return minUzel;
}
Uzel* Seznam::max(){
	int max = this->getPrvni()->getCislo();
	Uzel* maxUzel = this->getPrvni();
	for(Uzel* p = this->getPrvni();p!=nullptr; p=p->getNasl()){
		if(p->getCislo()>max){
			max = p->getCislo();
			maxUzel = p;
		}
	}

	return maxUzel;
}
void Seznam::loadFromFile(){
	ifstream soubor;
	soubor.open("pivo.txt");
	if(soubor.is_open()){
		int cislo;
		string nazev;
		string cis;
		string radek;
		while(getline(soubor, radek)){
			stringstream radecek=stringstream(radek);
			getline(radecek, cis, '$');
			cislo = stoi(cis);
			getline(radecek, nazev, '$');
			Uzel u(cislo, nazev);
			this->addUzelToEnd(u);
		}
		soubor.close();
	}else{
		cout<<"Soubor se nepodarilo otevrit"<<endl;
	}

}
void Seznam::saveToFile(){
	ofstream soubor;
	soubor.open("pivo.txt");
	if(soubor.is_open()){
		for(Uzel* p = this->getPrvni();p!=nullptr; p=p->getNasl()){
			soubor<<p->getCislo()<<"$"<<p->getNazev()<<"$"<<endl;
		}
		soubor.close();
	}else{
		cout<<"Soubor se nepodarilo otevrit"<<endl;
	}
}
void Seznam::remove(Uzel *u){
	if(u==this->getPrvni()){
		this->prvni = u->getNasl();
	}else{
		Uzel* pred = u->getPred();
		Uzel* nasl = u->getNasl();
		pred->setNasl(nasl);
		if(nasl!=nullptr){
			nasl->setPred(pred);
		}
	}
	delete u;
}
void Seznam::edit(Uzel *u){
	int cislo;
	string nazev;
	cout<<"Zadejte nove cislo: ";
	cin>>cislo;
	cout<<"Zadejte novy nazev: ";
	fflush(stdin);
	getline(cin, nazev);
	u->setCislo(cislo);
	u->setNazev(nazev);
}

void Seznam::sortByNumber(){
	Uzel* p = this->getPrvni();
	Uzel* r = p->getNasl();
	while(r!=nullptr){
		if(p->getCislo()>r->getCislo()){
			Uzel* pred = p->getPred();
			Uzel* nasl = r->getNasl();
			if(pred!=nullptr){
				pred->setNasl(r);
			}else{
				this->prvni = r;
			}
			r->setPred(pred);
			r->setNasl(p);
			p->setPred(r);
			p->setNasl(nasl);
			if(nasl!=nullptr){
				nasl->setPred(p);
			}
			p = this->getPrvni();
			r = p->getNasl();
		}else{
			p = r;
			r = r->getNasl();
		}
	}
}

