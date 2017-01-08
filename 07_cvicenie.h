#include <iostream>

using namespace std;

//#include "riesenie7.h"

//Toto je vlozeny hlavickovy subor riesenie7.h
#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class VELMI_VELKE_CISLO {
	string cislo;
public:
	VELMI_VELKE_CISLO(const string &vstup = "0");
	void vloz(const string &vstup);
	string value() const;
	int velkost() const;
	bool zaporneCislo() const;
	//2.uloha
	VELMI_VELKE_CISLO(long long l);
	VELMI_VELKE_CISLO(const VELMI_VELKE_CISLO &vstup);
	VELMI_VELKE_CISLO &operator=(const VELMI_VELKE_CISLO &vstup);
	VELMI_VELKE_CISLO &operator=(const string &vstup);
	//3.uloha
	bool operator==(const VELMI_VELKE_CISLO &vstup) const;
	bool operator==(const string &vstup) const;
	bool operator<(const VELMI_VELKE_CISLO &vstup) const;
	bool operator<(const string &vstup) const;
	//4.uloha
	void zmenZnamienko();
	//5.uloha
	const VELMI_VELKE_CISLO operator*(const VELMI_VELKE_CISLO &vstup);
};
//4.uloha
const VELMI_VELKE_CISLO operator+(const VELMI_VELKE_CISLO &vstup, const VELMI_VELKE_CISLO &vstup1);
const VELMI_VELKE_CISLO operator-(const VELMI_VELKE_CISLO &vstup, const VELMI_VELKE_CISLO &vstup1);
#endif

const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";

//Pomocne fcie
char konverziaIntNaChar(int cislo) {
	if (cislo == -2) {
		return ' ';
	}
	if (cislo == -1) {
		return '-';
	}
	if (cislo >= 0 && cislo <= 9) {
		return cislo + '0';
	}
	if (cislo == 10) {
		return 'A';
	}
	if (cislo == 11) {
		return 'B';
	}
	if (cislo == 12) {
		return 'C';
	}
	if (cislo == 13) {
		return 'D';
	}
	if (cislo == 14) {
		return 'E';
	}
	if (cislo == 15) {
		return 'F';
	}
	return 'Z';
}

string desiatkoveCisloNaDesiatkovyString(long long desiatkoveCislo) {
	if (desiatkoveCislo == 0) {
		return "0";
	}
	int cislo = abs(desiatkoveCislo);
	string new_cislo = "";

	while (cislo != 0) {
		new_cislo += konverziaIntNaChar(cislo % 10);
		cislo /= 10;
	}
	string final_number = "";
	if (desiatkoveCislo < 0) {
		final_number = "-";
	}

	for (int n = new_cislo.size() - 1; n >= 0; n--) {
		final_number += new_cislo[n];
	}
	return final_number;
}

int konverziaCharNaInt(char znak) {
	if (znak == ' ') {
		return -2;
	}
	if (znak == '-') {
		return -1;
	}
	if (znak >= '0' && znak <= '9') {
		return znak - '0';
	}
	if (znak == 'A' || znak == 'a') {
		return 10;
	}
	if (znak == 'B' || znak == 'b') {
		return 11;
	}
	if (znak == 'C' || znak == 'c') {
		return 12;
	}
	if (znak == 'D' || znak == 'd') {
		return 13;
	}
	if (znak == 'E' || znak == 'e') {
		return 14;
	}
	if (znak == 'F' || znak == 'f') {
		return 15;
	}
	return -99;
}

bool spravnostCislaVSustave(const string &vstup, int sustava) {
	int uz_bolo_cislo = 0;

	if (sustava > 16 || sustava < 2) {
		return false;
	}
	for (int i = 0; i < vstup.size(); i++) {
		int ibacisla = 0;
		if (vstup[i] == ' ') {
			continue;
		}

		if ((uz_bolo_cislo == 0) && (vstup[i] == '-')) {
			continue;
		}
		uz_bolo_cislo = 1;
		if (vstup[i] == '-') {
			return false;
		}
		int cislo = konverziaCharNaInt(vstup[i]);
		for (int x = 0; x < sustava; x++) {

			if (cislo == x) {
				ibacisla = 1;
				break;
			}
		}
		if (ibacisla == 0) {
			return false;
		}
	}
	return (uz_bolo_cislo);
}

/*int konverziaCislaZoSustavyNaInt(const string &vstup, int sustava = 10) {
	string retazec = vstup;
	int suma = 0;
	bool zaporne = false;
	int lenth = retazec.size();
	bool spravnost = spravnostCislaVSustave(vstup, sustava);
	if (!spravnost) {
		return -9999;
	}
	for (int i = 0; i < lenth; i++) {
		int number = konverziaCharNaInt(retazec[i]);
		if (retazec[i] == '-') {
			zaporne = true;
		}
		else {
			int mocnina = lenth - (i + 1);
			//printf("mocnina = %d; cislo = %d\n", mocnina, number);
			number = number * pow(sustava, mocnina);
			suma += number;
		}
	}
	if (zaporne) {
		return -suma;
	}
	return suma;
}*/

//1.uloha
VELMI_VELKE_CISLO::VELMI_VELKE_CISLO(const string &vstup) {
	vloz(vstup);
}
void VELMI_VELKE_CISLO::vloz(const string &vstup) {
	string VelkeCislo = "";
	bool boloCislo = false, zleCislo = false;
	for (int i = 0; i < vstup.size(); i++) {
		if (vstup[i] != ' ') {
			if (vstup[i] != '0' && vstup[i] != '-') {
				boloCislo = true;
			}
			if (boloCislo || vstup[i] == '-') {
				VelkeCislo += vstup[i];
			}
			if ((vstup[i] < '0' || vstup[i] > '9') && vstup[i] != '-') {
				zleCislo = true;
			}
		}
	}
	if (!boloCislo || zleCislo) {
		VelkeCislo = '0';
	}
	cislo = VelkeCislo;
}
string VELMI_VELKE_CISLO::value() const {
	return cislo;
}
int VELMI_VELKE_CISLO::velkost() const {
	return cislo.size();
}
bool VELMI_VELKE_CISLO::zaporneCislo() const {
	return (cislo[0] == '-');
}
//2.uloha
VELMI_VELKE_CISLO::VELMI_VELKE_CISLO(long long cislo0) {
	string vysl = desiatkoveCisloNaDesiatkovyString(cislo0);
	cislo = vysl;
}
VELMI_VELKE_CISLO::VELMI_VELKE_CISLO(const VELMI_VELKE_CISLO &vstup) {
	string newCislo = vstup.cislo;
	cislo = newCislo;
}
VELMI_VELKE_CISLO & VELMI_VELKE_CISLO::operator=(const VELMI_VELKE_CISLO &vstup) {
	string newCislo = vstup.cislo;
	cislo = newCislo;
	return *this;
}
VELMI_VELKE_CISLO & VELMI_VELKE_CISLO::operator=(const string &vstup) {
	cislo = vstup;
	return *this;
}
//3.uloha
bool VELMI_VELKE_CISLO::operator==(const VELMI_VELKE_CISLO &vstup) const {
	return (cislo == vstup.cislo);
}
bool VELMI_VELKE_CISLO::operator==(const string &c) const {
	return (cislo == c);
}
bool VELMI_VELKE_CISLO::operator<(const VELMI_VELKE_CISLO &vstup) const {
	return (cislo < vstup.cislo);
}
bool VELMI_VELKE_CISLO::operator<(const string &c) const {
	return (cislo > c);
}
//4.uloha
const VELMI_VELKE_CISLO operator+(const VELMI_VELKE_CISLO &vstup, const VELMI_VELKE_CISLO &vstup1) {
	VELMI_VELKE_CISLO c, x;
	string cislo1 = vstup.value();
	string cislo2 = vstup1.value();
	string vysl = "", vysl2 = "";
	//cout << "TOTO JE OPERATOR +" << endl;
	if (vstup.zaporneCislo() && !vstup1.zaporneCislo()) {
		for (unsigned int i = 1; i < cislo1.size(); i++) {
			vysl += cislo1[i];
		}
		x.vloz(vysl);
		c = vstup1 - x;
	}
	else if(!vstup.zaporneCislo() && vstup1.zaporneCislo()){
		for (unsigned int i = 1; i < cislo2.size(); i++) {
			vysl += cislo2[i];
		}
		x.vloz(vysl);
		c = vstup - x;
	}
	else {
		int zaklad = 0, zvysok = 0, prenos = 0, a = 0, b = 0;
		if (cislo1.size() < cislo2.size()) {
			cislo1 = vstup1.value();
			cislo2 = vstup.value();
		}
		int lenth2 = cislo2.size() - 1;
		for (int i = cislo1.size() - 1; i >= 0; i--) {
			if (lenth2 >= 0 && cislo2[lenth2] != '-') {
				a = konverziaCharNaInt(cislo1[i]);
				b = konverziaCharNaInt(cislo2[lenth2]);
				zaklad = a + b + prenos;
				zvysok = zaklad % 10;
				prenos = zaklad / 10;
				vysl += konverziaIntNaChar(zvysok);
				lenth2--;
			}
			else {
				a = konverziaCharNaInt(cislo1[i]);
				zaklad = a + prenos;
				zvysok = zaklad % 10;
				prenos = zaklad / 10;
				vysl += konverziaIntNaChar(zvysok);
			}
		}
		if (prenos) {
			vysl += "1";
		}
		for (int i = vysl.size() - 1; i >= 0; i--) {
			vysl2 += vysl[i];
		}
		c.vloz(vysl2);
	}
	return c.value();
}
const VELMI_VELKE_CISLO operator-(const VELMI_VELKE_CISLO &vstup, const VELMI_VELKE_CISLO &vstup1) {
	VELMI_VELKE_CISLO c, x;
	string cislo1 = vstup.value();
	string cislo2 = vstup1.value();
	string vysl = "", vysl2 = "", pom = "";
	int zaklad = 0, zvysok = 0, prenos = 0, a = 0, b = 0;
	bool vymena = false;
	//cout << "TOTO JE OPERATOR -" << endl;
	if (cislo2 == "0") {
		c.vloz(cislo1);
		return c.value();
	}
	if (vstup.zaporneCislo() && vstup1.zaporneCislo()) {
		if (vstup1 < vstup) vymena = true;
		for (int k = 1; k < cislo1.size(); k++) {
			pom += cislo1[k];
		}
		cislo1 = pom;
		pom = "";
		for (int k = 1; k < cislo2.size(); k++) {
			pom += cislo2[k];
		}
		cislo2 = pom;
		pom = "";
	}
	if (vstup.zaporneCislo() && !vstup1.zaporneCislo()) {
		for (unsigned int i = 1; i < cislo1.size(); i++) {
			vysl += cislo1[i];
		}
		x.vloz(vysl);
		c = x + vstup1;
		pom = c.value();
		vysl2 += "-";
		for (unsigned int i = 0; i < pom.size(); i++) {
			vysl2 += pom[i];
		}
		c.vloz(vysl2);
		return c.value();
	}
	
	if (cislo1.size() < cislo2.size()) {
		vymena = true;
		cislo1 = vstup1.value();
		cislo2 = vstup.value();
		if (cislo1[0] == '-') {
			for (int k = 1; k < cislo1.size(); k++) {
				vymena = false;
				pom+=cislo1[k];
			}
			cislo1 = pom;
			pom = "";
		}
	}
	int lenth2 = cislo2.size() - 1;
	for (int i = cislo1.size() - 1; i >= 0; i--) {
		if (lenth2 >= 0) {
			a = konverziaCharNaInt(cislo1[i]);
			b = konverziaCharNaInt(cislo2[lenth2]);
			zaklad = a - b - prenos;
			if (zaklad == -1) {
				zaklad = 9;
				prenos = 1;
			}
			else {
				prenos = 0;
			}
			zvysok = zaklad % 10;
			vysl += konverziaIntNaChar(zvysok);
			lenth2--;
		}
		else {
			a = konverziaCharNaInt(cislo1[i]);
			zaklad = a - prenos;
			if (zaklad == -1) {
				zaklad = 9;
				prenos = 1;
			}
			else {
				prenos = 0;
			}
			zvysok = zaklad % 10;
			vysl += konverziaIntNaChar(zvysok);
		}
	}
	if (vymena) {
		vysl2 += "-";
	}
	for (int i = vysl.size() - 1; i >= 0; i--) {
		vysl2 += vysl[i];
	}
	c.vloz(vysl2);
	return c.value();
}

//5.uloha
const VELMI_VELKE_CISLO VELMI_VELKE_CISLO::operator*(const VELMI_VELKE_CISLO &vstup) {
	VELMI_VELKE_CISLO d;
	return d;
}



