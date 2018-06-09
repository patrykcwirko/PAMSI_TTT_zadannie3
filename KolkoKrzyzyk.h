#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "Matrix.h"
#include <cmath> 
#include "Ustawienia.h"
#include "Narzedzia.h"
#include "Typy.h"

#define GLEBOKOSC	8
#define BETA		1000000
#define ALFA		-BETA

class KolkoKrzyzyk;
typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

// gracz gra z XZnak
class KolkoKrzyzyk
{
private:
	bool terazRuchGracza;
	EKIK status;
	int ruchyWyczerpane;
	Matrix_Ptr matrix;
	Ustawienia_Ptr ustawienia;

	static int wielkosc;
	static Wynik_Ptr ruchNaMax(Matrix_Ptr matrix, int glebokosc, int alpha, int beta);
	static Wynik_Ptr ruchNaMin(Matrix_Ptr matrix, int glebokosc, int alpha, int beta);
	static bool czyKoniec(Matrix_Ptr matrix);
	static int policzPunkty(Matrix_Ptr matrix, int glebokosc);
	static bool czyKoniecGry(Matrix_Ptr matrix);
	static bool czyWygral(Matrix_Ptr matrix, EKratka gracz);

	void log(bool zrodlo, Pozycja_Ptr poz, EKratka kratka);
	Wynik_Ptr testujRuchLosowo();
	Wynik_Ptr algorytm(EKratka gracz);
	void zapamietajWynik();

public:
	KolkoKrzyzyk();
	KolkoKrzyzyk(Ustawienia_Ptr ustawienia);
	virtual ~KolkoKrzyzyk();
	void reset();
	void ustawParametry(Ustawienia_Ptr ustawienia);
	void wykonajRuchKomp(EKratka OZnak);
	bool czyTerazRuchGracza();
	bool ustawKratke(Wynik_Ptr wynik);
	EKIK czyjRuch();
	EKIK jakiStatus();
	EKratka pobierz(int x, int y);
};


