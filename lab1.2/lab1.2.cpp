#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	// Количество элементов
	int n = 0;
	if (argc > 1)
	{
		n = atoi(argv[1]);
	}
	else
	{
		cout << "Not arguments" << endl;
		return 0;
	}
	if (n == 0) {
		cout << "N must be > 0" << endl;
		return 0;
	}

	// Массив сочетаний
	int c[10] = {};

	// Длина сочетания
	int k = 5;

	// Количество возможных сочетаний
	int count = 0;

	// Инициализация массива сочетания
	for (int i = 1; i <= k; i++)
	{
		c[i] = i;
	}

	int j = 1;

	clock_t time;
	time = clock();

	while (j != 0)
	{
		// Вывод сочетания в консоль
		/*
		for (int i = 1; i <= k; i++)
			cout << c[i];
		cout << endl;
		*/

		j = k;
		while (c[j] == n - k + j && c[j] > 0)
		{
			j = j - 1;
		}
		c[j] = c[j] + 1;

		for (int i = j + 1; i <= k; i++)
		{
			c[i] = c[i - 1] + 1;
		}

		count++;
	}

	time = clock() - time;
	cout << "Execution time: " << (double)time / CLOCKS_PER_SEC << endl;
	cout << "All combinations: " << count << endl;
	cin.get();
	return 0;
}

/*
К = 5
N = 10
Время: 0
Количество сочетаний: 252

N = 20
Время: 0
Количество сочетаний: 15504

N = 25
Время: 0,001
Количество сочетаний: 53130

N = 50
Время: 0,013
Количество сочетаний: 2118760

N = 100
Время: 0,309
Количество сочетаний: 75287520
*/