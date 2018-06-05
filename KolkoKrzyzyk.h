#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "Matrix.h"
#include "Ustawienia.h"
#include "Typy.h"
#include "Narzedzia.h"

#define GLEBOKOSC	8
#define BETA		(2 * 1048576)
#define ALFA		-BETA

const int WAGI[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576 };


class KolkoKrzyzyk;
typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

// gracz gra z XZnak
class KolkoKrzyzyk
{
private:
	int wielkosc;
	bool terazRuchGracza;
	int ruchyWyczerpane;
	int iloscElementow;
	EKratka turn;
	Matrix_Ptr matrix;
	Matrix_Ptr tempMatrix;
	MapIntInt_ptr cache;
	Ustawienia_Ptr ustawienia;

public:
	KolkoKrzyzyk();
	KolkoKrzyzyk(Ustawienia_Ptr ustawienia);
	virtual ~KolkoKrzyzyk();

	int nalepszyRuch(Matrix_Ptr matrix, int rozmiarSiatki, EKratka OZnak);

	void ustawParametry(Ustawienia_Ptr ustawienia);
	void ustawWielkosc(int wielkosc);
	bool ustawKratke(int kratka);
	void init();
	EKIK status();
	bool czyTerazRuchGracza();
	void wykonajRuchKomp(EKratka OZnak);
	EKratka pobierz(int x, int y);
	EKratka pobierz(int index);

private:
	int testujRuchLosowo();
	int algorytm();
	//---
	int alphaBeta(const int poziom, EKratka gracz, Matrix_Ptr gra, int alpha, int beta, Pozycja &poz);
	void permutuj(std::vector<Pozycja>::iterator l, std::vector<Pozycja>::iterator r);
	int wyliczPunkty(int x, int o);
	int pobierzPunkty(Matrix_Ptr gra);
	bool wazanie(Pozycja a, Pozycja b);

	struct doCompare
	{
		doCompare(KolkoKrzyzyk_Ptr mm) : m(mm) { }
		KolkoKrzyzyk_Ptr m;

		bool operator()(const Pozycja & a, const Pozycja & b)
		{
			return m->wazanie(a, b);
		}
	};
};


