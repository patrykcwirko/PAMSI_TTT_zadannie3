#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Ustawienia.h"
#include "Minmax.h"
#include "Typy.h"

class KolkoKrzyzyk
{
private:
	int wielkosc;
	bool ruchG1;
	Matrix_Ptr matrix;
	Ustawienia_Ptr ustawienia;

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
	void wykonjaRuchKomp();
};

typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

