#pragma once
#include <memory>
#include <vector>
#include "Ustawienia.h"

template <class T>
using CMatrix = std::vector<std::vector<T>>;

template <class T>
using CMatrix_Ptr = std::shared_ptr<CMatrix<T> >;

template <class T>
class CSiatka
{
private:
	CUstawienia_Ptr ustawienia;
	CMatrix_Ptr<T> siatka;

public:
	CSiatka();

	CSiatka(CUstawienia_Ptr ustawienia);

	void ustaw(CUstawienia_Ptr ustawienia);

	void ustaw(int iloscWRzedzie);

	T get( size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	virtual ~CSiatka();

private:
	void wyczyscSiatke();
};

template <class T>
CSiatka<T>::CSiatka() : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawienia = std::make_shared<CUstawienia>();
	this->siatka = std::make_shared< CMatrix<T> >();
}

template <class T>
CSiatka<T>::CSiatka(CUstawienia_Ptr ustawienia) : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawienia = ustawienia;
	this->siatka = make_shared< CMatrix<T> >();
}

template <class T>
void CSiatka<T>::ustaw(int iloscWRzedzie)
{
	this->ustawienia = std::make_shared<CUstawienia>(iloscWRzedzie);
	this->siatka = std::make_shared< CMatrix<T> >();
}

template <class T>
CSiatka<T>::~CSiatka()
{
}

template <class T>
void CSiatka<T>::ustaw(CUstawienia_Ptr ustawienia)
{
	this->ustawienia = ustawienia;
	if (this->siatka != nullptr)
	{
		wyczyscSiatke();
	}
	this->siatka = make_shared< CMatrix<T> >();
}


template <class T>
T CSiatka<T>::get(size_t kolumna, size_t wiersz)
{
	return this->siatka[kolumna][wiersz];
}


template <class T>
void CSiatka<T>::set(size_t kolumna, size_t wiersz, T wartosc)
{
	this->siatka[kolumna][wiersz] = wartosc;
}

template <class T>
void CSiatka<T>::wyczyscSiatke()
{	

}

template <class T>
using Siatka_Ptr = std::shared_ptr<CSiatka<T> >;
