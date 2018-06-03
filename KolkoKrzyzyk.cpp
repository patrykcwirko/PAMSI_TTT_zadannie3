#include "stdafx.h"
#include "KolkoKrzyzyk.h"
#include "Narzedzia.h"

std::string kratkaNaString(EKratka znak)
{
	switch (znak)
	{
	case Pusta:
		return "_";
	case XZnak:
		return "X";
	case OZnak:
		return "O";
	default:
		return " ";
	}
}

KolkoKrzyzyk::KolkoKrzyzyk() : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), ruchG1(true), matrix(nullptr), ustawienia(nullptr)
{
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), ruchG1(false), matrix(nullptr), ustawienia(nullptr)
{
	this->wielkosc = ustawienia->pobierzIloscWRzedzie();
	this->ustawienia = ustawienia;
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
	std::string ctr1 = kratkaNaString(Pusta);
	std::string ctr2 = kratkaNaString(this->matrix->at(y).at(x));
	Narzedzia::printLog("\n" + std::to_string(x) + "," + std::to_string(y) + ":" + ctr2 + "\n");
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
	for(row = matrix->end(); row != matrix->begin(); row--)
	{
		row->clear();
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
	if (ruchG1)
	{
		return G1Ruch;
	}
	return G2Ruch;
}

bool KolkoKrzyzyk::czyRuchKomp()
{
	return false;
}

void KolkoKrzyzyk::wykonjaRuchKomp()
{
	
}
