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
	EKratka wygral;
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
	void ustawWygral(EKratka wygral);
	EKratka ktoWygral();
};

