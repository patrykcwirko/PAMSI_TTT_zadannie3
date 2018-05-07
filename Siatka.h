#pragma once
#include <memory>
#include <vector>
#include "Ustawienia.h"

template <class T>
using Matrix = std::vector<std::vector<T>>;

template <class T>
using Matrix_Ptr = std::shared_ptr<Matrix<T> >;

template <class T>
class Siatka
{
private:
	Ustawienia_Ptr ustawienia;
	Matrix_Ptr<T> siatka;

public:
	Siatka();

	Siatka(Ustawienia_Ptr ustawienia);

	void ustaw(Ustawienia_Ptr ustawienia);

	T get( size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	virtual ~Siatka();

private:
	void wyczyscSiatke();
};

template <class T>
Siatka<T>::Siatka() : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawienia = std::make_shared<Ustawienia>();
	this->siatka = std::make_shared< Matrix<T> >();
}

template <class T>
Siatka<T>::Siatka(Ustawienia_Ptr ustawienia) : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawinia = ustawienia;
	this->siatka = make_shared< Matrix<T> >();
}

template <class T>
Siatka<T>::~Siatka()
{
}

template <class T>
void Siatka<T>::ustaw(Ustawienia_Ptr ustawienia)
{
	this->ustawinia = ustawienia;
	if (this->siatka != nullptr)
	{
		wyczyscSiatke();
	}
	this->siatka = make_shared< Matrix<T> >();
}


template <class T>
T Siatka<T>::get(size_t kolumna, size_t wiersz)
{
	return this->siatka[kolumna][wiersz];
}


template <class T>
void Siatka<T>::set(size_t kolumna, size_t wiersz, T wartosc)
{
	this->siatka[kolumna][wiersz] = wartosc;
}

template <class T>
void Siatka<T>::wyczyscSiatke()
{
	vector< vector<T> >::iterator row;
	vector<T>::iterator col;
	for (row = this->siatka.begin(); row != this->siatka.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			*col = NULL;
		}
	}
}

template <class T>
using Siatka_Ptr = std::shared_ptr<Siatka<T> >;
