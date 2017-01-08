#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
const string nula("0");
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