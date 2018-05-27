#pragma once
#include <memory>
#include <vector>
#include "Ustawienia.h"
#include "KolkoKrzyzyk.h"

#define ZMNIEJSZENIE 0.8

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
	void narysujSiatke(HDC DC);
	void narysujKrzyzyk(HDC DC, HBRUSH Brush, HBRUSH MBrush ,int a, int b);
	void narysujKolko(HDC DC, HBRUSH Brush, HBRUSH MBrush, int a, int b);

public:
	Siatka();

	Siatka(Ustawienia_Ptr ustawienia);

	virtual ~Siatka();

	void ustaw(Ustawienia_Ptr ustawienia);

	void ustaw(int iloscWRzedzie);

	T get(size_t kolumna, size_t wiersz);

	void set(size_t kolumna, size_t wiersz, T wartosc);

	void narysuj(HWND *Window, KolkoKrzyzyk_Ptr ptrKik);

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
void Siatka<T>::narysuj(HWND *Window, KolkoKrzyzyk_Ptr ptrKik)
{
	PAINTSTRUCT ps;
	HBRUSH MBrush;
	HBRUSH Brush = 0;
	HDC DC;
	InvalidateRect(*Window, NULL, true);
	DC = BeginPaint(*Window, &ps);
	Brush = CreateSolidBrush(RGB(255, 255, 255));
	MBrush = HBRUSH(SelectObject(DC, Brush));
	narysujSiatke(DC);
	int x= 0, y = 0;
	int iloscKratek = this->ustawienia->ilosc() *  this->ustawienia->ilosc();
	for (int i = 0; i<iloscKratek; i++)
	{
		x = i / this->ustawienia->ilosc();
		y = i - (x* this->ustawienia->ilosc() );
		x *= (int)(TDLUGOSC / ustawienia->ilosc());
		y *= (int)(TDLUGOSC / ustawienia->ilosc());
		if (ptrKik->pobierz(i) == XZnak)
		{
			narysujKrzyzyk(DC, Brush, MBrush, x, y);
		}
		if (ptrKik->pobierz(i) == OZnak)
		{
			narysujKolko(DC, Brush, MBrush, x, y);
		}
	}
	EndPaint(*Window, &ps);
	ReleaseDC(*Window, DC);
	DeleteObject(Brush);
	DeleteObject(MBrush);
}

template <class T>
void Siatka<T>::narysujSiatke(HDC DC)
{
	int x = 0, y = 0;
	int dlKratki = (int)(TDLUGOSC / ustawienia->ilosc());
	for (x = 0; x < this->ustawienia->ilosc(); x++)
	{
		for (y = 0; y < this->ustawienia->ilosc(); y++)
		{
			Rectangle(DC, y * dlKratki, x * dlKratki, (y * dlKratki) + dlKratki, (x * dlKratki) + dlKratki);
		}
	}
}

template <class T>
void Siatka<T>::narysujKrzyzyk(HDC DC, HBRUSH Brush, HBRUSH MBrush, int x, int y)
{
	DeleteObject(Brush);
	DeleteObject(MBrush);
	Brush = CreateSolidBrush(RGB(255, 0, 0));
	MBrush = HBRUSH(SelectObject(DC, Brush));
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN Pen2 = HPEN(SelectObject(DC, Pen));
	int dlKratki = (int)(TDLUGOSC / ustawienia->ilosc());
	int margines = (int)(0.1 * dlKratki);
	int dlZnaku = dlKratki - 2 * margines;
	MoveToEx(DC, y + margines, x + margines, NULL);
	LineTo(DC, y + dlZnaku, x + dlZnaku);
	MoveToEx(DC, y + margines, x + dlZnaku, NULL);
	LineTo(DC, y + dlZnaku, x + margines);
	DeleteObject(Pen);
	DeleteObject(Pen2);
}

template <class T>
void Siatka<T>::narysujKolko(HDC DC, HBRUSH Brush, HBRUSH MBrush, int x, int y)
{
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN Pen2 = HPEN(SelectObject(DC, Pen));
	DeleteObject(Brush);
	DeleteObject(MBrush);
	Brush = CreateSolidBrush(RGB(255, 255, 255));
	MBrush = HBRUSH(SelectObject(DC, Brush));
	int dlKratki = (int)(TDLUGOSC / ustawienia->ilosc());
	int margines = (int)(0.1 * dlKratki);
	int dlZnaku = dlKratki - 2 * margines;
	Ellipse(DC, y + margines, x + margines, y + dlZnaku, x + dlZnaku);
	DeleteObject(Pen);
	DeleteObject(Pen2);
}

template <class T>
using Siatka_Ptr = std::shared_ptr<Siatka<T> >;

