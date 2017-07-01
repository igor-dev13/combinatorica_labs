#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <string>
#include <array>

unsigned long getDecodeNumber(const std::string &str);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Need text data file to input" << std::endl;
		return 1;
	}
	std::ifstream fIn(argv[1]);
	if (!fIn.is_open()) 
	{
		std::cerr << "Can't open input file" << std::endl;
		return 1;
	}
	std::string inputLine;
	if (!std::getline(fIn, inputLine)) 
	{
		std::cerr << "Can't read from file" << std::endl;
		return 1;
	}
	if (inputLine.length() > 100) 
	{
		std::cerr << "To long string" << std::endl;
		return 1;
	}
	fIn.close();
	std::cout << "Total variants of decoding = " << getDecodeNumber(inputLine) << std::endl;
	return 0;
}

unsigned long getDecodeNumber(const std::string &str)
{
	std::array<unsigned long, 101> decodeNumber;
	decodeNumber.fill(0);
	decodeNumber[str.length()] = 1;
	decodeNumber[str.length() - 1] = str[str.length() - 1] != '0';
	for (size_t i = str.length() - 2; i < 101; --i)
	{
		printf("%d\n", i);
		//printf("%d\n", decodeNumber[i + 1]);
		//printf("%d\n", decodeNumber[i + 2]);
		if (str[i] == '0')
		{
			decodeNumber[i] = 0;
		}
		else if (str[i] == '1' || (str[i] == '2' && str[i + 1] <= '6'))
		{
			decodeNumber[i] = decodeNumber[i + 1] + decodeNumber[i + 2];
		}
		else
		{
			decodeNumber[i] = decodeNumber[i + 1];
		}
	}
	return decodeNumber[0];
}