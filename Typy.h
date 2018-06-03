#pragma once

#include <string>
#include <memory>
#include <vector>

typedef std::shared_ptr< std::string > String_Ptr;
//std::make_shared<string>("hello world");

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

struct Move
{
	int row, col;
};

typedef std::vector<std::vector<EKratka>> Matrix;

typedef std::shared_ptr<Matrix> Matrix_Ptr;