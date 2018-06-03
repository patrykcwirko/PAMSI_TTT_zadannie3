#pragma once

#include "Typy.h"

class MinMax
{
public:
	MinMax();
	virtual ~MinMax();
	int nalepszyRuch(Matrix_Ptr matrix);
};

typedef std::shared_ptr< MinMax > MinMax_Ptr;

