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
	int ruchyWyczerpane;
	Tablica_Ptr data;

public:
	Matrix();
	Matrix(int rozmiar);
	virtual ~Matrix();

	void init();
	void init(ListaKratek_Ptr pozycje);
	EKratka pobierz(int x, int y);
	EKratka pobierz(int index);
	bool ustaw(int x, int y, EKratka kratka);
	bool ustaw(int index, EKratka kratka);

	int indeks(int y, int x);
	Pozycja_Ptr pozycja(int index);

	bool czyWolne(Pozycja &poz);
	bool czyKoniecGry();
	bool czyRemis();
	ListaPozycji_Ptr pobierzMozliweRuchy();
	ListaKratek_Ptr pobierzDane();
	Matrix_Ptr wykonajRuch(Pozycja &poz);
	int liczRzedem(int row, EKratka player);
	int liczKolumnowo(int column, EKratka player);
	int liczPoPrzekatnej1(EKratka player);
	int liczPoPrzekatnej2(EKratka player);
};

