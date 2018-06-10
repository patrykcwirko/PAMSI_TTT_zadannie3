#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix() : rozmiar(0), data(nullptr)
{
	this->data = std::make_shared< Tablica >();
	init();
}

Matrix::Matrix(int rozmiar)
{
	this->data = std::make_shared< Tablica >();
	this->rozmiar = rozmiar;
	init();
}

Matrix::Matrix(ListaKratek_Ptr pozycje, int rozmiar)
{
	this->data = std::make_shared< Tablica >();
	this->rozmiar = rozmiar;
	init(pozycje);
}

Matrix::~Matrix()
{
}

void Matrix::clearData()
{
	std::vector< std::vector<EKratka> >::iterator row;
	std::vector<EKratka>::iterator col;
	for (row = this->data->begin(); row != this->data->end(); row++)
	{
		if (!row->empty())
		{
			row->clear();
		}
	}
	this->data->clear();
}

void Matrix::init()
{
	clearData();
	for (int y = 0; y < this->rozmiar; y++)
	{
		std::vector <EKratka> row;
		for (int x = 0; x < this->rozmiar; x++)
		{
			row.push_back(Pusta);
		}
		this->data->push_back(row);
	}
}

void Matrix::init(ListaKratek_Ptr pozycje)
{
	clearData();
	for (int y = 0; y < this->rozmiar; y++)
	{
		std::vector <EKratka> row;
		for (int x = 0; x < this->rozmiar; x++)
		{
			int idx = indeks(x, y); 
			EKratka k = Pusta;
			if (XZnak == pozycje->at(idx))
			{
				k = XZnak; 
			}
			else if (OZnak == pozycje->at(idx)) {
				k = OZnak;
			}
			row.push_back(k);
		}
		this->data->push_back(row);
	}
}

EKratka Matrix::pobierz(int x, int y)
{
	//z kolumy i potem wiersza
	return this->data->at(y).at(x);
}

bool Matrix::ustaw(int x, int y, EKratka kratka)
{
	this->data->at(y).at(x) = kratka;
	return true;
	//if (true || (this->data->at(y).at(x) == Pusta)) 
	//{
	//	this->data->at(y).at(x) = kratka;
	//	return true;
	//}
	//return false;
}

int Matrix::indeks(int x, int y)
{
	return (y * this->rozmiar + x);
}

Pozycja_Ptr Matrix::pozycja(int index)
{
	int y = index / this->rozmiar;
	int x = index - (y * this->rozmiar);
	Pozycja p = { x, y };
	return std::make_shared<Pozycja>(p);
}

bool Matrix::czyWolne(Pozycja &poz)
{
	return (this->data->at(poz.x).at(poz.y) == Pusta);
}

ListaPozycji_Ptr Matrix::pobierzMozliweRuchy()
{
	ListaPozycji_Ptr lista = std::make_shared<ListaPozycji>();
	Pozycja temp;
	for (int y = 0; y < this->rozmiar; y++)
	{
		for (int x = 0; x < this->rozmiar; x++)
		{
			if (this->data->at(y).at(x) == Pusta)
			{
				temp.y = y;
				temp.x = x;
				lista->push_back(temp);
			}
		}
	}
	return lista;
}

ListaKratek_Ptr Matrix::pobierzDane()
{
	ListaKratek_Ptr lista = std::make_shared<ListaKratek>();
	for (int y = 0; y < this->rozmiar; y++)
	{
		std::vector <EKratka> row;
		for (int x = 0; x < this->rozmiar; x++)
		{
			int idx = indeks(x, y);
			EKratka k = Pusta;
			if (XZnak == this->data->at(y).at(x))
			{
				k = XZnak;
			}
			else if (OZnak == this->data->at(y).at(x)) {
				k = OZnak;
			}
			lista->push_back(k);
		}
	}
	return lista;
}

int Matrix::liczRzedem(int row, EKratka player) {
	int counter = 0;
	for (int x = 0; x < this->rozmiar; x++)
	{
		if (this->data->at(row).at(x) == player)
		{
			counter++;
		}
	}
	return counter;
}
int Matrix::liczKolumnowo(int column, EKratka player)
{
	int counter = 0;
	for (int y = 0; y < this->rozmiar; y++)
	{
		if (this->data->at(y).at(column) == player)
		{
			counter++;
		}
	}
	return counter;
}

int Matrix::liczPoPrzekatnej1(EKratka player)
{
	int counter = 0;
	for (int i = 0; i < this->rozmiar; i++)
	{
		if (this->data->at(i).at(i) == player)
		{
			counter++;
		}
	}
	return counter;
}

int Matrix::liczPoPrzekatnej2(EKratka player)
{
	int counter = 0;
	for (int i = 0; i < this->rozmiar; i++)
	{
		if (this->data->at(i).at(this->rozmiar - 1 - i) == player)
		{
			counter++;
		}
	}
	return counter;
}
