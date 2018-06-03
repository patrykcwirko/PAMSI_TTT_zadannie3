#pragma once

#include <string>
#include <memory>
#include <vector>

typedef std::shared_ptr< std::string > String_Ptr;
//std::make_shared<string>("hello world");

enum EKIK
{
	G1Wygrywa = 1, //1 
	G2Wygrywa,     //2
	G1Ruch,        //3
	G2Ruch,		   //4
	Remis,	       //5
	Gramy		   //6
};

enum EKratka
{
	Pusta,
	XZnak,
	OZnak
};

struct Move
{
	int row, col;
};

typedef std::vector<std::vector<EKratka>> Matrix;

typedef std::shared_ptr<Matrix> Matrix_Ptr;