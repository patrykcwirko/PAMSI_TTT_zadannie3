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
	this->matrix = std::make_shared< Matrix >(this->wielkosc);
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
	int x = kratka / this->ustawienia->pobierzRozmiarSiatki();
	int y = kratka - (x * this->ustawienia->pobierzRozmiarSiatki());
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
	//TEST 
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
	int punkty = NIEPOPRAWNA;
	int ilosc = this->wielkosc * this->wielkosc;
	for (int i = 0; i < ilosc; ++i)
	{
		if (this->matrix->pobierz(i) == Pusta)
		{
			this->matrix->ustaw(i, OZnak);
			Matrix_Ptr tmpMatrix = std::make_shared<Matrix>(this->wielkosc);
			tmpMatrix->init(this->matrix->pobierzDane());
			int tempPunkty = -alphaBeta(tmpMatrix, OZnak, true, ALFA, BETA);
			this->matrix->ustaw(i, Pusta);
			if (tempPunkty > punkty)
			{
				punkty = tempPunkty;
				odpowiedz = i;
			}
		}
	}
	return odpowiedz;
}

int KolkoKrzyzyk::alphaBeta(Matrix_Ptr matrix, EKratka gracz, bool znaleziono, int alfa, int beta)
{
	if (this->matrix->czyKoniecGry())
	{
		int a = std::abs(alfa);
		int b = std::abs(beta);
		return (a > b) ? a : b;
	}

	int ilosc = this->wielkosc * this->wielkosc;
	for (int i = 0; i < ilosc; ++i)
	{
		if (this->matrix->pobierz(i) == Pusta)
		{
			this->matrix->ustaw(i, gracz);
			//((gracz == XZnak) ? OZnak : XZnak)
			int najlepszy = -alphaBeta(matrix, gracz, !znaleziono, alfa, beta);
			if (znaleziono == false)
			{
				if (najlepszy < beta)
				{
					beta = najlepszy;
					if (alfa >= beta)
					{
						this->matrix->ustaw(i, Pusta);
						return beta;
					}
				}
			}
			else
			{
				if (najlepszy > alfa)
				{
					alfa = najlepszy;
					if (alfa >= beta)
					{
						this->matrix->ustaw(i, Pusta);
						return alfa;
					}
				}
			}
			this->matrix->ustaw(i, Pusta);
		}
	}
	return (znaleziono) ? alfa : beta;
}

