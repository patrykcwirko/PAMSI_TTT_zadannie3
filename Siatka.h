#pragma once
#include <memory>
#include "Ustawienia.h"

template <class T, size_t KOLUMN, size_t WIERSZY>
using Matrix = std::array<std::array<T, KOLUMN>, WIERSZY>;

template <class T, size_t KOLUMN, size_t WIERSZY>
using Matrix_Ptr = std::shared_ptr<Matrix<T, KOLUMN, WIERSZY> >;

template <class T, size_t ROZMIAR >
class Siatka
{
private:
	Ustawienia_Ptr ustawienia;
	Matrix_Ptr siatka;

public:
	Siatka();

	Siatka(Ustawienia_Ptr ustawienia);

	void ustaw(Ustawienia_Ptr ustawienia);

	T get( size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	virtual ~Siatka();
};


template <class T, size_t ROZMIAR >
Siatka::Siatka() : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawienia = std::make_shared<Ustawienia>(DFLT_ILOSC_W_RZEDZIE);
	this->siatka = std::make_shared< Matrix<T, DFLT_ILOSC_W_RZEDZIE, DFLT_ILOSC_W_RZEDZIE> >();
}


template <class T, size_t ROZMIAR >
Siatka::Siatka(Ustawienia_Ptr ustawienia) : ustawienia(nullptr), siatka(nullptr)
{
	this->ustawinia = ustawienia;
	this->siatka = make_shared< Matrix<T, ustawienia->ilosc(), ustawienia->ilosc()> >();
}


template <class T, size_t ROZMIAR >
Siatka::~Siatka()
{
}


template <class T, size_t ROZMIAR >
Siatka::ustaw(Ustawienia_Ptr ustawienia)
{
	this->ustawinia = ustawienia;
	this->siatka = make_shared< Matrix<T, ustawienia->ilosc(), ustawienia->ilosc()> >();
}


template <class T, size_t ROZMIAR >
T Siatka::get(size_t kolumna, size_t wiersz)
{
	return this->siatka[kolumna][wiersz];
}


template <class T, size_t ROZMIAR >
void Siatka::set(size_t kolumna, size_t wiersz, T wartosc)
{
	this->siatka[kolumna][wiersz] = wartosc;
}


template <class T, size_t ROZMIAR >
using Siatka_Ptr = std::shared_ptr<Siatka<T, ROZMIAR> >;
//std::shared_ptr<Siatka> p = std::make_shared<Siatka>();