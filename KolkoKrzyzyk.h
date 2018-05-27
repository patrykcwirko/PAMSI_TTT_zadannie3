#pragma once

#include <memory>
#include <vector>
#include "Ustawienia.h"

enum EKIK 
{
	G1Wygrywa = 1, //1 
	G2Wygrywa,     //2
	G1Ruch,        //3
	G2Ruch,		   //4
	Remis	       //5
};

enum EKratka 
{
	Pusta,
	XZnak,
	OZnak
};

typedef std::vector<std::vector<EKratka>> Matrix;

typedef std::shared_ptr<Matrix> Matrix_Ptr;

class KolkoKrzyzyk
{
private:
	int wielkosc;
	Matrix_Ptr siatka;
	Ustawienia_Ptr ustawienia;

public:
	KolkoKrzyzyk();
	KolkoKrzyzyk(Ustawienia_Ptr ustawienia);
	virtual ~KolkoKrzyzyk();
	void ustawWielkosc(int wielkosc);
	EKratka get(size_t kolumna, size_t wiersz);
	void set(size_t kolumna, size_t wiersz, EKratka wartosc);
	bool ustaw(int kratka);
	EKratka pobierz(int kratka);
	void reset();
};

typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

