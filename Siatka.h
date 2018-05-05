#pragma once
#include "Ustawienia.h"

class Siatka
{
private:
	Ustawienia_Ptr ustawienia;
	bool** siatka;

public:
	Siatka();

	Siatka(Ustawienia_Ptr ustawienia);

	virtual ~Siatka();
};


Siatka::Siatka() : ustawienia(std::make_shared<Ustawienia>()) 
{
}

Siatka::Siatka(Ustawienia_Ptr ustawienia)
{
	this->ustawinia = ustawienia;
}

Siatka::~Siatka()
{
	if (this->siatka != nullptr)
	{
		delete[] siatka;
	}
}

typedef std::shared_ptr<Siatka> Siatka_Ptr;
//std::shared_ptr<Siatka> p = std::make_shared<Siatka>();