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

bool Ustawienia::czyZaczynaCzlowiek()
{
	return this->zaczynaCzlowiek;
}

void Ustawienia::ustawCzyZaczynaCzlowiek(bool ruch)
{
	this->zaczynaCzlowiek = ruch;
}