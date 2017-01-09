#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

//#include "riesenie9.h"

//Toto je vlozeny hlavickovy subor riesenie9.h
#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
class Vynimka {};
class ZlyVstup : public Vynimka {
	string text;
public:
	ZlyVstup(const char *v) { text = v; };
	string vypis() const { return text; };
};
//1.uloha
struct Cas {
	int hod, min, sek, mikrosek;
	string vlozenyCas = "00:00:00,000";
	Cas(const string &vstup = "");
	bool vloz(const string &cas);
	string vratVlozenyCas() const { return vlozenyCas; };
	bool skontrolujCas(int h, int m, int s, int mik) const;
	bool skontrolujCas() const;
	string vratCas() const;
	//2.uloha
	void operator+=(const Cas &posun);
	void operator-=(const Cas &posun);
	void vlozUpravene(int h, int m, int s, int mik);
};

//3.uloha
class Titulok {
	int poradie = 0; //poradove cislo titulku
	Cas zaciatok, koniec; // cas zaciatku a konca zobrazenia titulku
	string titulky[3]; //samotn0 texty titulku
	string chyba = ""; //chybov0 vynimka, ak titulok nema spravny format
	bool vlozTextChyby(const string &textChyby);
	
public:
	bool vlozPoradoveCislo(const string &cislo);
	int poradoveCisloTitulku() const { return poradie; };
	bool vlozCasy(const string &casy);
	void vlozZaciatok(const string &cas);
	void vlozKoniec(const string &cas);
	string casZaciatku() const;
	string casKonca() const;
	void vloz(const string texty[]);
	string titulok(int index) const;
	string textChyby() const { return chyba; };
	void vloz(const Titulok &vstup);
};
//4.uloha
class Element : public Titulok {
	Element *nasl;
public:
	Element() : nasl(nullptr) {};
	void nasledujuci(Element *n) { nasl = n; };
	Element *dajDalsi() const { return nasl; };
};
class VsetkyTitulky {
	Element *prvy;
	Element *aktualny;
public:
	VsetkyTitulky();
	~VsetkyTitulky();
	void vymazVsetkyTitulky();
	void vloz(const Titulok &vstup);
	Element *vratAktualny() const;
	bool nastavNaZaciatok();
	bool posunNaDalsi();
	int pocetTitulkov();
	//5.uloha
	bool nacitajZoSuboru(const string &menoSuboru);
	bool zapisDoSuboru(const string &menoSuboru);
	//5.uloha
	void operator+=(const Cas &posun);
	void operator-=(const Cas &posun);
};
#endif

const bool DUMMY_BOOL = false;
const int DUMMY_INT = 0;
const string DUMMY_STRING = "";

//Pomocne Fcie

int konverziaCharNaInt(char znak) {
	if (znak == ' ') {
		return -2;
	}
	if (znak == '-') {
		return 99;
	}
	if (znak >= '0' && znak <= '9') {
		return znak - '0';
	}
	if (znak == ':') {
		return -3;
	}
	if (znak == ',') {
		return -4;
	}
	return -99;
}

//1.uloha

Cas::Cas(const string &vstup) {
	if (vstup == "") {
		hod = 0, min = 0, sek = 0, mikrosek = 0;
		return;
	}
	vloz(vstup);
	return;
}

bool Cas::skontrolujCas() const {
	return skontrolujCas(hod, min, sek, mikrosek);
}
bool Cas::skontrolujCas(int h, int m, int s, int mik) const {
	if (h < 0 || h > 23) {
		throw ZlyVstup("Hodina je mimo povolenych hodnot");
	}
	if (m < 0 || m > 59) {
		throw ZlyVstup("Minuta je mimo povolenych hodnot");
	}
	if (s < 0 || s > 59) {
		throw ZlyVstup("Sekunda je mimo povolenych hodnot");
	}
	if (mik < 0 || mik > 999) {
		throw ZlyVstup("Mikrosekunda je mimo povolenych hodnot");
	}
	return true;
}
bool Cas::vloz(const string &cas0) {
	vlozenyCas = cas0;
	stringstream vstup(cas0);
	char o1, o2, o3;
	int h, m, s, ms;
	if (vstup >> h >> o1 >> m >> o2 >> s >> o3 >> ms) {
		if (o1 == ':' && o2 == ':' && o3 == ',') {
			if (skontrolujCas(h, m, s, ms)) {
				hod = h, min = m, sek = s, mikrosek = ms;
				return true;
			}
		}
	}
	throw ZlyVstup("Zly format casu");
}
string Cas::vratCas() const {
	stringstream vystup;
	vystup << setw(2) << setfill('0') << hod << ":" << setw(2) <<  min << ":" << setw(2) << sek << "," << setw(3) << mikrosek;
	return vystup.str();
}
//2.uloha
void Cas::operator+=(const Cas &posun) {
	Cas pripocitany = posun;
	int h = pripocitany.hod + hod;
	int m = pripocitany.min + min;
	int s = pripocitany.sek + sek;
	int ms = pripocitany.mikrosek + mikrosek;
	vlozUpravene(h, m, s, ms);
}
void Cas::operator-=(const Cas &posun) {
	Cas odpocitany = posun;
	int h = hod - odpocitany.hod;
	int m = min - odpocitany.min;
	int s = sek - odpocitany.sek;
	int ms = mikrosek - odpocitany.mikrosek;
	vlozUpravene(h, m, s, ms);
}
void Cas::vlozUpravene(int h, int m, int s, int mik) {
	if (mik > 1000 - 1) {
		mik -= 1000;
		s++;
	}
	else if (mik < 0) {
	}
	if (s < 0) { 
		s += 60;
		m--; 
	}
	else if (s > 60 - 1) {
		s -= 60;
		m++;
	}
	if (m < 0) {
		m += 60;
		h--;
	}
	else if (m > 60 - 1) {
		m -= 60;
		h++;
	}
	hod = h;
	min = m;
	sek = s;
	mikrosek = mik;
	vloz(vratCas());
}

//3.uloha
bool Titulok::vlozPoradoveCislo(const string &textPoradia) {
	int p = 0;
	for (unsigned int i = 0; i < textPoradia.size(); i++) {
		p *= 10;
		p += konverziaCharNaInt(textPoradia[i]);
		if (textPoradia[i] == '-') {
			poradie = 0;
			chyba = "Zle poradie";
			return false;
		}
	}
	if (p > 0) {
		poradie = p;
		return true;
	}
	poradie = 0;
	chyba = "Zle poradie";
	return false;
}
bool Titulok::vlozCasy(const string &casy) {
	stringstream vstup(casy);
	string zac, kon, odd;
	if (vstup >> zac >> odd >> kon) {
		if (odd == "-->") {
			try {
				vlozZaciatok(zac);
				vlozKoniec(kon);
				return true;
			}
			catch (ZlyVstup) {
				chyba = "Zle casy";
				vlozZaciatok("00:00:00,000");
				vlozKoniec("00:00:00,000");
				return false;
			}
			
		}
	}
	if (chyba == "") chyba = "Zle casy";
	return false;
}
void Titulok::vlozZaciatok(const string &cas) {
	zaciatok.vloz(cas);
}
void Titulok::vlozKoniec(const string &cas) {
	koniec.vloz(cas);
}
string Titulok::casZaciatku() const {
	return zaciatok.vlozenyCas;
};
string Titulok::casKonca() const {
	return koniec.vlozenyCas;
};
string Titulok::titulok(int index) const {
	if (index >= 0 && index < 3) {
		return titulky[index];
	}
	return "";
};
void Titulok::vloz(const string text[]) {
	for (unsigned int i = 0; i < sizeof(text)-1; i++) {
		titulky[i] = text[i];
	}	
}
bool Titulok::vlozTextChyby(const string &textChyby) {
	return DUMMY_BOOL;
}
void Titulok::vloz(const Titulok &vstup) {
}

//4.uloha
VsetkyTitulky::VsetkyTitulky() : prvy(nullptr), aktualny(nullptr) { }

VsetkyTitulky::~VsetkyTitulky() {
}
void VsetkyTitulky::vymazVsetkyTitulky() {
}
void VsetkyTitulky::vloz(const Titulok &vstup) {
}
Element *VsetkyTitulky::vratAktualny() const {
	return new Element();
}
bool VsetkyTitulky::nastavNaZaciatok() {
	return DUMMY_BOOL;
}
bool VsetkyTitulky::posunNaDalsi() {
	return DUMMY_BOOL;
}
int VsetkyTitulky::pocetTitulkov() {
	return DUMMY_INT;
}
//5.uloha
void VsetkyTitulky::operator+=(const Cas &posun) {
}
void VsetkyTitulky::operator-=(const Cas &posun) {
}

