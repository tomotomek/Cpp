#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

const char oddelovacAkordov = '$';
const char oddelovacFraz = '#';
const char nahradaMedzery = '%';

template<class T> class vacsi {
public:
	bool operator()(T x, T y) {
		return x < y;
	}
};
class FRAZA {
	string text;
	string akord;
	bool vlozFrazu(const string &fraza0);
public:
	FRAZA(const string &fraza0);
	string vratText() const;
	string vratAkord() const;
};
class VERS {
	vector<FRAZA> frazy;
	void vlozFrazu(const string &vers0);
	int vlozVers(const string &vers0);
public:
	VERS(const string &vers0);
	int pocetFraz() const;
	string vratTextFrazy(unsigned int fraza) const;
	string vratAkordFrazy(unsigned int fraza) const;
	string vratVers() const;
};
class PESNICKA {
	string nazov;
	vector<VERS> verse;
	set<string, vacsi<string>> akordy;
	int aktualny;
	void pridajAkordy();
public:
	PESNICKA(const string& naz) : nazov(naz), aktualny(-1) {};
	const string vratNazov() const { return nazov; };
	int pridajVers(const string &vers);
	const int pocetVersov() const { return verse.size(); };
	const string vratVers(unsigned int vers) const;
	const int pocetFraz() const;
	const string vratFrazu(unsigned int fraza) const;
	const string vratAkordFrazy(unsigned int fraza) const;
	const string vratTextFrazy(unsigned int fraza) const;
	bool pridajAkord(const string &s);
	const string vratZoznamAkordov() const;
	const int vratPocetAkordov() const { return akordy.size(); };
	const string akordZoZoznamu(unsigned int poradie) const;
	bool prvy();
	bool dalsi();
	const string vratAktualnuFrazu() const;
	const string vratAktualnyTextFrazy() const;
	const string vratAktualnyAkordFrazy() const;
	//1.uloha - nacitat pesnicku zo suboru 
	bool nacitajPesnickuZoSuboru(const string &nazov);
};
//2.uloha
class SPEVNIK {
	map<string, PESNICKA> spevnik;
	set<string> akordy;
	//3.uloha
	string aktualnaPiesen;
public:
	//2.uloha
	SPEVNIK() {};
	bool pridajPiesen(const PESNICKA& piesen);
	bool vyhodPiesen(const string& nazovPiesne);
	int vratPocetPiesni() const { return spevnik.size(); };
	bool nachadzaSaPiesen(const string& nazovPiesne) const;
	//3.uloha
	SPEVNIK(const SPEVNIK& spevnik);
	const string vratZoznamAkordov()  const;
	const string zoznamPesniciek() const;
	bool nastavPiesen(const string& nazovPiesne);
	PESNICKA & pesnicka();
	//4.uloha
	int pridajSpevnik(const SPEVNIK& spevnik);
	bool nachadzaSaAkord(const string& akord) const;
};
//5.uloha
class HUDOBNIK {
	string meno;
	SPEVNIK spevnik;
public:
	HUDOBNIK(const string& meno0) : meno(meno0) {};
	const string vratPlaylist() const { return spevnik.zoznamPesniciek(); };
	int naucSaPesnicky(const SPEVNIK& spevnik);
	const string vratZoznamAkordov() const;
	const string neznamyAkord(const PESNICKA& piesen) const;
	bool pridajPiesenAkVieZahrat(const PESNICKA& piesen);
};
#endif
bool DUMMY_BOOL = true;
int DUMMY_INT = 0;
string DUMMY_STRING = "";

//Zdedene riesenie programu pre pracu s triedami FRAZA, VERS a PESNICKA
string zamenCharaktery(const string &vstup, const char co, const char za) {
	string vystup;
	for (unsigned int i = 0; i < vstup.length(); i++) {
		if (vstup[i] == co)
			vystup += za;
		else
			vystup += vstup[i];
	}
	return vystup;
}
FRAZA::FRAZA(const string &fraza0) : text(""), akord("") {
	vlozFrazu(fraza0);
};
bool FRAZA::vlozFrazu(const string &fraza0) {
	if (fraza0.length() == 0) {
		return false;
	}
	string temp = zamenCharaktery(fraza0, ' ', nahradaMedzery);
	temp = zamenCharaktery(temp, oddelovacAkordov, ' ');
	istringstream rr(temp);
	string prvy, druhy;
	if (rr >> prvy) {
		if (rr >> druhy) {
			akord = prvy;
			druhy = zamenCharaktery(druhy, nahradaMedzery, ' ');
			text = druhy;
		}
		else {
			prvy = zamenCharaktery(prvy, nahradaMedzery, ' ');
			text = prvy;
			akord = "";
		}
		return true;
	}
	return false;
}
string FRAZA::vratText() const {
	return text;
}
string FRAZA::vratAkord() const {
	return akord;
}
VERS::VERS(const string &vers0) {
	vlozVers(vers0);
};
int VERS::vlozVers(const string &vers0) {
	if (vers0.length() == 0) {
		frazy.clear();
		return frazy.size();
	}
	frazy.clear();
	string temp = zamenCharaktery(vers0, ' ', nahradaMedzery);
	temp = zamenCharaktery(temp, oddelovacFraz, ' ');
	istringstream rr(temp);
	string fraza;
	while (rr >> fraza) {
		vlozFrazu(fraza);
	}
	return frazy.size();
}
void VERS::vlozFrazu(const string &fraza) {
	frazy.push_back(FRAZA(fraza));
}
int VERS::pocetFraz() const {
	return frazy.size();
}
string VERS::vratTextFrazy(unsigned int fraza) const {
	if (fraza >= 0 && fraza < frazy.size()) {
		return frazy[fraza].vratText();
	}
	return "Zly index";
}
string VERS::vratAkordFrazy(unsigned int fraza) const {
	if (fraza >= 0 && fraza < frazy.size()) {
		return frazy[fraza].vratAkord();
	}
	return "Zly index";
}
string VERS::vratVers() const {
	string vers;
	for (unsigned int i = 0; i < pocetFraz(); i++) {
		if (i > 0) {
			vers += oddelovacFraz;
		}
		if (frazy[i].vratAkord().length() > 0) {
			vers += frazy[i].vratAkord() + oddelovacAkordov;
		}
		vers += frazy[i].vratText();
	}
	return vers;
}
int PESNICKA::pridajVers(const string &vers) {
	if (vers.length() == 0) {
		return pocetVersov();
	}
	verse.push_back(VERS(vers));
	pridajAkordy();
	return pocetVersov();
}
const string PESNICKA::vratVers(unsigned int vers) const {
	if (vers < pocetVersov()) {
		return verse[vers].vratVers();
	}
	return "Neexistujuci vers";
}
const int PESNICKA::pocetFraz() const {
	int pocitadloFraz = 0;
	for (unsigned int i = 0; i < pocetVersov(); i++) {
		pocitadloFraz += verse[i].pocetFraz();
	}
	return pocitadloFraz;
}
const string PESNICKA::vratFrazu(unsigned int fraza) const {
	if (fraza < pocetFraz()) {
		int pocitadloFraz = 0;
		for (unsigned int i = 0; i < pocetVersov(); i++) {
			if (pocitadloFraz <= fraza
				&& fraza < (pocitadloFraz + verse[i].pocetFraz())) {
				string temp = verse[i].vratAkordFrazy(fraza - pocitadloFraz);
				temp += oddelovacAkordov;
				temp += verse[i].vratTextFrazy(fraza - pocitadloFraz);
				return temp;
			}
			pocitadloFraz += verse[i].pocetFraz();
		}
	}
	return "Neexistujuca fraza";
}
const string PESNICKA::vratTextFrazy(unsigned int fraza) const {
	if (fraza < pocetFraz()) {
		int pocitadloFraz = 0;
		for (unsigned int i = 0; i < pocetVersov(); i++) {
			if (pocitadloFraz <= fraza
				&& fraza < (pocitadloFraz + verse[i].pocetFraz())) {
				string temp = verse[i].vratAkordFrazy(fraza - pocitadloFraz);
				return verse[i].vratTextFrazy(fraza - pocitadloFraz);
			}
			pocitadloFraz += verse[i].pocetFraz();
		}
	}
	return "Neexistujuca fraza";
}
const string PESNICKA::vratAkordFrazy(unsigned int fraza) const {
	if (fraza < pocetFraz()) {
		int pocitadloFraz = 0;
		for (unsigned int i = 0; i < pocetVersov(); i++) {
			if (pocitadloFraz <= fraza
				&& fraza < (pocitadloFraz + verse[i].pocetFraz())) {
				string temp = verse[i].vratAkordFrazy(fraza - pocitadloFraz);
				return verse[i].vratAkordFrazy(fraza - pocitadloFraz);
			}
			pocitadloFraz += verse[i].pocetFraz();
		}
	}
	return "Neexistujuca fraza";
}
void PESNICKA::pridajAkordy() {
	for (unsigned int i = 0; i < verse[pocetVersov() - 1].pocetFraz(); i++) {
		string temp = verse[pocetVersov() - 1].vratAkordFrazy(i);
		if (temp.length() > 0) {
			pridajAkord(temp);
		}
	}
}
bool PESNICKA::pridajAkord(const string &akord) {
	const bool is = (akordy.find(akord) != akordy.end());
	if (is) {
		return false;
	}
	akordy.insert(akord);
	return true;
}
const string PESNICKA::vratZoznamAkordov() const {
	string temp = "";
	for (auto i = akordy.begin(); i != akordy.end(); ++i) {
		if (i != akordy.end() && i != akordy.begin()) {
			temp += ",";
		}

		temp += *i;
	}
	return temp;
}
const string PESNICKA::akordZoZoznamu(unsigned int poradie) const {
	if (poradie <= akordy.size()) {
		int pocet = 0;
		for (auto i = akordy.begin(); i != akordy.end(); ++i) {
			if (pocet == poradie) {
				return *i;
			}
			pocet++;
		}
	}
	return "Taky akord nie je";
}
bool PESNICKA::prvy() {
	if (pocetFraz() > 0) {
		aktualny = 0;
		return true;
	}
	return false;
}
bool PESNICKA::dalsi() {
	if (aktualny < pocetFraz() - 1) {
		aktualny++;
		return true;
	}
	return false;
}
const string PESNICKA::vratAktualnuFrazu() const {
	return vratFrazu(aktualny);
}
const string PESNICKA::vratAktualnyTextFrazy() const {
	return vratTextFrazy(aktualny);
}
const string PESNICKA::vratAktualnyAkordFrazy() const {
	return vratAkordFrazy(aktualny);
}
//Koniec zdedeneho riesenia

//1.uloha

//Vymenit v zdedenom rieseni v triede PESNICKA pouzivanie kontajnera: vector<string> akordy; 
//za pouzivanie kontajnera: set<string> zoznamAkordov;
//bez zmeny funkcionality

bool PESNICKA::nacitajPesnickuZoSuboru(const string &nazov) {
	ifstream inFile;
	string line;
	inFile.open(nazov);
	if (!inFile) {
		return false;
	}
	while ( getline(inFile, line) ) {
		if (line != "") {
			pridajVers(line);
		}
	}	
	inFile.close();
	return true;
}
//2.uloha
bool SPEVNIK::pridajPiesen(const PESNICKA &piesen) {
	stringstream akordy1(piesen.vratZoznamAkordov());
	string akord;
	if (nachadzaSaPiesen(piesen.vratNazov())) {
		return false;
	}
	spevnik.insert(pair<const string, PESNICKA>(piesen.vratNazov(), piesen));
	while (getline(akordy1, akord, ',')) {
		const bool is = (akordy.find(akord) != akordy.end());
		if (is) {
		}
		else {
			akordy.insert(akord);
		}
	}
	
	return true;
}
bool SPEVNIK::nachadzaSaPiesen(const string &nazovPiesne) const {
	if (spevnik.find(nazovPiesne) == spevnik.end()) {
		return false;
	}
	return true;
}
bool SPEVNIK::vyhodPiesen(const string &nazovPiesne) {
	if (nachadzaSaPiesen(nazovPiesne)) {
		stringstream akordy1(spevnik.find(nazovPiesne)->second.vratZoznamAkordov());
		string akord;
		bool nechaj = false;
		while (getline(akordy1, akord, ',')) {
			if (akordy.find(akord) != akordy.end()) {
				nechaj = false;
				for (auto i = spevnik.begin(); i != spevnik.end(); i++) {
					if (i->first != nazovPiesne) {
						stringstream akordy2(i->second.vratZoznamAkordov());
						string akord2;
						while (getline(akordy2, akord2, ',')) {
							if (akord2 == akord) {
								nechaj = true;
							}
						}
					}
				}
				if (!nechaj) {
					akordy.erase(akord);
				}
			}
		}
		spevnik.erase(nazovPiesne);
		return true;
	}
	return false;
}
//3.uloha
bool SPEVNIK::nastavPiesen(const string &nazovPiesne){
	if (nachadzaSaPiesen(nazovPiesne)) {
		aktualnaPiesen = nazovPiesne;
		return true;
	}
	return false;
}
SPEVNIK::SPEVNIK(const SPEVNIK &spev){
	for (auto i = spev.akordy.begin(); i != spev.akordy.end(); ++i) {
		const bool is = (akordy.find(*i) != akordy.end());
		if (is) {
		}
		else {
			akordy.insert(*i);
		}
	}
	for (auto i = spev.spevnik.begin(); i != spev.spevnik.end(); i++) {
		spevnik.insert(pair<const string, PESNICKA>(i->first, i->second));
	}
	nastavPiesen(spev.aktualnaPiesen);

}
const string SPEVNIK::vratZoznamAkordov() const {
	string temp = "";
	for (auto i = akordy.begin(); i != akordy.end(); ++i) {
		if (i != akordy.end() && i != akordy.begin()) {
			temp += ",";
		}
		temp += *i;
	}
	return temp;
}
const string SPEVNIK::zoznamPesniciek() const {
	string temp = "";
	for (auto i = spevnik.begin(); i != spevnik.end(); ++i) {
		if (i != spevnik.end() && i != spevnik.begin()) {
			temp += ",";
		}
		temp += i->first;
	}
	return temp;
}
PESNICKA & SPEVNIK::pesnicka() {
	if (aktualnaPiesen != "") {
		for (auto i = spevnik.begin(); i != spevnik.end(); i++) {
			if (i->first == aktualnaPiesen) {
				return i->second;
			}
		}
	}
	else {
		PESNICKA temp("Dummy");
		pridajPiesen(temp);
		return spevnik.begin()->second;
	}
}
//4.uloha
int SPEVNIK::pridajSpevnik(const SPEVNIK &spevnik0) {
	int pocet = 0;
	for (auto i = spevnik0.spevnik.begin(); i != spevnik0.spevnik.end(); i++) {
		if (spevnik.find(i->first) == spevnik.end()) {
			spevnik.insert(pair<const string, PESNICKA>(i->first, i->second));
			pocet++;
		}
	}
	for (auto i = spevnik0.akordy.begin(); i != spevnik0.akordy.end(); i++) {
		if (akordy.find(*i) == akordy.end()) {
			akordy.insert(*i);
		}
	}
	return pocet;
}
bool SPEVNIK::nachadzaSaAkord(const string & akord) const {
	if (akordy.find(akord) != akordy.end()) {
		return true;
	}
	return false;
}
//5.uloha
int HUDOBNIK::naucSaPesnicky(const SPEVNIK &spevnik0) {
	return spevnik.pridajSpevnik(spevnik0);
}
const string HUDOBNIK::vratZoznamAkordov() const {
	return spevnik.vratZoznamAkordov();
}
const string HUDOBNIK::neznamyAkord(const PESNICKA &piesen) const {
	stringstream zoznam(piesen.vratZoznamAkordov());
	string akord;
	while (getline(zoznam, akord, ',')) {
		if (!spevnik.nachadzaSaAkord(akord)) {
			return akord;
		}
	}
	return "";
}
bool HUDOBNIK::pridajPiesenAkVieZahrat(const PESNICKA &piesen) {
	stringstream zoznam(piesen.vratZoznamAkordov());
	string akord;
	while (getline(zoznam, akord, ',')) {
		if (!spevnik.nachadzaSaAkord(akord)) {
			return false;
		}
	}
	return spevnik.pridajPiesen(piesen);
}