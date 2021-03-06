#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Ustawienia.h"
#include "KolkoKrzyzyk.h"
#include "Narzedzia.h"
#include "Typy.h"

#define ZMNIEJSZENIE 0.8

typedef std::shared_ptr< std::string > String_Ptr;

class Siatka
{
private:
	Ustawienia_Ptr ustawienia;
	void narysujSiatke(HDC DC);
	void narysujKrzyzyk(HDC DC, HBRUSH Brush, HBRUSH MBrush ,int a, int b);
	void narysujKolko(HDC DC, HBRUSH Brush, HBRUSH MBrush, int a, int b);
	Pozycja_Ptr pozycja(int index);
	void log(Pozycja_Ptr poz);

public:
	Siatka();
	Siatka(Ustawienia_Ptr ustawienia);
	virtual ~Siatka();
	void ustawParametry(Ustawienia_Ptr ustawienia);
	void narysuj(HWND *Window, KolkoKrzyzyk_Ptr ptrKik);
	Pozycja_Ptr wyliczKratke(LPARAM LParam);
};

typedef std::shared_ptr<Siatka> Siatka_Ptr;

