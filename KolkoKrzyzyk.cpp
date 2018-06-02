#include "stdafx.h"
#include "KolkoKrzyzyk.h"
#include "Ustawienia.h"


KolkoKrzyzyk::KolkoKrzyzyk() : wielkosc(DFLT_ILOSC_W_RZEDZIE), ruchG1(false), matrix(nullptr), ustawienia(nullptr)
{
	this->matrix = std::make_shared< Matrix >();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : wielkosc(DFLT_ILOSC_W_RZEDZIE), ruchG1(false), matrix(nullptr), ustawienia(nullptr)
{
	this->wielkosc = ustawienia->ilosc();
	this->ustawienia = ustawienia;
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::~KolkoKrzyzyk()
{
}

void KolkoKrzyzyk::ustawWielkosc(int wielkosc)
{
	this->wielkosc = wielkosc;
	this->init();
}

bool KolkoKrzyzyk::ustawKratke(int kratka)
{
	int ilKratek = this->ustawienia->ilosc() * this->ustawienia->ilosc();
	if (kratka <0 || kratka >ilKratek-1) { return false; }
	int y = kratka / this->ustawienia->ilosc();
	int x = kratka - (y * this->ustawienia->ilosc());
	if (this->matrix->at(y).at(x) != Pusta )
	{
		return false;
	}
	if (this->status() == G1Ruch) 
	{
		this->matrix->at(y).at(x) = XZnak;
		ruchG1 = false;
		return true;
	}
	if (this->status() == G2Ruch)
	{
		this->matrix->at(y).at(x) = OZnak;
		ruchG1 = true;
	}
	return true;
}

EKratka KolkoKrzyzyk::pobierz(int kratka)
{
	return Pusta;
}

void KolkoKrzyzyk::init()
{
	std::vector< std::vector<EKratka> >::iterator row;
	std::vector<EKratka>::iterator col;
	for(row = matrix->end(); row != matrix->begin(); row--)
	{
		row->clear();
	}
	matrix->clear();

	for (int i = 0; i<ustawienia->ilosc(); i++)
	{
		std::vector <EKratka> row;
		for (int j = 0; j<ustawienia->ilosc(); j++)
		{
			row.push_back(Pusta);
		}
		matrix->push_back(row);
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

EKIK KolkoKrzyzyk::status()
{
	return Gramy;
}

bool KolkoKrzyzyk::czyRuchKomp()
{
	return false;
}

void KolkoKrzyzyk::wykonjaRuchKomp()
{

}