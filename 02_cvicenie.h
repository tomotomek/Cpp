#include <iostream>

using namespace std;

int DUMMY_INT = -999;
string DUMMY_STRING = "";
bool DUMMY_BOOL = false;

//1. uloha
string odstranenieVsetkychVyskytovZnaku(const string &vstup, char znak) {
	int lenth = vstup.size();
	string vystup = "";

	for (int i = 0; i < lenth; i++) {
		if (vstup[i] != znak) {
			vystup += vstup[i];
		}
	}
	return vystup;
}
string odstraneniePrvehoVyskytuZnaku(const string &vstup, char znak) {
	int lenth = vstup.size();
	bool nasiel = false;
	string vystup = "";

	for (int i = 0; i < lenth; i++) {
		if (vstup[i] != znak || nasiel) {
			vystup += vstup[i];
		}
		else {
			nasiel = true;
		}
	}
	return vystup;
}
string odstranenieViacnasobnychZnakov(const string &vstup, char znak) {
	int lenth = vstup.size();
	bool nasiel = true;
	string vystup = "";

	if (lenth == 1) {
		return vstup;
	}
	for (int i = 0; i < (lenth - 1); i++) {
		if (vstup[i] != znak) {
			vystup += vstup[i];
			nasiel = true;
		}
		else if (vstup[i] == znak && vstup[i] == vstup[i + 1]) {
			if (nasiel) {
				nasiel = false;
				vystup += vstup[i];
			}
		}
		else if (i > 1 && vstup[i] == znak && vstup[i] != vstup[i + 1] && vstup[i] != vstup[i - 1]) {
			vystup += vstup[i];
		}
		else if (i == 0 && vstup[i] == znak && vstup[i] != vstup[i + 1]) {
			vystup += vstup[i];
		}
	}
	return vystup;
}

//2. uloha
bool vyskytZnaku(const string &vstup, char znak) {
	int lenth = vstup.size();

	for (int i = 0; i < lenth; i++) {
		if (vstup[i] == znak){
			return true;
		}
	}
	return false;
}
int pocetVyskytovZnaku(const string &vstup, char znak) {
	int lenth = vstup.size();
	int pocet = 0;

	for (int i = 0; i < lenth; i++) {
		if (vstup[i] == znak) {
			pocet ++;
		}
	}
	return pocet;
}
int najvacsiSuvislyVyskytZnaku(const string &vstup, char znak) {
	int lenth = vstup.size();
	int pocet = 0;
	int max = 0;

	for (int i = 0; i < lenth; i++) {
		if (vstup[i] == znak) {
			pocet++;
		}
		else {
			if (pocet > max) {
				max = pocet;
			}
			pocet = 0;
		}
	}
	if (max == 0) {
		max = pocet;
	}
	return max;
}

//3. uloha
int kontrolaPovolenychZnakov(const string &vstup, const string &povoleneZnaky) {
	int inlenth = vstup.size();
	int stlenth = povoleneZnaky.size();
	bool found = false;

	if (vstup == "") {
		return -1;
	}
	if (povoleneZnaky == "") {
		return 0;
	}
	for (int i = 0; i < inlenth; i++) {
		found = false;
		for (int j = 0; j < stlenth; j++) {
			if (vstup[i] == povoleneZnaky[j]) {
				found = true;
			}
		}
		if (!found) {
			return i;
		}
	}
	return -1;
}

//4. uloha
int najvacsiPocetVyskytovZnaku(const string &vstup) {
	int max = 0;
	bool ne = true;
	string zoznam = "";
	for (int i = 0; i < vstup.size(); i++) {
		for (int j = 0; j < zoznam.size(); j++) {
			if (vstup[i] == zoznam[j]) {
				ne = false;
			}
		}
		if (ne) {
			int pocet = pocetVyskytovZnaku(vstup, vstup[i]);
			zoznam += vstup[i];
			if (pocet > max) {
				max = pocet;
			}
		}
		ne = true;
	}
	return max;
}

//5. uloha
string vratPodretazec(const string &zdroj, char oddelovac, int poradie) {
	if (poradie < 0) return "";
	char vysl[255];
	int k = 0;
	int por = 0;
	for (unsigned int i = 0; i < zdroj.size(); i++) {
		if (zdroj[i] == oddelovac) {
			if (por < poradie) {
				por++;
			}
			else {
				vysl[k] = '\0';
				return vysl;
			}
		}
		if (por == poradie && zdroj[i] != oddelovac) {
			vysl[k] = zdroj[i];
			k++;
		}
	}
	vysl[k] = '\0';
	return vysl;
}