#include "stdafx.h"
#include "KolkoKrzyzyk.h"
#include "Ustawienia.h"


KolkoKrzyzyk::KolkoKrzyzyk() : wielkosc(DFLT_ILOSC_W_RZEDZIE), matrix(nullptr), ustawienia(nullptr)
{
	this->matrix = std::make_shared< Matrix >();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : wielkosc(DFLT_ILOSC_W_RZEDZIE), matrix(nullptr), ustawienia(nullptr)
{
	this->wielkosc = ustawienia->ilosc();
	this->ustawienia = ustawienia;
	this->matrix = std::make_shared< Matrix >();
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
	//for(std::vector<EKratka> wek : this->matrix)
	//{
	//	wek.clear();
	//}
	//for (std::vector<EKratka>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	//	std::cout << ' ' << *it;

	std::vector< std::vector<EKratka> >::iterator row;
	std::vector<EKratka>::iterator col;
	for (row = matrix->begin(); row != matrix->end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			*col = Pusta;
		}
	}
}

EKratka KolkoKrzyzyk::get(size_t kolumna, size_t wiersz)
{
	return this->matrix->at(kolumna).at(wiersz);
}

void KolkoKrzyzyk::set(size_t kolumna, size_t wiersz, EKratka wartosc)
{
	this->matrix->at(kolumna).at(wiersz) = wartosc;
}