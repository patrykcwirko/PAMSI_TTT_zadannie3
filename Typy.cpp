#include "stdafx.h"
#include "Typy.h"

Pozycja::Pozycja()
{
	Pozycja(0, 0);
}

Pozycja::Pozycja(int xx, int yy)
{
	this->x = xx;
	this->y = yy;
}

Wynik::Wynik()
{
	Wynik(0, nullptr);
}

Wynik::Wynik(int p, Pozycja_Ptr poz)
{
	this->punkty = p;
	this->wygral = Pusta;
	this->pozycja = poz;
}

Wynik::Wynik(int p, EKratka wygral, Pozycja_Ptr poz)
{
	this->punkty = p;
	this->wygral = wygral;
	this->pozycja = poz;
}

Pozycja_Ptr Wynik::pobierzPozycje()
{
	return this->pozycja;
}

void Wynik::ustawWygral(EKratka wygral)
{
	this->wygral = wygral;
}

EKratka Wynik::ktoWygral()
{
	return this->wygral;
}