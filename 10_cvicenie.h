#include <sstream>

using namespace std;

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

//1.uloha
template<typename T> class Pole {
	void deleteClenov();
	inline void vlozPrazdnyElement();
	string chyba;
protected:
	int pocet;
	T *clen;
public:
	Pole();
	~Pole();
	int velkost() const { return pocet; };
	bool vloz(const T &vstup);
	void vyprazdni();
	const string obsah(char delimiter);
	//2.uloha
	const string vratPoslednuChybu() const { return chyba; };
	Pole(const Pole<T> &);
	Pole(Pole<T> &&);
	T & operator[](int i);
	//3.uloha
	bool nachadzaSa(const T &vstup);
	bool odober(const int i);
	bool vyhod(const T &vstup);
	void operator+=(const Pole<T> &);
};
//4.uloha
template<typename T> class Mnozina : public Pole<T> {
public:
	Mnozina() {};
	bool vloz(const T &vstup);
	//5.uloha
	Mnozina(const Mnozina<T> &vstup);
	bool zrus(const T &vstup);
	void operator+=(const Mnozina<T> &vstup);
};

const int MAX = 5;

//1.uloha
template<typename T> Pole<T>::Pole() : pocet(0), clen(nullptr), chyba("") {
};
template<typename T> void Pole<T>::deleteClenov() {
	clen = nullptr;
}
template<typename T> Pole<T>::~Pole() {
	deleteClenov();
}
template<typename T> const string Pole<T>::obsah(char delimiter) {
	ostringstream ost;
	for (int i = 0; i < pocet; i++) {
		if (i > 0) {
			ost << delimiter;
		}
		ost << *(clen + i);
	}
	return ost.str();
}
template<typename T> bool Pole<T>::vloz(const T &vstup) {
	auto i = 0;
    for (auto j = 0 ; j < pocet; j++) {
		if (*(clen + j) == vstup){
		  return false;
		}
	}
	T *temp = new T[pocet + 1];
	for (i ; i < pocet; i++) {
		*(temp + i) = *(clen + i);
	}
	*(temp + i) = vstup;
	if (i <= pocet) {
		pocet++;
	}
	deleteClenov();
	clen = temp;
	return true;
}
template<typename T> void Pole<T>::vyprazdni() {
	deleteClenov();
	pocet = 0;
}
//2.uloha
template<typename T> Pole<T>::Pole(const Pole<T> &vstup)
{
	pocet = vstup.pocet;
	clen = new T[pocet];
	for (auto i = 0; i < pocet; i++) {
		clen[i] = vstup.clen[i];
	}
}
template<typename T> Pole<T>::Pole(Pole<T> &&vstup)
	: pocet(0), clen(nullptr), chyba("")
{
	clen = vstup.clen;
	pocet = vstup.pocet;
	chyba = vstup.chyba;
	vstup.clen = nullptr;
	vstup.pocet = 0;
	vstup.chyba = "";
}
template<typename T> T & Pole<T>::operator[](int i) {
	if (i <= 0 || i >= pocet) {
		ostringstream ost;
		ost << "Zly index " << i;
		chyba = ost.str();
		if (clen == nullptr) {
			vlozPrazdnyElement();
		}
		return clen[0];
	}
	return clen[i];
}
template<typename T> void Pole<T>::vlozPrazdnyElement() {
	if (clen == nullptr && pocet == 0) {
		clen = new T[1];
		clen[0] = 0;
	}
}
template<> void Pole<string>::vlozPrazdnyElement() {
	if (clen == nullptr && pocet == 0) {
		clen = new string[1];
		clen[0] = "";
	}
}
//3.uloha
template<typename T> bool Pole<T>::odober(int i) {
	if (pocet == 1 && i == 0) {
		vyprazdni();
		return true;
	}
	if ((pocet-1) < i){
	  return false;
	}
	T *temp = new T[pocet - 1];
	for (auto j = 0, k = 0; j <= pocet - 1; j++) {
		if (j == i) k++;
		if ((j + k) < pocet) {
			*(temp + j) = *(clen + j + k);
		}
	}
	deleteClenov();
	clen = temp;
	pocet--;
	return true;
}
template<typename T> bool Pole<T>::vyhod(const T &vstup) {
	int pozicia = -1;
	for (int j = 0; j < pocet; j++) {
		if (*(clen + j) == vstup) {
			pozicia = j;
			break;
		}
	}
	if (pozicia == -1) {
		return false;
	}
	T *temp = new T[pocet - 1];
	for (int j = 0, k = 0; j < pocet - 1; j++) {
		if (j == pozicia) k++;
		if ((j+k) < pocet) *(temp + j) = *(clen + j + k);
	}
	deleteClenov();
	clen = temp;
	pocet--;
	return true;
}
template<typename T> void Pole<T>::operator+=(const Pole<T> &b) {
	if (pocet == 0 && b.pocet == 0) {
		
		return;
	}
	T *temp = new T[pocet + b.pocet];
	for (int i = 0; i < pocet; i++) {
		temp[i] = clen[i];
	}
	for (int i = 0; i < b.pocet; i++) {
		temp[pocet + i] = b.clen[i];
	}
	pocet += b.pocet;
	deleteClenov();
	clen = temp;
}
//4.uloha
template<typename T> bool Pole<T>::nachadzaSa(const T &vstup) {
	for (auto i = 1; i < this->velkost(); i++) {
		if (this->operator[](i) == vstup) {
			return true;
		}
	}
	return false;
}
template<typename T> bool Mnozina<T>::vloz(const T &vstup) {
	return Pole<T>::vloz(vstup);
}
//5.uloha
template<typename T> Mnozina<T>::Mnozina(const Mnozina<T> &vstup)
{
	for (int i = 0; i < MAX && i < vstup.pocet; i++) {
		vloz(vstup.clen[i]);
	}
}
template<typename T> bool Mnozina<T>::zrus(const T &vstup) {
	for (int i = 0; i < this->pocet; i++) {
		if (this->operator[](i) == vstup) {
			return this->odober(i);
		}
	}
	return false;
}
template<typename T> void Mnozina<T>::operator+=(const Mnozina<T> &vstup) {
	for (int i = 0; i < vstup.pocet; i++) {
		vloz(vstup.clen[i]);
	}
}

#endif





