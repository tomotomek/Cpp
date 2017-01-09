#include <iostream>
#include <typeinfo>
using namespace std;

const int DUMMY_INT = -999;
const char DUMMY_CHAR = 'X';
const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";

const int ZLE_CISLO = -9999;
const int MIN_SUSTAVA = 2;
const int MAX_SUSTAVA = 16;

//1. uloha
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
	int lenth = vstup.size();
	int pocet = 0;
	if (sustava < MIN_SUSTAVA || sustava > MAX_SUSTAVA || vstup == "" || vstup == "-") {
		return false;
	}
	for (int i = 0; i < lenth; i++) {
		int number = konverziaCharNaInt(vstup[i]);
		if (number == -2) {
			pocet++;
			if (pocet == lenth) {
				return false;
			}
		}
		if (number >= sustava) {
			return false;
		}
		if (vstup[i] != ' ' && vstup[i + 1] == '-') {
			return false;
		}

	}
	return true;
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
			printf("mocnina = %d; cislo = %d\n", mocnina, number);
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



