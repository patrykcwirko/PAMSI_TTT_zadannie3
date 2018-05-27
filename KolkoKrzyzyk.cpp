#include "stdafx.h"
#include "KolkoKrzyzyk.h"
#include "Ustawienia.h"


KolkoKrzyzyk::KolkoKrzyzyk() : wielkosc(DFLT_ILOSC_W_RZEDZIE), siatka(nullptr), ustawienia(nullptr)
{
	this->siatka = std::make_shared< Matrix >();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : wielkosc(DFLT_ILOSC_W_RZEDZIE), siatka(nullptr), ustawienia(nullptr)
{
	this->wielkosc = ustawienia->ilosc();
	this->ustawienia = ustawienia;
	this->siatka = std::make_shared< Matrix >();
}

KolkoKrzyzyk::~KolkoKrzyzyk()
{
}

void KolkoKrzyzyk::ustawWielkosc(int wielkosc)
{
	this->wielkosc = wielkosc;
	this->reset();
}

bool KolkoKrzyzyk::ustaw(int kratka)
{
	return false;
}

EKratka KolkoKrzyzyk::pobierz(int kratka)
{
	return OZnak;
}

void KolkoKrzyzyk::reset()
{
	//TODO
	this->siatka = std::make_shared< Matrix >();
}

EKratka KolkoKrzyzyk::get(size_t kolumna, size_t wiersz)
{
	return this->siatka->at(kolumna).at(wiersz);
}

void KolkoKrzyzyk::set(size_t kolumna, size_t wiersz, EKratka wartosc)
{
	this->siatka->at(kolumna).at(wiersz) = wartosc;
}