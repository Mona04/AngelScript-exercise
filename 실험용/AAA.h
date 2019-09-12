#pragma once
#include "pch.h"

class AAA
{
public:
	AAA() = default;
	~AAA() = default;

	void Excute()
	{
		std::cout << "Excute AAA ~" << std::endl;
	}

};