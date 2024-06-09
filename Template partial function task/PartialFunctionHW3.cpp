#pragma once
#include <iostream>
#include "Factory.h"

static void intervalMode(const PartialFunction* function)
{
	int a, b;
	std::cout << "Please, enter interval [a; b] boundaries: " << std::endl;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;

	if (a > b)
	{
		std::swap(a,b);
	}

	std::cout << "Results in the current interval: " << std::endl;
	for (int i = a; i <= b; i++)
	{
		if (function->isDefined(i))
		{
			std::cout << function->evaluate(i) << " ";
		}
	}
}

static void userInputMode(const PartialFunction* function)
{
	int point = INT_MIN;
	char answer;

	while (true)
	{
		std::cout << "Generate result? (Press 'y' for 'Yes' and n for 'No')" << std::endl;		
		std::cin >> answer;

		if (function->isDefined(point))
		{
			std::cout << function->evaluate(point) << " ";
		}

		point++;
	}
}

static void execute(const char*fileName)
{
	Factory f;
	PartialFunction* function = f.functionsFactory(fileName);

	std::cout << "Please, enter a valid program's mode (1 or 2). 1 stands for specific interval results' generation. 2 stand for generation of results according to user's input:" << std::endl;
   
	unsigned programMode;
	std::cin >> programMode;

	switch (programMode)
	{
	case 1: intervalMode(function); break;
	case 2: userInputMode(function); break;
	default: throw std::exception("Error! Invalid program mode!"); break;
	}
}

//Just samples
//void createFuncDat(const char* fileName)
//{
//	std::ofstream ofs(fileName, std::ios::binary);
//	uint16_t T = 3;
//	uint16_t N = 3;
//	char files[3][15] = { "first.dat", "second.dat", "third.dat" };
//
//	ofs.write((char*)&T, sizeof(uint16_t));
//	ofs.write((char*)&N, sizeof(uint16_t));
//	ofs.write(files[0], sizeof(files[0]));
//	ofs.write(files[1], sizeof(files[1]));
//	ofs.write(files[2], sizeof(files[2]));	
//}
//void specificContextCreationTest(const char* fileName) 
//{
//	std::ofstream ofs(fileName, std::ios::binary);
//	uint16_t T = 0;
//	uint16_t N = 7;
//	ofs.write((char*)&T, sizeof(uint16_t));
//	ofs.write((char*)&N, sizeof(uint16_t));
//
//    int args[] = { 0, 1, 2, 3, 5, 6, 7 };
//	int results[] = { 0, 3, 3, 3, 4, 4, 0 };
//
//	ofs.write((char*)args, N * sizeof(int));
//	ofs.write((char*)results, N * sizeof(int));
//}
//
//void notDefinedContextCreationTest(const char* fileName) 
//{
//	std::ofstream ofs(fileName, std::ios::binary);
//	uint16_t T = 1;
//	uint16_t N = 2;
//	ofs.write((char*)&T, sizeof(uint16_t));
//	ofs.write((char*)&N, sizeof(uint16_t));
//
//	int arr[] = { 3, 5 };
//	ofs.write((char*)arr, N * sizeof(int));
//}
//
//void allDefinedContextCreationTest(const char* fileName) 
//{
//	std::ofstream out(fileName, std::ios::binary);
//	uint16_t T = 2;
//	uint16_t N = 4;
//	out.write((char*)&T, sizeof(uint16_t));
//	out.write((char*)&N, sizeof(uint16_t));
//
//	int arr[] = {0,5,6,7};
//	out.write((char*)arr, N * sizeof(int));
//}

int main()
{
	//Just samples
	/*specificContextCreationTest("first.dat");
	notDefinedContextCreationTest("second.dat");
	allDefinedContextCreationTest("third.dat");
	
	createFuncDat("func.dat");
    execute("func.dat");*/
}

