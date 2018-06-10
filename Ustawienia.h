#pragma once

#include <memory>
#include <string>
#include "Narzedzia.h"
#include "Typy.h"

#define MAX_GLEBOKOSC	3
#define DFLT_ILOSC_W_RZEDZIE 3
#define TDLUGOSC 406
#define TWYSOKOSC 445

class Ustawienia
{
private:
	int rozmiarSiatki;
	int glebokoscSzukania;
	bool zaczynaKomputer;
	bool graWartLosowymi;

public:

	Ustawienia() : rozmiarSiatki(DFLT_ILOSC_W_RZEDZIE), glebokoscSzukania(MAX_GLEBOKOSC), zaczynaKomputer(false), graWartLosowymi(false) { }
	Ustawienia(int rozmiar) : rozmiarSiatki(rozmiar), glebokoscSzukania(MAX_GLEBOKOSC), zaczynaKomputer(false), graWartLosowymi(false) { }

	virtual ~Ustawienia() {}
	int pobierzRozmiarSiatki();
	void ustawRozmiarSiatki(int rozmiar);
	int pobierzGlebokoscSzukania();
	void ustawGlebokoscSzukania(int glebokosc);
	bool czyZaczynaKomputer();
	void ustawZaczynaKomputer(bool czyKomputer);
	bool czyGraWartLosowymi();
	void ustawGraWartLosowymi(bool graLosowymi);
	
	String_Ptr info();
};


typedef std::shared_ptr< Ustawienia > Ustawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();