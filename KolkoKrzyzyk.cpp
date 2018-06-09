#include "stdafx.h"
#include "KolkoKrzyzyk.h"

int KolkoKrzyzyk::wielkosc = DFLT_ILOSC_W_RZEDZIE;

KolkoKrzyzyk::KolkoKrzyzyk() : 
	terazRuchGracza(true), status(Gramy), ruchyWyczerpane(0), matrix(nullptr), ustawienia(nullptr)
{
	this->ustawienia = std::make_shared< Ustawienia >();
	this->wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->matrix = std::make_shared< Matrix >();
	this->matrix->init();
}

KolkoKrzyzyk::KolkoKrzyzyk(Ustawienia_Ptr ustawienia) : 
	terazRuchGracza(true), status(Gramy), ruchyWyczerpane(0), matrix(nullptr), ustawienia(nullptr)
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
	this->terazRuchGracza = true;
	this->status = Gramy;
}

void KolkoKrzyzyk::ustawParametry(Ustawienia_Ptr ustawienia)
{
	KolkoKrzyzyk::wielkosc = ustawienia->pobierzRozmiarSiatki();
	this->ustawienia = ustawienia;
	this->matrix->init();
	this->terazRuchGracza = true;
}

bool KolkoKrzyzyk::ustawKratke(Wynik_Ptr wynik)
{
	bool usawionoKratke = false;
	if(wynik->ktoWygral() != Pusta)
	{
		return false;
	}
	if (wynik->pobierzPozycje()->x == NIEPOPRAWNA || wynik->pobierzPozycje()->y == NIEPOPRAWNA)
	{ 
		return false; 
	}
	if (this->matrix->pobierz(wynik->pobierzPozycje()->x, wynik->pobierzPozycje()->y) == Pusta )
	{
		if (this->czyjRuch() == RuchGracza)
		{
			this->matrix->ustaw(wynik->pobierzPozycje()->x, wynik->pobierzPozycje()->y, XZnak);
			usawionoKratke = true;
			log(true, wynik->pobierzPozycje(), XZnak);
		} else if (this->czyjRuch() == RuchKomputera)
		{
			this->matrix->ustaw(wynik->pobierzPozycje()->x, wynik->pobierzPozycje()->y, OZnak);
			usawionoKratke = true;
			log(true, wynik->pobierzPozycje(), OZnak);
		}
	}
	return usawionoKratke;
}

EKIK KolkoKrzyzyk::czyjRuch()
{
	if (terazRuchGracza)
	{
		return RuchGracza;
	}
	return RuchKomputera;
}

EKIK KolkoKrzyzyk::jakiStatus()
{
	return this->status;
}

bool KolkoKrzyzyk::czyTerazRuchGracza()
{
	return terazRuchGracza;
}

void KolkoKrzyzyk::wykonajRuchKomp(EKratka kratka)
{
	if (czyKoniec(this->matrix)) {
		zapamietajWynik();
		return;
	}
	this->terazRuchGracza = false;
	//Wynik_Ptr najlepszyRuch = algorytm(OZnak);
	//TEST 
	Wynik_Ptr najlepszyRuch = testujRuchLosowo();
	ustawKratke(najlepszyRuch);

	if (czyKoniec(this->matrix)) {
		zapamietajWynik();
		return;
	}
	this->terazRuchGracza = true;
}

EKratka KolkoKrzyzyk::pobierz(int x, int y)
{
	return this->matrix->pobierz(x, y);
}

Wynik_Ptr KolkoKrzyzyk::testujRuchLosowo()
{
	int iloscKratek = KolkoKrzyzyk::wielkosc * KolkoKrzyzyk::wielkosc;
	std::vector<int> wolneKratki = std::vector<int>();

	Pozycja poz = { NIEPOPRAWNA, NIEPOPRAWNA };
	Pozycja_Ptr ptrPoz = std::make_shared<Pozycja>(poz);
	for (int i = 0; i < iloscKratek; ++i) {
		ptrPoz = this->matrix->pozycja(i);
		if (matrix->pobierz(ptrPoz->x, ptrPoz->y) == Pusta)
		{
			wolneKratki.push_back(i);
		}
	}
	Wynik_Ptr wynik = std::make_shared<Wynik>(0, Pusta, ptrPoz);
	if (wolneKratki.empty()) {
		log(false, ptrPoz, OZnak);
	} else {
		int randIndex = (rand() * (int)(wolneKratki.size()-1) / RAND_MAX);
		int wolnyIndex = wolneKratki.at(randIndex);
		wolneKratki.clear();
		ptrPoz = this->matrix->pozycja(wolnyIndex);
		wynik = std::make_shared<Wynik>(0, Pusta, ptrPoz);
		log(false, ptrPoz, OZnak);
	}
	return wynik;
}

Wynik_Ptr KolkoKrzyzyk::algorytm(EKratka gracz)
{
	Pozycja poz = { NIEPOPRAWNA, NIEPOPRAWNA };
	Pozycja_Ptr ptrPoz = std::make_shared<Pozycja>(poz);
	Wynik_Ptr wynik = std::make_shared<Wynik>(0, Pusta, ptrPoz);
	ListaKratek_Ptr kratki = this->matrix->pobierzDane();
	Matrix_Ptr alfaBeta = std::make_shared< Matrix >(kratki, this->wielkosc);
	if (gracz == XZnak) {
		wynik = ruchNaMax(alfaBeta, 0, INT16_MIN, INT16_MAX);
	}
	else {
		wynik = ruchNaMin(alfaBeta, 0, INT16_MIN, INT16_MAX);
	}
	if (czyKoniec(alfaBeta)) {
		return std::make_shared<Wynik>(policzPunkty(alfaBeta, 0), alfaBeta->ktoWygral(), std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	}
	return wynik;
}

Wynik_Ptr KolkoKrzyzyk::ruchNaMax(Matrix_Ptr alfaBeta, int glebokosc, int alpha, int beta) {
	if (czyKoniec(alfaBeta)) {
		return std::make_shared<Wynik>(policzPunkty(alfaBeta, glebokosc), alfaBeta->ktoWygral(), std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	}
	Wynik_Ptr maxRuch = std::make_shared<Wynik>(INT16_MIN, std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));

	for (int y = 0; y < KolkoKrzyzyk::wielkosc; ++y) {
		for (int x = 0; x < KolkoKrzyzyk::wielkosc; ++x) {
			if (alfaBeta->pobierz(x, y) == Pusta) {
				alfaBeta->ustaw(x, y, XZnak);
				Wynik_Ptr ruch = ruchNaMin(alfaBeta, glebokosc + 1, alpha, beta);
				alfaBeta->ustaw(x, y, Pusta);
				if (ruch->punkty > maxRuch->punkty) {
					maxRuch->punkty = ruch->punkty;
					maxRuch->pozycja->x = x;
					maxRuch->pozycja->y = y;
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

Wynik_Ptr KolkoKrzyzyk::ruchNaMin(Matrix_Ptr alfaBeta, int glebokosc, int alpha, int beta) {
	if (czyKoniec(alfaBeta)) {
		return std::make_shared<Wynik>(policzPunkty(alfaBeta, glebokosc), std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	}
	Wynik_Ptr minRuch = std::make_shared<Wynik>(INT16_MAX, std::make_shared<Pozycja>(NIEPOPRAWNA, NIEPOPRAWNA));
	for (int y = 0; y < KolkoKrzyzyk::wielkosc; ++y) {
		for (int x = 0; x < KolkoKrzyzyk::wielkosc; ++x) {
			if (alfaBeta->pobierz(x, y) == Pusta) {
				alfaBeta->ustaw(x, y, OZnak);
				Wynik_Ptr ruch = ruchNaMax(alfaBeta, glebokosc + 1, alpha, beta);
				alfaBeta->ustaw(x, y, Pusta);

				if (ruch->punkty < minRuch->punkty) {
					minRuch->punkty = ruch->punkty;
					minRuch->pozycja->x = x;
					minRuch->pozycja->y = y;
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

int KolkoKrzyzyk::policzPunkty(Matrix_Ptr alfaBeta, int glebokosc) {
	if (czyWygral(alfaBeta, XZnak)) {
		return 100 - glebokosc;
	}
	else if (czyWygral(alfaBeta, OZnak)) {
		return glebokosc - 100;
	}
	return 0;
}

bool KolkoKrzyzyk::czyKoniec(Matrix_Ptr alfaBeta) {
	bool koniec = czyKoniecGry(alfaBeta);
	bool wygralX = czyWygral(alfaBeta, XZnak);
	bool wygralO = czyWygral(alfaBeta, OZnak);
	if (wygralX)
	{
		alfaBeta->ustawWygral(XZnak);
	}
	if (wygralO)
	{
		alfaBeta->ustawWygral(OZnak);
	}
	return koniec || wygralX || wygralO;
}

bool KolkoKrzyzyk::czyKoniecGry(Matrix_Ptr alfaBeta) {
	for (int y = 0; y < KolkoKrzyzyk::wielkosc; ++y) {
		for (int x = 0; x < KolkoKrzyzyk::wielkosc; ++x) {
			if (alfaBeta->pobierz(x, y) == Pusta) {
				return false;
			}
		}
	}

	return true;
}

bool KolkoKrzyzyk::czyWygral(Matrix_Ptr alfaBeta, EKratka gracz) {
	for (int y = 0; y < KolkoKrzyzyk::wielkosc; ++y) {
		bool czyWierszami = true, czyKolumnami = true;
		for (int x = 0; x < KolkoKrzyzyk::wielkosc; ++x) {
			if (alfaBeta->pobierz(x, y) != gracz) {
				czyWierszami = false;
			}

			if (alfaBeta->pobierz(y, x) != gracz) {
				czyKolumnami = false;
			}
		}
		if (czyWierszami || czyKolumnami) {
			return true;
		}
	}

	bool czyPrzekatna = true, czyPrzekatnaBis = true;
	for (int i = 0; i < KolkoKrzyzyk::wielkosc; ++i) {
		if (alfaBeta->pobierz(i, i) != gracz) {
			czyPrzekatna = false;
		}
		if (alfaBeta->pobierz(KolkoKrzyzyk::wielkosc - 1 - i, i) != gracz) {
			czyPrzekatnaBis = false;
		}
	}
	return czyPrzekatna || czyPrzekatnaBis;
}

void KolkoKrzyzyk::zapamietajWynik()
{
	EKIK wynik = (this->matrix->czyRemis()) ? Remis : Gramy;
	if (this->czyjRuch() != Remis)
	{
		EKratka wygral = this->matrix->ktoWygral();
		if (wygral == XZnak)
		{
			wynik = GraczWygrywa;
		}
		if (wygral == OZnak)
		{
			wynik = KomputerWygrywa;
		}
		this->status = wynik;
	}
}

void KolkoKrzyzyk::log(bool zrodlo, Pozycja_Ptr poz, EKratka kratka)
{
	std::string strKratka = Narzedzia::kratkaNaString(kratka);
	Narzedzia::printLog((zrodlo ? "KolkoKrzyzyk: " : "Wylosowane: ") + std::to_string(poz->x) + "," + std::to_string(poz->y) + ":" + strKratka);
}