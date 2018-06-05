#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>


enum EKIK
{
	GraczWygrywa = 1,		//1 
	KomputerWygrywa,		//2
	RuchGracza,				//3
	RuchKomputera,			//4
	Remis,					//5
	Gramy					//6
};

enum EKratka
{
	Pusta = 100,
	XZnak,
	OZnak
};

#define NIEPOPRAWNA_KRATKA		-1

struct Pozycja
{
	int y, x;
};

typedef std::shared_ptr< std::string > String_Ptr;

typedef std::shared_ptr< Pozycja > Pozycja_Ptr;

typedef std::vector<Pozycja> ListaPozycji;

typedef std::shared_ptr< std::vector<Pozycja> > ListaPozycji_Ptr;

typedef std::vector<std::vector<EKratka>> Tablica;

typedef std::shared_ptr< std::vector<std::vector<EKratka> > > Tablica_Ptr;

typedef std::shared_ptr< std::vector<int> > VectorInts_Ptr;

typedef std::shared_ptr< std::map<int, int> > MapIntInt_ptr;
