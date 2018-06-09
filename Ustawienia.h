#pragma once

#include <memory>
#include <string>
#include "Narzedzia.h"
#include "Typy.h"

#define DFLT_ILOSC_W_RZEDZIE 3
#define TDLUGOSC 406
#define TWYSOKOSC 445

class Ustawienia
{
private:
	int rozmiarSiatki;
	bool zaczynaKomputer;
	bool wygranaGdyPiec;

public:

	Ustawienia() : rozmiarSiatki(DFLT_ILOSC_W_RZEDZIE), zaczynaKomputer(false), wygranaGdyPiec(false) { }
	Ustawienia(int rozmiar) : rozmiarSiatki(rozmiar), zaczynaKomputer(false), wygranaGdyPiec(false) { }

	virtual ~Ustawienia() {}
	int pobierzRozmiarSiatki();
	void ustawRozmiarSiatki(int rozmiar);
	bool czyZaczynaKomputer();
	void ustawZaczynaKomputer(bool czyKomputer);
	bool czyWygranaGdyPiec();
	void ustawWygranaGdyPiec(bool czyPiecToWygrana);
	String_Ptr info();
};


typedef std::shared_ptr< Ustawienia > Ustawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();