//#pragma once
#ifndef USTAWIENIA_H
#define USTAWIENIA_H

#include <memory>

#define DFLT_ILOSC_W_RZEDZIE 5


class Ustawienia
{
private:
	int iloscWRzedzie;

public:

	Ustawienia() : iloscWRzedzie(DFLT_ILOSC_W_RZEDZIE) {}

	Ustawienia(int ilosc) : iloscWRzedzie(ilosc) {}

	virtual ~Ustawienia() {}

	int ilosc();

	void ilosc(int ilosc);
};

int Ustawienia::ilosc()
{
	return iloscWRzedzie;
}

void Ustawienia::ilosc(int ilosc)
{
	this->iloscWRzedzie = ilosc;
}

typedef std::shared_ptr< Ustawienia > Ustawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();

#endif //USTAWIENIA_H