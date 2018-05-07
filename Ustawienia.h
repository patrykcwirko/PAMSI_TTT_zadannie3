#pragma once

#define DFLT_ILOSC_W_RZEDZIE 3

class Ustawienia 
{
private:
	int iloscWRzedzie;
	
public:

	Ustawienia() : iloscWRzedzie(DFLT_ILOSC_W_RZEDZIE) {}

	Ustawienia(int ilosc) : iloscWRzedzie(ilosc) {}

	~Ustawienia() {}

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

typedef std::shared_ptr<Ustawienia> Ustawienia_Ptr;
//std::shared_ptr<Ustawienia> p = std::make_shared<Ustawienia>();