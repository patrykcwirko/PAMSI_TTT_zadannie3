#pragma once

#include <random>
#include "Typy.h"

class MinMax
{
public:
	MinMax();
	virtual ~MinMax();
	int nalepszyRuch(Matrix_Ptr matrix, int iloscWRzedzie);
	int testing(Matrix_Ptr matrix, int iloscWRzedzie);
};

typedef std::shared_ptr< MinMax > MinMax_Ptr;

