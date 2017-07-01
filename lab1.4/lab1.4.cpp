#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

void FillRandomPermutation(int p[], int n);

int main(int argc, char* argv[])
{
	// ƒлина последовательности
	int n = 0;
	if (argc > 1)
	{
		n = atoi(argv[1]);
	}
	else
	{
		cout << "No argument N" << endl;
		return 0;
	}
	if (n <= 0) {
		cout << "N must be > 0" << endl;
		return 0;
	}

	// —лучайна€ последовательность
	int p[100] = {};

	// √енерируем случайную последовательность
	FillRandomPermutation(p, n);

	cout << "Random permutation: ";
	for (int i = 0; i < n; i++)
		cout << p[i] << " ";
	cout << endl;

	cin.get();
	return 0;
}

void FillRandomPermutation(int p[], int n) 
{
	// »нициализируем начальные значени€
	for (int i = 0; i < n; i++) {
		p[i] = -1;
	}

	// «аполн€ем случайную последовательность
	srand((int)time(0));
	for (int i = 0; i < n; i++)
	{
		int rnd;
		do {
			rnd = rand() % n;
		} while (p[rnd] != -1);
		p[rnd] = i;
	}
}