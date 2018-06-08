#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix() : rozmiar(0), ruchyWyczerpane(0), data(nullptr)
{
	this->data = std::make_shared< Tablica >();
	init();
}

Matrix::Matrix(int rozmiar)
{
	this->ruchyWyczerpane = 0;
	this->data = std::make_shared< Tablica >();
	this->rozmiar = rozmiar;
	init();
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
	for (int i = 0; i < this->rozmiar; i++)
	{
		std::vector <EKratka> row;
		for (int j = 0; j < this->rozmiar; j++)
		{
			row.push_back(Pusta);
		}
		this->data->push_back(row);
	}
}

void Matrix::init(ListaKratek_Ptr pozycje)
{
	clearData();

	for (int i = 0; i < this->rozmiar; i++)
	{
		std::vector <EKratka> row;
		for (int j = 0; j < this->rozmiar; j++)
		{
			int idx = indeks(i, j);
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

EKratka Matrix::pobierz(int kratka)
{
	int x = kratka / this->rozmiar;
	int y = kratka - (x* this->rozmiar);
	return pobierz(x, y);
}

EKratka Matrix::pobierz(int x, int y)
{
	//z kolumy i potem wiersza
	return this->data->at(x).at(y);
}

bool Matrix::ustaw(int x, int y, EKratka kratka)
{
	if ((this->data->at(x).at(y) == Pusta)) 
	{
		this->data->at(x).at(y) = kratka;
		return true;
	}
	return false;
}

bool Matrix::ustaw(int index, EKratka kratka)
{
	Pozycja_Ptr poz = pozycja(index);
	return ustaw(poz->x, poz->y, kratka);
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
	for (int i = 0; i < this->rozmiar; i++)
	{
		for (int j = 0; j < this->rozmiar; j++)
		{
			if (i == poz.y && j == poz.x)
			{
				if ((temp->ruchyWyczerpane % 2) == 0)
				{
					temp->ustaw(i, j, XZnak);
				}
				else {
					temp->ustaw(i, j, OZnak);
				}
				temp->ruchyWyczerpane = ruchyWyczerpane + 1;
			}
			else {
				temp->ustaw(i, j, this->data->at(i).at(j));
			}
		}
	}
	return temp;
}

ListaPozycji_Ptr Matrix::pobierzMozliweRuchy()
{
	ListaPozycji_Ptr lista = std::make_shared<ListaPozycji>();
	Pozycja temp;
	for (int i = 0; i < this->rozmiar; i++)
	{
		for (int j = 0; j < this->rozmiar; j++)
		{
			if (this->data->at(i).at(j) == Pusta)
			{
				temp.y = i;
				temp.x = j;
				lista->push_back(temp);
			}
		}
	}
	return lista;
}

ListaKratek_Ptr Matrix::pobierzDane()
{
	ListaKratek_Ptr lista = std::make_shared<ListaKratek>();
	for (int i = 0; i < this->rozmiar; i++)
	{
		for (int j = 0; j < this->rozmiar; j++)
		{
			EKratka k = this->data->at(i).at(j);
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
	for (int j = 0; j < this->rozmiar; j++)
	{
		if (this->data->at(row).at(j) == player)
		{
			counter++;
		}
	}
	return counter;
}
int Matrix::liczKolumnowo(int column, EKratka player)
{
	int counter = 0;
	for (int i = 0; i < this->rozmiar; i++)
	{
		Pozycja_Ptr poz = pozycja(i);
		if (this->data->at(poz->x).at(poz->y) == player)
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
