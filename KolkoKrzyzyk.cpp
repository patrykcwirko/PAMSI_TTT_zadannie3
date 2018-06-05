#include "stdafx.h"
#include "KolkoKrzyzyk.h"

KolkoKrzyzyk::KolkoKrzyzyk() : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), terazRuchGracza(true), ruchyWyczerpane(0), iloscElementow(0), 
	turn(OZnak), matrix(nullptr), tempMatrix(nullptr), cache(nullptr), ustawienia(nullptr)
{
	this->ustawienia = std::make_shared< Ustawienia >();
	this->wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : 
	wielkosc(DFLT_ILOSC_W_RZEDZIE), terazRuchGracza(true), ruchyWyczerpane(0), iloscElementow(0),
	turn(OZnak), matrix(nullptr), tempMatrix(nullptr), cache(nullptr), ustawienia(nullptr)
{
	this->ustawienia = ustawienia;
	this->wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->matrix = std::make_shared< Matrix >();
	this->init();
}

KolkoKrzyzyk::~KolkoKrzyzyk()
{
	if (this->cache != nullptr)
	{
		this->cache->clear();
	}
}

void KolkoKrzyzyk::ustawParametry(Ustawienia_Ptr ustawienia)
{
	this->ustawienia = ustawienia;
	this->wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->init();
}

void KolkoKrzyzyk::ustawWielkosc(int wielkosc)
{
	this->wielkosc = wielkosc;
	this->init();
}

bool KolkoKrzyzyk::ustawKratke(int kratka)
{
	int ilKratek = this->ustawienia->pobierzRozmiarSiatki() * this->ustawienia->pobierzRozmiarSiatki();
	if (kratka <0 || kratka >ilKratek-1) { return false; }
	int y = kratka / this->ustawienia->pobierzRozmiarSiatki();
	int x = kratka - (y * this->ustawienia->pobierzRozmiarSiatki());
	//std::string ctr1 = Narzedzia::kratkaNaString(Pusta);
	std::string ctr2 = Narzedzia::kratkaNaString(this->matrix->pobierz(x, y)); 
	Narzedzia::printLog(std::to_string(x) + "," + std::to_string(y) + ":" + ctr2);

	if (this->matrix->pobierz(x, y) != Pusta )
	{
		return false;
	}
	if (this->status() == RuchGracza) 
	{
		this->matrix->ustaw(x, y, XZnak);
		terazRuchGracza = false;
		return true;
	}
	if (this->status() == RuchKomputera)
	{
		this->matrix->ustaw(x, y, OZnak);
		terazRuchGracza = true;
	}
	return true;
}

void KolkoKrzyzyk::init()
{
	matrix->init();
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

void KolkoKrzyzyk::wykonajRuchKomp(EKratka kratka)
{
	terazRuchGracza = false;
	KolkoKrzyzyk_Ptr ptrGra = std::make_shared<KolkoKrzyzyk>(*this);
	int najlepszyRuch = this->nalepszyRuch(this->matrix, ustawienia->pobierzRozmiarSiatki(), kratka);
	ustawKratke(najlepszyRuch);
	terazRuchGracza = true;
}

EKratka KolkoKrzyzyk::pobierz(int x, int y)
{
	return this->matrix->pobierz(x, y);
}

EKratka KolkoKrzyzyk::pobierz(int index)
{
	return this->matrix->pobierz(index);
}

int KolkoKrzyzyk::nalepszyRuch(Matrix_Ptr matrix, int rozmiarSiatki, EKratka kratka)
{
	//EKIK 
	this->turn = kratka;
	if (this->cache != nullptr)
	{
		this->cache->clear();
	}
	this->cache = std::make_shared< std::map<int, int> >();
	this->matrix = matrix;
	this->wielkosc = rozmiarSiatki;
	this->iloscElementow = rozmiarSiatki * rozmiarSiatki;

	return algorytm();
	//return testujRuchLosowo();
}

int KolkoKrzyzyk::testujRuchLosowo()
{
	int limit = 1000;
	while (true)
	{
		if (--limit == 0)
		{
			return NIEPOPRAWNA_KRATKA;
		}
		int kratka = (rand() * (int)(this->wielkosc * this->wielkosc) / RAND_MAX);
		int y = kratka / this->wielkosc;
		int x = kratka - (y * this->wielkosc);
		if (this->matrix->ustaw(y, x, Pusta))
		{
			return kratka;
		}
	}
}

int KolkoKrzyzyk::algorytm()
{
	int odpowiedz = NIEPOPRAWNA_KRATKA;
	Pozycja poz;
	tempMatrix = this->matrix; //TODO
	alphaBeta(GLEBOKOSC, XZnak, this->matrix, ALFA, BETA, poz);
	return odpowiedz;
}

int KolkoKrzyzyk::alphaBeta(const int poziom, EKratka gracz, Matrix_Ptr gra, int alpha, int beta, Pozycja &poz)
{
	if (this->matrix->czyKoniecGry() || poziom == 0)
	{
		if (!this->matrix->czyKoniecGry()) poz = (this->matrix->pobierzMozliweRuchy())->at(0);
		return pobierzPunkty(this->matrix);
	}
	ListaPozycji_Ptr dzieci = this->matrix->pobierzMozliweRuchy();

	permutuj(dzieci->begin(), dzieci->end());

	if (gracz == XZnak)
	{
		for (std::vector<Pozycja>::iterator it = dzieci->begin(); it != dzieci->end(); it++)
		{
			Matrix_Ptr dziecko = gra->wykonajRuch(*it);
			Pozycja temp;
			int punkty = alphaBeta(poziom - 1, OZnak, dziecko, alpha, beta, temp); //0Znak == !gracz
			if (punkty > alpha)
			{
				alpha = punkty; // We have found a better best move
				poz = *it;
			}
			if (alpha >= beta)
			{
				poz = *it;
				return alpha; // Beta Cut Off
			}
		}
		return alpha; // This is our best move
	}
	else {
		for (std::vector<Pozycja>::iterator it = dzieci->begin(); it != dzieci->end(); it++)
		{
			Matrix_Ptr dziecko = gra->wykonajRuch(*it);
			Pozycja temp;
			int punkty = alphaBeta(poziom - 1, XZnak, dziecko, alpha, beta, temp);
			if (punkty < beta)
			{
				beta = punkty; // Opponent has found a better worse move
				poz = *it;
			}
			if (alpha >= beta)
			{
				poz = *it;
				return beta; // Alpha Cut Off
			}
		}
		return beta; // This is the opponent's best move
	}
}

void KolkoKrzyzyk::permutuj(std::vector<Pozycja>::iterator l, std::vector<Pozycja>::iterator r)
{
	ListaPozycji_Ptr dodatnie, ujemne, zero;
	for (std::vector<Pozycja>::iterator it = l; it != r; it++)
	{
		int punkty = pobierzPunkty(tempMatrix->wykonajRuch(*it));
		if (punkty < 0) ujemne->push_back(*it);
		else if (punkty == 0) zero->push_back(*it);
		else dodatnie->push_back(*it);
	}
	std::random_shuffle(zero->begin(), zero->end());
	std::sort(dodatnie->begin(), dodatnie->end(), doCompare(std::make_shared<KolkoKrzyzyk>(*this)));
	std::sort(ujemne->begin(), ujemne->end(), doCompare(std::make_shared<KolkoKrzyzyk>(*this)));

	std::vector<Pozycja>::iterator i = l;

	while (!dodatnie->empty() || !zero->empty() || !ujemne->empty())
	{
		if (!dodatnie->empty()) {
			*(i++) = *(dodatnie->rbegin());
			dodatnie->pop_back();
		}
		if (!zero->empty()) {
			*(i++) = *(zero->rbegin());
			zero->pop_back();
		}
		if (!ujemne->empty()) {
			*(i++) = *(ujemne->rbegin());
			ujemne->pop_back();
		}
	}
}

int KolkoKrzyzyk::wyliczPunkty(int x, int o)
{
	int punkty = 0;
	if (o == 0) punkty += WAGI[x];
	if (x == 0) punkty -= WAGI[o];
	return punkty;
}

int KolkoKrzyzyk::pobierzPunkty(Matrix_Ptr gra)
{
	int punkty = 0;
	for (int i = 0; i < this->wielkosc; i++)
	{
		punkty += wyliczPunkty(gra->liczRzedem(i, XZnak), gra->liczRzedem(i, OZnak));
		punkty += wyliczPunkty(gra->liczKolumnowo(i, XZnak), gra->liczKolumnowo(i, OZnak));
	}
	punkty += wyliczPunkty(gra->liczPoPrzekatnej1(XZnak), gra->liczPoPrzekatnej1(OZnak));
	punkty += wyliczPunkty(gra->liczPoPrzekatnej2(XZnak), gra->liczPoPrzekatnej2(OZnak));
	return punkty;
}

bool KolkoKrzyzyk::wazanie(Pozycja a, Pozycja b)
{
	int punktyA = pobierzPunkty(tempMatrix->wykonajRuch(a));
	int punktyB = pobierzPunkty(tempMatrix->wykonajRuch(b));
	if (punktyA < 0) punktyA = -punktyA;
	if (punktyB < 0) punktyB = -punktyB;
	return (punktyA < punktyB);
}

