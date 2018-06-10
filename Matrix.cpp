#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix() : rozmiar(0), ruchyWyczerpane(0), wygral(Pusta), data(nullptr)
{
	this->data = std::make_shared< Tablica >();
	init();
}

Matrix::Matrix(int rozmiar)
{
	this->ruchyWyczerpane = 0;
	this->data = std::make_shared< Tablica >();
	this->rozmiar = rozmiar;
	this->wygral = Pusta;
	init();
}

Matrix::Matrix(ListaKratek_Ptr pozycje, int rozmiar)
{
	this->ruchyWyczerpane = 0;
	this->data = std::make_shared< Tablica >();
	this->rozmiar = rozmiar;
	this->wygral = Pusta;
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
	this->wygral = Pusta;
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
	this->wygral = Pusta;
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
	if (true || (this->data->at(y).at(x) == Pusta)) 
	{
		this->data->at(y).at(x) = kratka;
		return true;
	}
	return false;
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

Matrix_Ptr Matrix::wykonajRuch(Pozycja &poz)
{
	if (!czyWolne(poz)) return std::make_shared<Matrix>(*this);
	Matrix_Ptr temp = std::make_shared<Matrix>(this->rozmiar);
	for (int y = 0; y < this->rozmiar; y++)
	{
		for (int x = 0; x < this->rozmiar; x++)
		{
			if (y == poz.y && x == poz.x)
			{
				if ((temp->ruchyWyczerpane % 2) == 0)
				{
					temp->ustaw(x, y, XZnak);
				}
				else {
					temp->ustaw(x, y, OZnak);
				}
				temp->ruchyWyczerpane = ruchyWyczerpane + 1;
			}
			//TODO
			//else {
			//	temp->ustaw(x, y, this->data->at(i).at(j));
			//}
		}
	}
	return temp;
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

bool Matrix::czyKoniecGry()
{
	int temp = 0;
	for (int i = 0; i < this->rozmiar; i++)
	{
		temp = max(liczRzedem(i, XZnak), temp);
		temp = max(liczRzedem(i, OZnak), temp);
		temp = max(liczKolumnowo(i, XZnak), temp);
		temp = max(liczKolumnowo(i, OZnak), temp);
	}
	temp = max(temp, liczPoPrzekatnej1(XZnak));
	temp = max(temp, liczPoPrzekatnej1(OZnak));
	temp = max(temp, liczPoPrzekatnej2(XZnak));
	temp = max(temp, liczPoPrzekatnej2(OZnak));
	return ((temp == this->rozmiar) || (ruchyWyczerpane == this->rozmiar * this->rozmiar));
}

void Matrix::ustawWygral(EKratka wygral)
{
	this->wygral = wygral;
}

EKratka Matrix::ktoWygral()
{
	return this->wygral;
}

bool Matrix::czyRemis()
{
	int temp = this->rozmiar;
	for (int i = 0; i < this->rozmiar; i++)
	{
		temp = min(liczRzedem(i, XZnak), temp);
		temp = min(liczRzedem(i, OZnak), temp);
		temp = min(liczKolumnowo(i, XZnak), temp);
		temp = min(liczKolumnowo(i, OZnak), temp);
	}
	temp = min(temp, liczPoPrzekatnej1(XZnak));
	temp = min(temp, liczPoPrzekatnej1(OZnak));
	temp = min(temp, liczPoPrzekatnej2(XZnak));
	temp = min(temp, liczPoPrzekatnej2(OZnak));
	return ((temp != 0) || (this->ruchyWyczerpane == this->rozmiar * this->rozmiar));
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
