#include "stdafx.h"
#include "KolkoKrzyzyk.h"
#include "Narzedzia.h"

KolkoKrzyzyk::KolkoKrzyzyk() : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), terazRuchGracza(true), matrix(nullptr), ustawienia(nullptr), minmax(nullptr)
{
	this->minmax = std::make_shared< MinMax >();
	this->ustawienia = std::make_shared< Ustawienia >();
	this->wielkosc = ustawienia->pobierzIloscWRzedzie();
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), terazRuchGracza(true), matrix(nullptr), ustawienia(nullptr), minmax(nullptr)
{
	this->minmax = std::make_shared< MinMax >();
	this->ustawienia = ustawienia;
	this->wielkosc = ustawienia->pobierzIloscWRzedzie();
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::~KolkoKrzyzyk()
{
}

void KolkoKrzyzyk::ustawParametry(Ustawienia_Ptr ustawienia)
{
	this->ustawienia = ustawienia;
	this->wielkosc = ustawienia->pobierzIloscWRzedzie();
	this->init();
}

void KolkoKrzyzyk::ustawWielkosc(int wielkosc)
{
	this->wielkosc = wielkosc;
	this->init();
}

bool KolkoKrzyzyk::ustawKratke(int kratka)
{
	int ilKratek = this->ustawienia->pobierzIloscWRzedzie() * this->ustawienia->pobierzIloscWRzedzie();
	if (kratka <0 || kratka >ilKratek-1) { return false; }
	int y = kratka / this->ustawienia->pobierzIloscWRzedzie();
	int x = kratka - (y * this->ustawienia->pobierzIloscWRzedzie());
	std::string ctr1 = Narzedzia::kratkaNaString(Pusta);
	std::string ctr2 = Narzedzia::kratkaNaString(this->matrix->at(y).at(x));
	Narzedzia::printLog(std::to_string(x) + "," + std::to_string(y) + ":" + ctr2);
	if (this->matrix->at(y).at(x) != Pusta )
	{
		return false;
	}
	if (this->status() == RuchGracza) 
	{
		this->matrix->at(y).at(x) = XZnak;
		terazRuchGracza = false;
		return true;
	}
	if (this->status() == RuchKomputera)
	{
		this->matrix->at(y).at(x) = OZnak;
		terazRuchGracza = true;
	}
	return true;
}

EKratka KolkoKrzyzyk::pobierz(int kratka)
{
	int x = kratka / this->ustawienia->pobierzIloscWRzedzie();
	int y = kratka - (x* this->ustawienia->pobierzIloscWRzedzie());
	return pobierz(x, y);
}

EKratka KolkoKrzyzyk::pobierz(int x, int y) 
{
	return this->matrix->at(y).at(x);
}

void KolkoKrzyzyk::init()
{
	std::vector< std::vector<EKratka> >::iterator row;
	std::vector<EKratka>::iterator col;
	for(row = matrix->begin(); row != matrix->end(); row++)
	{
		if (!row->empty()) {
			row->clear();
		}
	}
	matrix->clear();

	for (int i = 0; i<ustawienia->pobierzIloscWRzedzie(); i++)
	{
		std::vector <EKratka> row;
		for (int j = 0; j<ustawienia->pobierzIloscWRzedzie(); j++)
		{
			row.push_back(Pusta);
		}
		matrix->push_back(row);
	}
}

EKIK KolkoKrzyzyk::status()
{
	if (terazRuchGracza)
	{
		return RuchGracza;
	}
	return RuchKomputera;
}

bool KolkoKrzyzyk::czyTerazRuchGracza()
{
	return terazRuchGracza;
}

void KolkoKrzyzyk::wykonajRuchKomp()
{
	terazRuchGracza = false;
	int najlepszyRuch = this->minmax->nalepszyRuch(this->matrix, ustawienia->pobierzIloscWRzedzie());
	ustawKratke(najlepszyRuch);
	terazRuchGracza = true;
}
