#include <iostream>

//Uloha 1.
std::string vratText(const std::string vstup) {
	if (vstup == "") {
		return "Prazdny vstup";
	}
	else {
		return vstup;
	}
}

//Uloha 2. a 5.
int pocetVyskytov(const std::string retazec, const std::string podretazec) {
	if (retazec.size() == 0) {
		if (podretazec.size() == 0) {
			return 0;
		}
		return 0;
	}
	int pocet = 0;
	for (unsigned int i = 0; i < retazec.size(); i++) {
		if (retazec[i] == podretazec[0]) {
			bool zhoda = false;
			for (unsigned int j = 0; j < podretazec.size(); j++) {
				if (retazec[i + j] != podretazec[j]) {
					zhoda = false;
					j = podretazec.size();
				}
				else {
					zhoda = true;
				}
			}
			if (zhoda == true) {
				pocet++;
			}
		}
	}
	return pocet;
}

//Uloha 3. a 4.
bool realneCislo(const std::string cislo) {
	unsigned int i = 0;
	if (cislo == "") {
		return false;
	}

	if (cislo[cislo.size() - 1] == '-' && cislo.size() > 1) {
		return false;
	}

	if (cislo == "-.") {
		return true;
	}
	else if (cislo[cislo.size() - 1] == '.' && cislo.size() > 1) {
		return false;
	}

	while (i < cislo.size()) {
		switch (cislo[i]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
		case '-':
			break;
		default:
			return false;
		}
		if (cislo[i] == cislo[i+1] && cislo[i] == '.') {
			return false;
		}
		i++;
	}
	return true;
}

