#pragma once

#include <memory>

#define DFLT_ILOSC_W_RZEDZIE 5
#define TDLUGOSC 406
#define TWYSOKOSC 445

class Ustawienia
{
private:
	int iloscWRzedzie;
	bool zaczynaCzlowiek;

public:

	Ustawienia() : iloscWRzedzie(DFLT_ILOSC_W_RZEDZIE), zaczynaCzlowiek(true) {}

	Ustawienia(int ilosc) : iloscWRzedzie(ilosc), zaczynaCzlowiek(true) {}

	virtual ~Ustawienia() {}

	int pobierzIloscWRzedzie();

	void ustawIloscWRzedzie(int ilosc);

	bool czyZaczynaCzlowiek();

	void ustawCzyZaczynaCzlowiek(bool ruch);

};


typedef std::shared_ptr< Ustawienia > Ustawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();