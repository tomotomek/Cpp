#include <iostream>

using namespace std;

//#include "riesenie6.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class HOST {
	char *menoPriezvisko = nullptr;
public:
	HOST(const char *priezviskoMeno);
	HOST(HOST &&host);
	~HOST() {
		if (menoPriezvisko != nullptr) {
			delete[] menoPriezvisko;
			menoPriezvisko = nullptr;
		}
	}
	void vlozMeno(const char *priezviskoMeno);
	const char *celeMeno() const;
};
class HOTELOVA_IZBA {
	HOST zakaznik;
	bool obsadenost;
	//2.uloha
	enum typIzby { Izba, Apartman };
	bool upratana;
	typIzby typ;
	int casUpratania;
public:
	//1.uloha
	HOTELOVA_IZBA();
	~HOTELOVA_IZBA();
	bool getObsadenaIzba() const { return obsadenost; };
	bool nastahujZakaznika(const char *priezviskoMeno);
	bool vystahujZakaznika();
	const char *menoZakaznika() const;
	//2.uloha
	void nastavTypIzby(const char *typ, unsigned int cas);
	const char *getTypIzby() const;
	bool getUpratana() const;
	int upratanie();
};
//3.uloha
class HOTEL {
	int pocetPoschodi;
	int pocetIziebNaPoschodi;
	HOTELOVA_IZBA **izby;
public:
	HOTEL(int poschodia, int izby);
	~HOTEL();
	int pocetVsetkychIzieb() const;
	int pocetIzieb(const char *typ) const;
	int pocetVolnychIzieb(const char *typ) const;
	//4.uloha
	bool ubytujHosta(const char *priezviskoMeno, const char *typIzby);
	char *zoznamHosti(char *menaHosti) const;
	//5.uloha
	bool odhlasHosta(const char *priezviskoMeno);
	int upratanieVsetkychIzieb();
};
#endif

const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";
const int DUMMY_INT = -1;

//1.uloha
HOST::HOST(const char *priezviskoMeno) {
	vlozMeno(priezviskoMeno);
}
void HOST::vlozMeno(const char *priezviskoMeno) {
	if (priezviskoMeno == nullptr) {
		menoPriezvisko = nullptr;
	}
	else {
		char *vysl = new char[255];
		bool ciarka = false, bolP = false, bolM = false;
		int lenth = strlen(priezviskoMeno), j = 0, k = 0;
		char *meno = new char[255];
		char *priezvisko = new char[255];
		for (int i = 0; i < lenth; i++) {

			if (*priezviskoMeno != ',' && !ciarka) {
				bolP = true;
				priezvisko[j] = *priezviskoMeno;
				j++;
				priezvisko[j] = '\0';
			}
			else if (*priezviskoMeno == ',') {
				ciarka = true;
			}
			else if (*priezviskoMeno != ',' && ciarka) {
				bolM = true;
				meno[k] = *priezviskoMeno;
				k++;
				meno[k] = '\0';
			}

			priezviskoMeno++;
		}
		if (!bolP || !bolM) {
			menoPriezvisko = nullptr;
		}
		else {
			int lenthP = j;
			int lenthM = k;
			j = 0;
			k = 0;
			for (int i = 0; i < lenth; i++) {
				if (k < lenthM) {
					vysl[i] = meno[k];
					k++;
					vysl[i + 1] = ' ';
				}
				else if (j < lenthP) {
					vysl[i + 1] = priezvisko[j];
					j++;
					vysl[i + 2] = '\0';
				}
			}
			menoPriezvisko = vysl;
		}
	}
}
HOST::HOST(HOST &&host) {
	if (this != &host) {
		menoPriezvisko = host.menoPriezvisko;
		host.menoPriezvisko = nullptr;
	}
}
const char *HOST::celeMeno() const {
	if (menoPriezvisko == nullptr) {
		return "nezadane";
	}
	return menoPriezvisko;
}


HOTELOVA_IZBA::HOTELOVA_IZBA() : zakaznik(nullptr) {
	obsadenost = false;
	upratana = true;
	typ = Izba;
	casUpratania = 20;
}
HOTELOVA_IZBA::~HOTELOVA_IZBA() {
}
bool HOTELOVA_IZBA::nastahujZakaznika(const char *priezviskoMeno) {
	zakaznik.vlozMeno(priezviskoMeno);
	auto m = zakaznik.celeMeno();
	if (!obsadenost && m != "nezadane" && upratana) {
		obsadenost = true;
		upratana = false;
		return true;
	}
	return false;
}
const char *HOTELOVA_IZBA::menoZakaznika() const {
	if (zakaznik.celeMeno() != "nezadane") {
		return zakaznik.celeMeno();
	}
	return "";
}
bool HOTELOVA_IZBA::vystahujZakaznika() {
	if (obsadenost) {
		zakaznik.vlozMeno(nullptr);
		obsadenost = false;
		upratana = false;
		return true;
	}
	return false;
}
//2.uloha
bool HOTELOVA_IZBA::getUpratana()  const {
	return upratana;
}
int HOTELOVA_IZBA::upratanie() {
	if (upratana || obsadenost) {
		return 0;
	}
	upratana = true;
	return casUpratania;
}
const char * HOTELOVA_IZBA::getTypIzby() const {
	if (typ == Apartman) {
		return "Apartman";
	}
	return "Izba";
}
void HOTELOVA_IZBA::nastavTypIzby(const char *typIzby, unsigned int cas) {
	if (typIzby == "Apartman") {
		typ = Apartman;
		casUpratania = cas;
	}
	else {
		typ = Izba;
		casUpratania = cas;
	}
}
//3.uloha
HOTEL::HOTEL(int poschodia, int pocetIzieb) {
	if (poschodia < 1 || pocetIzieb < 1) {
		pocetPoschodi = 0;
		pocetIziebNaPoschodi = 0;
	}
	else {
		pocetPoschodi = poschodia;
		pocetIziebNaPoschodi = pocetIzieb;
		izby = new HOTELOVA_IZBA*[poschodia];
		for (unsigned int i = 0; i < poschodia; i++) {
			izby[i] = new HOTELOVA_IZBA[pocetIzieb];
		}
		for (unsigned int i = 0; i < poschodia; i++) {
			for (unsigned int j = 0; j < pocetIzieb; j++) {
				if (j % 3 == 2) {
					izby[i][j].nastavTypIzby("Apartman", 30);
				}
			}
		}
	}
}
HOTEL::~HOTEL() {
	if (izby == nullptr) {
		for (unsigned int i = 0; i < pocetPoschodi; i++) {
			delete[] izby[i];
		}
		delete[] izby;
	}
}
int HOTEL::pocetVsetkychIzieb() const {
	return pocetPoschodi * pocetIziebNaPoschodi;
}
int HOTEL::pocetIzieb(const char *typ) const {
	int pocet = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (izby[i][j].getTypIzby() == typ) {
				pocet++;
			}
		}
	}
	return pocet;
}
int HOTEL::pocetVolnychIzieb(const char *typ) const {
	int pocet = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (izby[i][j].getTypIzby() == typ && !izby[i][j].getObsadenaIzba()) {
				pocet++;
			}
		}
	}
	return pocet;
}
//4.uloha

bool HOTEL::ubytujHosta(const char *priezviskoMeno, const char *typ) {
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (izby[i][j].getTypIzby() == typ && !izby[i][j].getObsadenaIzba() && izby[i][j].getUpratana()) {
				izby[i][j].nastahujZakaznika(priezviskoMeno);
				return true;
			}
		}
	}
	
	return false;
}
char *HOTEL::zoznamHosti(char *menaHosti) const {
	if (menaHosti == nullptr) {
		return "";
	}
	menaHosti[0] = '\0';
	int pocetObsadenych = 0, zaznacene = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (izby[i][j].getObsadenaIzba()) {
				pocetObsadenych++;
			}
		}
	}
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (izby[i][j].getObsadenaIzba()) {
				if (zaznacene == pocetObsadenych-1) {
					strcat(menaHosti, izby[i][j].menoZakaznika());
				}
				else {
					strcat(menaHosti, izby[i][j].menoZakaznika());
					strcat(menaHosti, ", ");
					zaznacene++;
				}
			}
		}
	}
	return menaHosti;
}

//5.uloha
bool HOTEL::odhlasHosta(const char *priezviskoMeno) {
	HOST odchadza(priezviskoMeno);
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			string tmp = { odchadza.celeMeno() };
			if (izby[i][j].menoZakaznika() == tmp) {
				izby[i][j].vystahujZakaznika();
			}
		}
	}
	return false;
}
int HOTEL::upratanieVsetkychIzieb() {
	int casUpratania = 0;
	for (unsigned int i = 0; i < pocetPoschodi; i++) {
		for (unsigned int j = 0; j < pocetIziebNaPoschodi; j++) {
			if (!izby[i][j].getUpratana() && !izby[i][j].getObsadenaIzba()) {
				casUpratania += izby[i][j].upratanie();
			}
		}
	}
	return casUpratania;
}
