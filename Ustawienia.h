//#pragma once
#ifndef USTAWIENIA_H
#define USTAWIENIA_H

#include <memory>

#define DFLT_ILOSC_W_RZEDZIE 3


class CUstawienia
{
private:
	int iloscWRzedzie;

public:

	CUstawienia() : iloscWRzedzie(DFLT_ILOSC_W_RZEDZIE) {}

	CUstawienia(int ilosc) : iloscWRzedzie(ilosc) {}

	virtual ~CUstawienia() {}

	int ilosc();

	void ilosc(int ilosc);
};

int CUstawienia::ilosc()
{
	return iloscWRzedzie;
}

void CUstawienia::ilosc(int ilosc)
{
	this->iloscWRzedzie = ilosc;
}

typedef std::shared_ptr< CUstawienia > CUstawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();

#endif //USTAWIENIA_H