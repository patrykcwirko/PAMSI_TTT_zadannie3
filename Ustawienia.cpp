#include "stdafx.h"
#include "Ustawienia.h"

int Ustawienia::pobierzRozmiarSiatki()
{
	return rozmiarSiatki;
}

void Ustawienia::ustawRozmiarSiatki(int rozmiar)
{
	this->rozmiarSiatki = rozmiar;
}

int Ustawienia::pobierzGlebokoscSzukania()
{
	return this->glebokoscSzukania;
}
void Ustawienia::ustawGlebokoscSzukania(int glebokosc)
{
	this->glebokoscSzukania = glebokosc;
}

bool Ustawienia::czyZaczynaKomputer()
{
	return this->zaczynaKomputer;
}

void Ustawienia::ustawZaczynaKomputer(bool czyKomputer)
{
	this->zaczynaKomputer = czyKomputer;
}

bool Ustawienia::czyGraWartLosowymi()
{
	return this->graWartLosowymi;
}

void Ustawienia::ustawGraWartLosowymi(bool graLosowymi)
{
	this->graWartLosowymi = graLosowymi;
}

String_Ptr Ustawienia::info()
{
	std::string txt;
	txt.append("Ustawienia => ilosc: ");
	txt.append(std::to_string(rozmiarSiatki));
	txt.append(",  glebokosc szukania: ");
	txt.append(std::to_string(glebokoscSzukania));
	txt.append(", zaczynaKomputer: ");
	txt.append(std::to_string(zaczynaKomputer));
	txt.append(",  gra wart. losowymi: ");
	txt.append(std::to_string(graWartLosowymi));
	return std::make_shared<std::string>(txt);
}