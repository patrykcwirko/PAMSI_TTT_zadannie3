#pragma once

#include <memory>
#include <vector>
#include "Matrix.h"
#include "Typy.h"

class Matrix;
typedef std::shared_ptr<Matrix> Matrix_Ptr;

class Matrix
{

private:
	int rozmiar;
	Tablica_Ptr data;

public:
	Matrix();
	Matrix(int rozmiar);
	Matrix(ListaKratek_Ptr pozycje, int rozmiar);
	virtual ~Matrix();

	void clearData();
	void init();
	void init(ListaKratek_Ptr pozycje);
	EKratka pobierz(int x, int y);
	bool ustaw(int x, int y, EKratka kratka);

	int indeks(int , int );
	Pozycja_Ptr pozycja(int index);

	bool czyWolne(Pozycja &poz);
	ListaPozycji_Ptr pobierzMozliweRuchy();
	ListaKratek_Ptr pobierzDane();
	int liczRzedem(int row, EKratka player);
	int liczKolumnowo(int column, EKratka player);
	int liczPoPrzekatnej1(EKratka player);
	int liczPoPrzekatnej2(EKratka player);
};

