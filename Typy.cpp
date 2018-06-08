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
	this->pozycja = poz;
}