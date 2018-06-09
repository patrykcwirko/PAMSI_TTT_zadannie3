#include "stdafx.h"
#include "Siatka.h"


Siatka::Siatka() : ustawienia(nullptr)
{
	this->ustawienia = std::make_shared<Ustawienia>();
}

Siatka::Siatka(Ustawienia_Ptr ustawienia) : ustawienia(nullptr)
{
	this->ustawienia = ustawienia;
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
	int x = 0, y = 0;
	int iloscKratek = this->ustawienia->pobierzRozmiarSiatki() *  this->ustawienia->pobierzRozmiarSiatki();
	for (int i = 0; i<iloscKratek; i++)
	{
		x = i / this->ustawienia->pobierzRozmiarSiatki();
		y = i - (x* this->ustawienia->pobierzRozmiarSiatki());
		x *= (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
		y *= (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
		Pozycja_Ptr poz = pozycja(i);
		if (ptrKik->pobierz(poz->x, poz->y) == XZnak)
		{
			narysujKrzyzyk(DC, Brush, MBrush, x, y);
		} else if (ptrKik->pobierz(poz->x, poz->y) == OZnak)
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
	int dlKratki = (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
	for (x = 0; x < this->ustawienia->pobierzRozmiarSiatki(); x++)
	{
		for (y = 0; y < this->ustawienia->pobierzRozmiarSiatki(); y++)
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
	int dlKratki = (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
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
	int dlKratki = (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
	int margines = (int)(0.1 * dlKratki);
	int dlZnaku = dlKratki - 2 * margines;
	Ellipse(DC, y + margines, x + margines, y + dlZnaku, x + dlZnaku);
	DeleteObject(Pen);
	DeleteObject(Pen2);
}


Pozycja_Ptr Siatka::wyliczKratke(LPARAM lParam)
{
	Pozycja p = { NIEPOPRAWNA, NIEPOPRAWNA };
	Pozycja_Ptr poz = std::make_shared<Pozycja>(p);
	int y = 0, x = 0;
	int dlKratki = (int)(TDLUGOSC / ustawienia->pobierzRozmiarSiatki());
	for (y = 0; y < this->ustawienia->pobierzRozmiarSiatki(); y++)
	{
		for (x = 0; x < this->ustawienia->pobierzRozmiarSiatki(); x++)
		{
			if (LOWORD(lParam) >= x * dlKratki && LOWORD(lParam) < (x * dlKratki) + dlKratki)
			{
				if (HIWORD(lParam) >= (y * dlKratki) && HIWORD(lParam) <(y * dlKratki) + dlKratki)
				{
					Pozycja p = { x, y };
					Pozycja_Ptr poz = std::make_shared<Pozycja>(p);
					log(poz);
					return poz;
				}
			}
		}
	}
	return poz;
}

Pozycja_Ptr Siatka::pozycja(int index)
{
	int y = index / this->ustawienia->pobierzRozmiarSiatki();
	int x = index - (y * this->ustawienia->pobierzRozmiarSiatki());
	Pozycja p = { x, y };
	return std::make_shared<Pozycja>(p);
}

void Siatka::log(Pozycja_Ptr poz)
{
	Narzedzia::printLog("Siatka: " + std::to_string(poz->x) + "," + std::to_string(poz->y));
}