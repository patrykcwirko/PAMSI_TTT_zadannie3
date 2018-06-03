#include "stdafx.h"
#include "MinMax.h"


MinMax::MinMax()
{
}

MinMax::~MinMax()
{
}

int MinMax::nalepszyRuch(Matrix_Ptr matrix, int iloscWRzedzie)
{
	return testing(matrix, iloscWRzedzie);
}

int MinMax::testing(Matrix_Ptr matrix, int iloscWRzedzie)
{
	int limit = 1000;
	while (true) {
		if (--limit == 0) {
			return NIEPOPRAWNA_KRATKA;
		}
		int kratka = (rand() * (int)(iloscWRzedzie * iloscWRzedzie) / RAND_MAX);
		int y = kratka / iloscWRzedzie;
		int x = kratka - (y * iloscWRzedzie);
		if (matrix->at(y).at(x) == Pusta)
		{
			return kratka;
		}

	}
}