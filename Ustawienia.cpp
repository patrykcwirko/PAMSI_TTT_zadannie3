#include "stdafx.h"
#include "Ustawienia.h"

int Ustawienia::pobierzIloscWRzedzie()
{
	return iloscWRzedzie;
}

void Ustawienia::ustawIloscWRzedzie(int ilosc)
{
	this->iloscWRzedzie = ilosc;
}

bool Ustawienia::czyZaczynaKomputer()
{
	return this->zaczynaKomputer;
}

void Ustawienia::ustawZaczynaKomputer(bool czyKomputer)
{
	this->zaczynaKomputer = czyKomputer;
}

bool Ustawienia::czyWygranaGdyPiec()
{
	return this->wygranaGdyPiec;
}

void Ustawienia::ustawWygranaGdyPiec(bool czyPiecToWygrana)
{
	this->wygranaGdyPiec = czyPiecToWygrana;
}

String_Ptr Ustawienia::info()
{
	std::string txt;
	txt.append("Ustawienia => ilosc: ");
	txt.append(std::to_string(iloscWRzedzie));
	txt.append(", zaczynaKomputer: ");
	txt.append(std::to_string(zaczynaKomputer));
	txt.append(",  wygranaGdyPiec: ");
	txt.append(std::to_string(wygranaGdyPiec));
	return std::make_shared<std::string>(txt);
}