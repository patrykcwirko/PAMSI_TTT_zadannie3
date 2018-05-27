#pragma once
#include <memory>
#include <vector>
#include "Ustawienia.h"
#include "KolkoKrzyzyk.h"

#define ZMNIEJSZENIE 0.8

typedef std::shared_ptr< std::string > String_Ptr;

class Siatka
{
private:
	Ustawienia_Ptr ustawienia;
	void narysujSiatke(HDC DC);
	void narysujKrzyzyk(HDC DC, HBRUSH Brush, HBRUSH MBrush ,int a, int b);
	void narysujKolko(HDC DC, HBRUSH Brush, HBRUSH MBrush, int a, int b);

public:
	Siatka();

	Siatka(Ustawienia_Ptr ustawienia);

	virtual ~Siatka();

	void ustawParametry(Ustawienia_Ptr ustawienia);

	void ustawWielkosc(int iloscWRzedzie);

	void narysuj(HWND *Window, KolkoKrzyzyk_Ptr ptrKik);

	String_Ptr podajKtoWygral(KolkoKrzyzyk_Ptr ptrKik);

	void zaznaczKlikniecie(KolkoKrzyzyk_Ptr ptrKik, LPARAM LParam);

};

typedef std::shared_ptr<Siatka> Siatka_Ptr;

Siatka::Siatka() : ustawienia(nullptr)
{
	this->ustawienia = std::make_shared<Ustawienia>();
}

Siatka::Siatka(Ustawienia_Ptr ustawienia) : ustawienia(nullptr)
{
	this->ustawienia = ustawienia;
}

void Siatka::ustawWielkosc(int iloscWRzedzie)
{
	this->ustawienia = std::make_shared<Ustawienia>(iloscWRzedzie);
}

Siatka::~Siatka()
{
}

void Siatka::ustawParametry(Ustawienia_Ptr ustawienia)
{
	this->ustawienia = ustawienia;
}

void Siatka::narysuj(HWND *Window, KolkoKrzyzyk_Ptr ptrKik)
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

void Siatka::narysujSiatke(HDC DC)
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

void Siatka::narysujKrzyzyk(HDC DC, HBRUSH Brush, HBRUSH MBrush, int x, int y)
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

void Siatka::narysujKolko(HDC DC, HBRUSH Brush, HBRUSH MBrush, int x, int y)
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

String_Ptr Siatka::podajKtoWygral(KolkoKrzyzyk_Ptr ptrKik)
{
	std::string wygral;
	if (ptrKik->status() == G1Wygrywa)
	{
		wygral = "X wygral.";
	}
	if (ptrKik->status() == G2Wygrywa)
	{
		wygral = "O wygral.";
	}
	if (ptrKik->status() == Remis)
	{
		wygral = "Remis";
	}
	return std::make_shared<std::string>( wygral);
}

void Siatka::zaznaczKlikniecie(KolkoKrzyzyk_Ptr ptrKik, LPARAM lParam)
{
	int x = 0, y = 0;
	int dlKratki = (int)(TDLUGOSC / ustawienia->ilosc());
	for (x = 0; x < this->ustawienia->ilosc(); x++)
	{
		for (y = 0; y < this->ustawienia->ilosc(); y++)
		{
			if (LOWORD(lParam) >= y * dlKratki && LOWORD(lParam) < (y * dlKratki) + dlKratki)
			{
				if (HIWORD(lParam) >= (x * dlKratki) && HIWORD(lParam) <(x * dlKratki) + dlKratki)
				{
					int kratka = y + (x * this->ustawienia->ilosc());
					if (ptrKik->ustaw(kratka) == false) { continue; }
					if (ptrKik->czyRuchKomp() )
					{
						ptrKik->wykonjaRuchKomp();
					}
				}
			}
		}
	}
}

