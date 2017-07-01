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


	// Массив обратной перестановки
	int p[20] = {};
	// Текущая перестановка
	int s[20] = {};
	// Массив направлений
	int d[20] = {};

	int m = 0;

	// Количество перестановок
	int count = 0;

	// Инициализация начальных значений
	for (int i = 1; i <= n; i++)
	{
		p[i] = s[i] = i;
		d[i] = -1;
	}
	d[1] = 0;
	s[0] = s[n + 1] = m = n + 1;

	clock_t time;
	time = clock();

	// Основной цикл
	while (m != 1)
	{
		// Вывод перестановки в консоль
		/*
		for (int i = 1; i <= n; i++)
			cout << p[i];
		cout << endl;
		*/

		m = n;
		while (s[p[m] + d[m]] > m)
		{
			d[m] = -d[m];
			m = m - 1;
		}
		int buffer = 0;
		buffer = s[p[m]];
		s[p[m]] = s[p[m] + d[m]];
		s[p[m] + d[m]] = buffer;

		buffer = p[s[p[m]]];
		p[s[p[m]]] = p[m];
		p[m] = buffer;

		count++;
	}

	time = clock() - time;
	cout << "Execution time: " << (double)time / CLOCKS_PER_SEC << endl;
	cout << "All combinations: " << count << endl;
	cin.get();
	return 0;
}
/*
N = 10
Время: 0.046 сек
Количество сочетаний: 3628800

N = 11
Время: 0.488 сек
Количество сочетаний: 39916800

N = 12
Время: 5.966 сек
Количество сочетаний: 479001600

N = 13
Время: 68.277 сек
Количество сочетаний: 1932053504

N = 20
Время: 20 лет

*/