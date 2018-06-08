#include "stdafx.h"
#include "KolkoKrzyzyk.h"

int KolkoKrzyzyk::wielkosc = DFLT_ILOSC_W_RZEDZIE;

KolkoKrzyzyk::KolkoKrzyzyk() : 
	terazRuchGracza(true), ruchyWyczerpane(0), matrix(nullptr), tempMatrix(nullptr), ustawienia(nullptr)
{
	this->ustawienia = std::make_shared< Ustawienia >();
	this->wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->matrix = std::make_shared< Matrix >();
	this->matrix->init();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : 
	terazRuchGracza(true), ruchyWyczerpane(0), matrix(nullptr), tempMatrix(nullptr), ustawienia(nullptr)
{
	KolkoKrzyzyk::wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->ustawienia = ustawienia;
	this->matrix = std::make_shared< Matrix >(this->wielkosc);
	this->matrix->init();
}

KolkoKrzyzyk::~KolkoKrzyzyk()
{
}

void KolkoKrzyzyk::reset()
{
	this->matrix->init();
}

void KolkoKrzyzyk::ustawParametry(Ustawienia_Ptr ustawienia)
{
	KolkoKrzyzyk::wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->ustawienia = ustawienia;
	this->matrix->init();
}

bool KolkoKrzyzyk::ustawKratke(int kratka)
{
	int ilKratek = KolkoKrzyzyk::wielkosc * KolkoKrzyzyk::wielkosc;
	if (kratka <0 || kratka >ilKratek-1) { return false; }

	int x = kratka / KolkoKrzyzyk::wielkosc;
	int y = kratka - (x * KolkoKrzyzyk::wielkosc);
	std::string ctr2 = Narzedzia::kratkaNaString(this->matrix->pobierz(x, y)); 
	Narzedzia::printLog(std::to_string(x) + "," + std::to_string(y) + ":" + ctr2);

	if (this->matrix->pobierz(kratka) != Pusta )
	{
		return false;
	}
	if (this->status() == RuchGracza) 
	{
		this->matrix->ustaw(kratka, XZnak);
		terazRuchGracza = false;
		return true;
	}
	if (this->status() == RuchKomputera)
	{
		this->matrix->ustaw(kratka, OZnak);
		terazRuchGracza = true;
	}
	return true;
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
	int najlepszyRuch = algorytm(OZnak);
	//TEST 
	//int najlepszyRuch = testujRuchLosowo();
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

int KolkoKrzyzyk::testujRuchLosowo()
{
	int limit = 1000;
	while (true)
	{
		if (--limit == 0)
		{
			return NIEPOPRAWNA;
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

int KolkoKrzyzyk::algorytm(EKratka gracz)
{
	Wynik_Ptr wynik;
	if (gracz == XZnak) {
		wynik = ruchNaMax(this->matrix, 0, INT16_MIN, INT16_MAX);
	}
	else {
		wynik = ruchNaMin(this->matrix, 0, INT16_MIN, INT16_MAX);
	}
	return this->matrix->indeks(wynik->pozycja->x, wynik->pozycja->y);
}

Wynik_Ptr KolkoKrzyzyk::ruchNaMax(Matrix_Ptr matrix, int glebokosc, int alpha, int beta) {
	if (czyKoniec(matrix)) {
		return std::make_shared<Wynik>(policzPunkty(matrix, glebokosc), std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	}
	Wynik_Ptr maxRuch = std::make_shared<Wynik>(INT16_MIN, std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));

	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		for (int j = 0; j < KolkoKrzyzyk::wielkosc; ++j) {
			if (matrix->pobierz(i, j) == Pusta) {
				matrix->ustaw(i, j, XZnak);
				Wynik_Ptr ruch = ruchNaMin(matrix, glebokosc + 1, alpha, beta);
				matrix->ustaw(i, j, Pusta);
				if (ruch->punkty > maxRuch->punkty) {
					maxRuch->punkty = ruch->punkty;
					maxRuch->pozycja->x = i;
					maxRuch->pozycja->y = j;
				}
				if (ruch->punkty >= beta) {
					return maxRuch;
				}
				if (ruch->punkty > alpha) {
					alpha = ruch->punkty;
				}
			}
		}
	}

	return maxRuch;
}

Wynik_Ptr KolkoKrzyzyk::ruchNaMin(Matrix_Ptr matrix, int glebokosc, int alpha, int beta) {
	if (czyKoniec(matrix)) {
		return std::make_shared<Wynik>(policzPunkty(matrix, glebokosc), std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	}
	Wynik_Ptr minRuch = std::make_shared<Wynik>(INT16_MAX, std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		for (int j = 0; j < KolkoKrzyzyk::wielkosc; ++j) {
			if (matrix->pobierz(i, j) == Pusta) {
				matrix->ustaw(i, j, OZnak);
				Wynik_Ptr ruch = ruchNaMax(matrix, glebokosc + 1, alpha, beta);
				matrix->ustaw(i, j, Pusta);

				if (ruch->punkty < minRuch->punkty) {
					minRuch->punkty = ruch->punkty;
					minRuch->pozycja->x = i;
					minRuch->pozycja->y = j;
				}

				if (ruch->punkty <= alpha) {
					return minRuch;
				}

				if (ruch->punkty < beta) {
					beta = ruch->punkty;
				}
			}
		}
	}

	return minRuch;
}

bool KolkoKrzyzyk::czyWygral(Matrix_Ptr matrix, EKratka gracz) {
	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		bool czyWierszami = true, czyKolumnami = true;
		for (int j = 0; j < KolkoKrzyzyk::wielkosc; ++j) {
			if (matrix->pobierz(i, j) != gracz) {
				czyWierszami = false;
			}

			if (matrix->pobierz(i, j) != gracz) {
				czyKolumnami = false;
			}
		}

		if (czyWierszami || czyKolumnami) {
			return true;
		}
	}

	bool czyPrzekatna = true, czyPrzekatnaBis = true;
	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		if (matrix->pobierz(i, i) != gracz) {
			czyPrzekatna = false;
		}
		if (matrix->pobierz(KolkoKrzyzyk::wielkosc - 1 - i, i) != gracz) {
			czyPrzekatnaBis = false;
		}
	}
	return czyPrzekatna || czyPrzekatnaBis;
}

int KolkoKrzyzyk::policzPunkty(Matrix_Ptr matrix, int glebokosc) {
	if (czyWygral(matrix, XZnak)) {
		return 10 - glebokosc;
	}
	else if (czyWygral(matrix, OZnak)) {
		return glebokosc - 10;
	}
	return 0;
}

bool KolkoKrzyzyk::czyKoniec(Matrix_Ptr matrix) {
	return czyWygral(matrix, XZnak) || czyWygral(matrix, OZnak) || czyKoniecGry(matrix);
}

bool KolkoKrzyzyk::czyKoniecGry(Matrix_Ptr matrix) {
	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		for (int j = 0; j < KolkoKrzyzyk::wielkosc; ++j) {
			if (matrix->pobierz(i, j) == Pusta) {
				return false;
			}
		}
	}

	return true;
}
