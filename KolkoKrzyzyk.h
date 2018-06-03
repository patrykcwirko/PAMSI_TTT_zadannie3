#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Typy.h"
#include "Ustawienia.h"
#include "Minmax.h"

class KolkoKrzyzyk
{
private:
	int wielkosc;
	bool terazRuchGracza;
	Matrix_Ptr matrix;
	Ustawienia_Ptr ustawienia;
	MinMax_Ptr minmax;

public:
	KolkoKrzyzyk();
	KolkoKrzyzyk(Ustawienia_Ptr ustawienia);
	virtual ~KolkoKrzyzyk();
	void ustawParametry(Ustawienia_Ptr ustawienia);
	void ustawWielkosc(int wielkosc);
	bool ustawKratke(int kratka);
	EKratka pobierz(int kratka);
	EKratka pobierz(int x, int y);
	void init();
	EKIK status();
	bool czyRuchKomp();
	int wykonjaRuchKomp();
};

typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

