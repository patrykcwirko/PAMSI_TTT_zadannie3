//#pragma once
#ifndef SIATKA_H
#define SIATKA_H

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

	virtual ~CSiatka();

	void ustaw(CUstawienia_Ptr ustawienia);

	void ustaw(int iloscWRzedzie);

	T get(size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	void narysuj(HWND *Window);

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
void CSiatka<T>::narysuj(HWND *Window)
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
	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 3; b++)
		{
			Rectangle(DC, b * 100, a * 100, (b * 100) + 100, (a * 100) + 100);
		}
	}
}

template <class T>
using Siatka_Ptr = std::shared_ptr<CSiatka<T> >;

#endif //SIATKA_H