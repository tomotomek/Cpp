#include <iostream>

using namespace std;

//#include "riesenie4.h"

#ifndef _RIESENIE_H_
#define _RIESENIE_H_

//1. uloha
class CISLO {
	int hodnota;
	void vloz(int cislo);
protected:
	int vratHodnotu() const;
public:
	bool vloz(const string &cislo);
	void vloz(const CISLO &cislo);
	string vratCislo() const;
};
//2. uloha
class CISLO_V_SUSTAVE : public CISLO {
	int sustava = 10;
public:
	bool vlozSustavu(int sustava0);
	int vratSustavu() const;
	bool vlozCisloVSustave(const string &cislo0);
	void vlozCisloVSustave(const CISLO_V_SUSTAVE &cislo);
	string vratCisloVSustave() const;
};
//3. uloha
class KALKULACKA {
public:
	string vypocitaj(const string &op1, char operator0, const string  &op2);
	string vypocitaj(const CISLO &op1, char operator0, const CISLO &op2);
};
//4. uloha
class KALKULACKA_V_SUSTAVE : public KALKULACKA {
	int sustava = 10;
public:
	bool vlozSustavu(int sustava0);
	int vratSustavu() const;
	string vypocitajVSustave(const string &op1, char operator0, const string &op2);
	//5. uloha
	string vypocitajVyraz(const string &vyrazVSustave);
};

const int ZLE_CISLO = -9999;
const string zleCislo = "Zle cislo";

#endif

const int DUMMY_INT = -99;
const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";

//Pomocne fcie
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

//2. uloha
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
	if (uz_bolo_cislo) {
		return true;
	}
	else {
		return false;
	}
}

string BezMedzery(const string &vstup) {
	string vystup = "";
	for (int i = 0; i < vstup.size(); i++) {
		if (vstup[i] != ' ') {
			vystup += vstup[i];
		}
	}
	return vystup;
}

//3. uloha
int konverziaCislaZoSustavyNaInt(const string &vstup, int sustava) {
	string retazec = BezMedzery(vstup);
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
}
//4. uloha
string desiatkoveCisloNaDesiatkovyString(int desiatkoveCislo) {
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
string konverziaDesiatkovehoCislaDoSustavy(int desiatkoveCislo, int sustava) {
	if (sustava < 2 || sustava > 16) {
		return "Nepovolena sustava";
	}

	if (desiatkoveCislo == 0) {
		return "0";
	}

	int cislo = abs(desiatkoveCislo);


	string vysledok = "";
	string medzi_vysledok = "";
	if (desiatkoveCislo < 0) {
		vysledok = "-";
	}

	while (cislo > 0) {
		medzi_vysledok += konverziaIntNaChar(cislo % sustava);
		cislo = cislo / sustava;
	}

	for (int i = medzi_vysledok.size() - 1; i >= 0; i--) {
		vysledok += medzi_vysledok[i];
	}

	return vysledok;
}
//5. uloha
string konverziaZoSustavyDoSustavy(const string &vstup, int vstupnaSustava, int vystupnaSustava) {
	if (vstupnaSustava < 2 || vstupnaSustava > 16) {
		return "Nepovolena sustava";
	}
	if (vystupnaSustava < 2 || vystupnaSustava > 16) {
		return "Nepovolena sustava";
	}
	if (!spravnostCislaVSustave(vstup, vstupnaSustava)) {
		return "Zle vstupne cislo";
	}

	int cislo = 0;
	string vystup = "";
	cislo = konverziaCislaZoSustavyNaInt(vstup, vstupnaSustava);
	vystup = konverziaDesiatkovehoCislaDoSustavy(cislo, vystupnaSustava);
	return vystup;
}

//1. uloha
void CISLO::vloz(int cislo) {
	hodnota = cislo;
}
void CISLO::vloz(const CISLO &cislo) {
	string i = cislo.vratCislo();
	CISLO::hodnota = konverziaCislaZoSustavyNaInt(i, 10);
}
bool CISLO::vloz(const string &cislo) {

	if (spravnostCislaVSustave(cislo, 10)) {
		int i = konverziaCislaZoSustavyNaInt(cislo, 10);
		CISLO::vloz(i);
		return true;
	}
	else {
		CISLO::vloz(-9999);
		return false;
	}
}
int CISLO::vratHodnotu() const {
	return CISLO::hodnota;

}
string CISLO::vratCislo() const {
	string i = desiatkoveCisloNaDesiatkovyString(CISLO::hodnota);
	if (i == "-9999") {
		return "Zle cislo";
	}
	return i;
}

//2. uloha
bool CISLO_V_SUSTAVE::vlozSustavu(int sustava0) {
if (sustava0 >= 2 && sustava0 <= 18) {
	CISLO_V_SUSTAVE::sustava = sustava0;
	return true;
}
return false;

}
int CISLO_V_SUSTAVE::vratSustavu() const {
	return CISLO_V_SUSTAVE::sustava;
}
bool CISLO_V_SUSTAVE::vlozCisloVSustave(const string &cislo0) {
	if (spravnostCislaVSustave(cislo0, CISLO_V_SUSTAVE::sustava)) {
		int i = konverziaCislaZoSustavyNaInt(cislo0, CISLO_V_SUSTAVE::sustava);
		string m = konverziaDesiatkovehoCislaDoSustavy(i, 10);
		CISLO_V_SUSTAVE::vloz(m);
		return true;
	}
	CISLO_V_SUSTAVE::vloz("-9999");
	return false;
}
void CISLO_V_SUSTAVE::vlozCisloVSustave(const CISLO_V_SUSTAVE &cislo) {
	string i = cislo.vratCislo();
	int n = konverziaCislaZoSustavyNaInt(i, 10);
	CISLO_V_SUSTAVE::vloz(i);

}
string CISLO_V_SUSTAVE::vratCisloVSustave() const {
	int i = CISLO_V_SUSTAVE::vratSustavu();
	string m = CISLO_V_SUSTAVE::vratCislo();
	int n = konverziaCislaZoSustavyNaInt(m, 10);
	return konverziaDesiatkovehoCislaDoSustavy(n, i);

}
//3. uloha
string KALKULACKA::vypocitaj(const string &op1, char operator0, const string  &op2) {
	if (spravnostCislaVSustave(op1, 10) == false) {
		return "Zly operand 1";
	}
	if (spravnostCislaVSustave(op2, 10) == false) {
		return "Zly operand 2";
	}

	if (operator0 != '+' && operator0 != '-' && operator0 != '*' && operator0 != '/' && operator0 != '%') {
		return "Neznamy operator";
	}
	int n = konverziaCislaZoSustavyNaInt(op1, 10);
	int m = konverziaCislaZoSustavyNaInt(op2, 10);

	switch (operator0)
	{
	case '+':
		return konverziaDesiatkovehoCislaDoSustavy(n + m, 10);
	case '-':
		return konverziaDesiatkovehoCislaDoSustavy(n - m, 10);
	case '*':
		return konverziaDesiatkovehoCislaDoSustavy(n * m, 10);
	case '/':
		if (m == 0) {
			return "Delenie nulou";
		}
		return konverziaDesiatkovehoCislaDoSustavy(n / m, 10);
	case '%':
		return konverziaDesiatkovehoCislaDoSustavy(n % m, 10);

	default:
		break;
	}
}
string KALKULACKA::vypocitaj(const CISLO &op1, char operator0, const CISLO &op2) {
	string n = op1.vratCislo();
	string m = op2.vratCislo();
	if (spravnostCislaVSustave(n, 10) == false) {
		return "Zly operand 1";
	}
	if (spravnostCislaVSustave(m, 10) == false) {
		return "Zly operand 2";
	}
	return KALKULACKA::vypocitaj(n, operator0, m);
}
//4. uloha
bool KALKULACKA_V_SUSTAVE::vlozSustavu(int sustava0) {
	if (sustava0 >= 2 && sustava0 <= 16) {
		sustava = sustava0;
		return true;
	}
	return false;
}
int KALKULACKA_V_SUSTAVE::vratSustavu() const {
	return sustava;
}
string KALKULACKA_V_SUSTAVE::vypocitajVSustave(const string &op1, char operator0, const string &op2) {
	if (!spravnostCislaVSustave(op1, sustava)) {
		return "Zly operand 1";
	}
	if (!spravnostCislaVSustave(op2, sustava)) {
		return "Zly operand 2";
	}
	string operatory = "+-*/%";
	bool nachadza = false;
	for (unsigned int i = 0; i < operatory.size(); i++) {
		if (operatory[i] == operator0){
			nachadza = true;
		}
	}
	if (!nachadza) {
		return "Neznamy operator";
	}
	int n = konverziaCislaZoSustavyNaInt(op1, sustava);
	int m = konverziaCislaZoSustavyNaInt(op2, sustava);
	
	switch (operator0)
	{
	case '+':
		return konverziaDesiatkovehoCislaDoSustavy(n + m, sustava);
	case '-':
		return konverziaDesiatkovehoCislaDoSustavy(n - m, sustava);
	case '*':
		return konverziaDesiatkovehoCislaDoSustavy(n * m, sustava);
	case '/':
		if (m == 0) {
			return "Delenie nulou";
		}
		return konverziaDesiatkovehoCislaDoSustavy(n / m, sustava);
	case '%':
		return konverziaDesiatkovehoCislaDoSustavy(n % m, sustava);

	default:
		break;
	}
}
//5. uloha
string KALKULACKA_V_SUSTAVE::vypocitajVyraz(const string &vyraz) {
	string c1 = "";
	string c2 = "";
	char op[1];
	int medzera = 0;
	for (unsigned int i = 0; i < vyraz.size(); i++) {
		if (medzera == 0 && vyraz[i] != ' ') {
			c1 += vyraz[i];
		}
		else if (medzera == 1 && vyraz[i] != ' ') {
			op[0] = vyraz[i];
		}
		else if (medzera == 2 && vyraz[i] != ' ') {
			c2 += vyraz[i];
		}
		else if (vyraz[i] == ' ') {
			medzera++;
		}
	}
	return vypocitajVSustave(c1, *op, c2);
}
