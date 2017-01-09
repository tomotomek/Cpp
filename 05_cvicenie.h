#include <iostream>

using namespace std;

//#include "riesenie5.h"

#ifndef _RIESENIE_H_
#define _RIESENIE_H_

//1. uloha
int pocetVsetkychSlov(char *retazec);
//2. uloha
char *odSlova(char *retazec, int poradie);
//3. uloha
char *vratSlovoVPoradi(char *retazec, char *vystup, int poradie);
//4. uloha
char *vratPrveSlovoPodlaUsporiadania(char *retazec, char *vystup);
//5. uloha
char *zoznamVybranychSlov(char *retazec, char *vystup, const int zoznam[], int pocet);

#endif

int DUMMY_INT = -999;
bool DUMMY_BOOL = false;
string DUMMY_STRING = "";
char DUMMY_CHARS[] = "";

bool jeOddelovac(char znak) {
	if (znak == ' ') {
		return true;
	}
	if (znak == '.') {
		return true;
	}
	if (znak == ',') {
		return true;
	}
	if (znak == ';') {
		return true;
	}
	if (znak == '?') {
		return true;
	}
	if (znak == '!') {
		return true;
	}
	if (znak == ':') {
		return true;
	}
	if (znak == '-') {
		return true;
	}
	return false;
}

//1. uloha
int pocetVsetkychSlov(char *retazec) {
	char *a = retazec;
	bool bol = false, oddelovac = true;
	int pocetSlov = 0;
	if (retazec == nullptr) {
		return -1;
	}
	while (*a != '\0') {
		if (jeOddelovac(*a)) {
			oddelovac = false;
			if (bol) {
				pocetSlov++;
				bol = false;
			}
		}
		else {
			bol = true;
			oddelovac = true;
		}
		a++;
	}
	if (oddelovac && bol) {
		pocetSlov++;
	}
	return pocetSlov;
}

//2. uloha
char *odSlova(char *retazec, int poradie) {
	if (retazec == nullptr || poradie < 0) {
		return "";
	}
	int vsetkySlova = pocetVsetkychSlov(retazec);
	if (poradie >= vsetkySlova) {
		return "";
	}
	char *a = retazec;
	bool bol = false, oddelovac = true;
	int indexSlova = 0;
	while (indexSlova < poradie) {
		if (jeOddelovac(*a)) {
			oddelovac = false;
			if (bol) {
				indexSlova++;
				bol = false;
			}
		}
		else {
			bol = true;
			oddelovac = true;
		}
		if (indexSlova == poradie) {
			while (jeOddelovac(*a)) {
				a++;
			}
			return a;
		}
		a++;
	}
	if (poradie == 0) {
		while (jeOddelovac(*a)) {
			a++;
		}
	}
	return a;
}

//3. uloha
char *vratSlovoVPoradi(char *retazec, char *vystup, int poradie) {
	int vsetkySlova = pocetVsetkychSlov(retazec);
	if (retazec == nullptr || poradie < 0 || poradie >= vsetkySlova) {
		vystup = new char[1];
		*vystup = '\0';
		return vystup;
	}
	int pocet = 0, j = 0;
	vystup = new char[255];
	char *pomoc = new char[255];
	strcpy(vystup, odSlova(retazec, poradie));
 	for (int i = 0; i < strlen(vystup); i++) {
		if (jeOddelovac(vystup[i])) {
			pocet++;
		}
		if (!jeOddelovac(vystup[i]) && pocet < 1) {
			pomoc[j] = vystup[i];
			pomoc[j + 1] = '\0';
			j++;
		}
	}
	return pomoc;
}

//4.uloha
char *vratPrveSlovoPodlaUsporiadania(char *retazec, char *vystup) {
	if (retazec == nullptr || retazec == "") {
		vystup = new char[1];
		*vystup = '\0';
		return vystup;
	}
	char *max = vratSlovoVPoradi(retazec, vystup, 0);
	char *slovo = new char[255];
	int pocetSlov = pocetVsetkychSlov(retazec);
	for (unsigned int i = 1; i < pocetSlov; i++) {
		slovo = vratSlovoVPoradi(retazec, vystup, i);
		if (*max > *slovo) {
			max = slovo;
		}
		if (*max == *slovo) {
			if (strlen(slovo) < strlen(max)) {
				max = slovo;
			}
		}
	}
	return max;
}

//5.uloha
char *zoznamVybranychSlov(char *retazec, char *vystup, const int zoznam[], int pocet) {
	if (retazec == nullptr || retazec == "") {
		vystup = new char[1];
		*vystup = '\0';
		return vystup;
	}
	vystup = new char[255];
	*vystup = '\0';
	char *slovo = new char[255];
	for (unsigned int i = 0; i < pocet; i++) {
		slovo = vratSlovoVPoradi(retazec, vystup, zoznam[i]);
		if (i < pocet - 1) {
			strcat(vystup, slovo);
			strcat(vystup, ",");
		}
		else {
			strcat(vystup, slovo);
		}
	}
	return vystup;
}