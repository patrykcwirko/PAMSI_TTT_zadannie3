#pragma once

#define ILOSCWRZEDZIE 3

class Ustawienia 
{
private:
	int iloscWRzedzie;
	
public:

	Ustawienia() : iloscWRzedzie(ILOSCWRZEDZIE) {}

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