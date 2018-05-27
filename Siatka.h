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

	virtual ~Siatka();

	void ustaw(Ustawienia_Ptr ustawienia);

	void ustaw(int iloscWRzedzie);

	T get(size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	void narysuj(HWND *Window);

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
	this->ustawienia = ustawienia;
	this->siatka = make_shared< Matrix<T> >();
}

template <class T>
void Siatka<T>::ustaw(int iloscWRzedzie)
{
	this->ustawienia = std::make_shared<Ustawienia>(iloscWRzedzie);
	this->siatka = std::make_shared< Matrix<T> >();
}

template <class T>
Siatka<T>::~Siatka()
{
}

template <class T>
void Siatka<T>::ustaw(Ustawienia_Ptr ustawienia)
{
	this->ustawienia = ustawienia;
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

}

template <class T>
void Siatka<T>::narysuj(HWND *Window)
{
	PAINTSTRUCT ps;
	HBRUSH MBrush;
	HBRUSH Brush = 0;
	HDC DC;
	InvalidateRect(*Window, NULL, true);
	DC = BeginPaint(*Window, &ps);
	Brush = CreateSolidBrush(RGB(255, 255, 255));
	MBrush = HBRUSH(SelectObject(DC, Brush));
	short a = 0, b = 0;
	for (a = 0; a < this->ustawienia->ilosc(); a++)
	{
		for (b = 0; b < this->ustawienia->ilosc(); b++)
		{
			Rectangle(DC, b * 10, a * 10, (b * 10) + 10, (a * 10) + 10);
		}
	}
}

template <class T>
using Siatka_Ptr = std::shared_ptr<Siatka<T> >;

