#pragma once

#include <memory>

enum EKIK 
{
	G1Wygrywa = 1, //1 
	G2Wygrywa,     //2
	G1Ruch,        //3
	G2Ruch,		   //4
	Remis	       //5
};

enum EKratka 
{
	Pusta,
	XZnak,
	OZnak
};

class KolkoKrzyzyk
{
public:
	KolkoKrzyzyk();
	virtual ~KolkoKrzyzyk();
	bool ustaw(int kratka);
	EKratka pobierz(int kratka);
	void reset();
};

typedef std::shared_ptr< KolkoKrzyzyk > KolkoKrzyzyk_Ptr;

