#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void GeneratePermutation(int n, int t, int w[], int c[]) 
{
	int i = 0;
	int k = 0;
	int b[255] = {};

	int maxValue = 0;
	int maxWeight = 0;
	int maxItems = 0;
	int maxb[255] = {};

	k = t / *min_element(w, w + n);

	// ��������� ������������������
	for (int i = 0; i < k; i++)
	{
		b[i] = 0;
	}

	// ��������� ���������� � ������������
	while (b[k] != 1)
	{
		i = 0;
		// ���� ������� ������� ����� ������������ �������� 
		// �������� ��� � ���������� 1 � ����������
		while (b[i] == n - 1)
		{
			b[i] = 0;
			i = i + 1;
		}
		b[i] = b[i] + 1;

		// ������� ��� � ��������� ������
		// ���� ��������� ����������� �� ��������� ���������
		int value = 0;
		int weight = 0;
		for (int i = 0; i < k; i++)
		{
			if (weight + w[b[i]] > t) {
				if (maxValue < value) {
					maxWeight = weight;
					maxValue = value;
					maxItems = i;
					for (int j = 0; j < i; j++)
						maxb[j] = b[j];
				}
				break;
			}
			weight += w[b[i]];
			value += c[b[i]];
		}

		if (weight <= t && value > maxValue)
		{
			maxWeight = weight;
			maxValue = value;
			maxItems = k;
			for (int j = 0; j < k; j++)
				maxb[j] = b[j];
		}
	}

	// ��������� ���������� � ����
	ofstream outputFile;
	outputFile.open("output.txt");

	outputFile << "Maximum value: " << maxValue << endl;
	outputFile << "Maximum weight: " << maxWeight << endl;
	outputFile << "Items: ";

	for (int i = 0; i < n; i++)
	{
		int itemsCount = 0;
		for (int j = 0; j < maxItems; j++)
		{
			if (maxb[j] == i) itemsCount++;
		}
		outputFile << itemsCount << " ";
	}
	outputFile << endl;
	outputFile.close();
}

int main()
{
	// ���������� ����� ���������
	int n = 0;
	// ������������ ��� �������
	int t = 0;

	// ��� ���������
	int w[255] = {};
	// ��������� ���������
	int p[255] = {};

	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> n >> t;

	for (size_t i = 0; i < n; i++)
	{
		getline(inputFile, line);
		istringstream ss(line);
		ss >> w[i] >> p[i];
	}

	GeneratePermutation(n, t, w, p);
	return 0;
}