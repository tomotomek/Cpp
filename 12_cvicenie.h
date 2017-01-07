#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

//#include "riesenie12.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class Listok {
	int obsadenost = 0; //0 - volny, 1 - rezervovany, 2 - predany
	string meno;
public:
	bool jeVolny() const { return obsadenost == 0; };
	bool jeRezervovany() const { return obsadenost == 1; };
	bool jePredany() const { return obsadenost == 2; };
	bool kupit();
	bool uvolnit();
	bool rezervovatNaMeno(const string &menoRezervacie);
	string menoRezervacie() const { return meno; };
	bool kupitRezervovany(const string &meno);
};
//2.uloha
class Koncert {
	vector<Listok> listky;
public:
	Koncert(int pocetListkov = 0);
	int pocetVsetkychListkov() const;
	int pocetVolnychListkov() const;
	int pocetRezervacii() const;
	int pocetPredanychListkov() const;
	bool kupitListky(int pocet);
	bool rezervovatListky(int pocet, const string &meno);
	//3.uloha
	int kupitRezervovane(const string &meno);
	int zrusitRezervaciu(const string &meno);
	bool zrusitVsetkyRezervacie();
	//4.uloha
};
#endif

const int DUMMY_INT = -1;
const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";

mutex m1, m2;

//1.uloha
bool Listok::kupit() {
	if (obsadenost == 0) {
		obsadenost = 2;
		return true;
	}
	return false;
}
bool Listok::rezervovatNaMeno(const string &menoRezervacie) {
	if (obsadenost != 0 || menoRezervacie == "") {
		return false;
	}
	obsadenost = 1;
	meno = menoRezervacie;
	return true;
}
bool Listok::uvolnit() {
	if (obsadenost == 1) {
		obsadenost = 0;
		meno = "";
		return true;
	}
	return false;
}
bool Listok::kupitRezervovany(const string &menoRez) {
	if (obsadenost == 1 && meno == menoRez) {
		obsadenost = 2;
		meno = "";
		return true;
	}
	return false;
}
//2.uloha
Koncert::Koncert(int pocetVsetkychListkov) {
	if (pocetVsetkychListkov >= 0)
		listky.resize(pocetVsetkychListkov);
}
int Koncert::pocetVsetkychListkov() const {
	return listky.size();
}
int Koncert::pocetVolnychListkov() const {
	int pocet = 0;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jeVolny()) {
			pocet++;
		}
	}
	return pocet;
}
int Koncert::pocetRezervacii() const {
	int pocet = 0;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jeRezervovany()) {
			pocet++;
		}
	}
	return pocet;
}
int Koncert::pocetPredanychListkov() const {
	int pocet = 0;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jePredany()) {
			pocet++;
		}
	}
	return pocet;
}
bool Koncert::kupitListky(int pocet) {
	if (pocetVolnychListkov() < pocet) {
		return false;
	}
	int p = 0;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (p < pocet && i->jeVolny()) {
			i->kupit();
			p++;
		}
	}
	return true;
}
bool Koncert::rezervovatListky(int pocet, const string &meno) {
	if (pocetVolnychListkov() < pocet || meno == "") {
		return false;
	}
	int p = 0;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (p < pocet && i->jeVolny()) {
			i->rezervovatNaMeno(meno);
			p++;
		}
	}
	return true;
}
//3.uloha
bool Koncert::zrusitVsetkyRezervacie() {
	bool uvolnil = false;
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jeRezervovany()) {
			i->uvolnit();
			uvolnil = true;
		}
	}
	return uvolnil;
}
int Koncert::kupitRezervovane(const string &meno) {
	int pocet = 0;
	if (meno == "") {
		return false;
	}
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jeRezervovany() && i->menoRezervacie() == meno) {
			i->kupitRezervovany(meno);
			pocet++;
		}
	}
	return pocet;
}
int Koncert::zrusitRezervaciu(const string &meno) {
	int pocet = 0;
	if (meno == "") {
		return false;
	}
	for (auto i = listky.begin(); i != listky.end(); i++) {
		if (i->jeRezervovany() && i->menoRezervacie() == meno) {
			i->uvolnit();
			pocet++;
		}
	}
	return pocet;
}
