#pragma once

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <string>

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

class Narzedzia
{
public:
	Narzedzia();
	virtual ~Narzedzia();
	static void RedirectIOToConsole();
	static void printLog(std::string info);
};

