#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX = 8;

void initGraph();
void calculateKirchhoffMatrix();
int gaussDeterm(int a[MAX][MAX], int n);

int v = 0;				// ���������� ������
int graph[MAX][MAX];		// ����������������� ����
int martix[MAX][MAX];	// ������� ��������

int main()
{
	initGraph();
	calculateKirchhoffMatrix();

	// ������� ������������� ������� ��� ������� ��������
	int dm[MAX][MAX];
	for (int row = 1; row<v; row++) {
		for (int col = 1; col<v; col++) {
			dm[row - 1][col - 1] = martix[row][col];
		}
	}
	int determinant = gaussDeterm(dm, v - 1);

	cout << "Number of spanning trees - " << determinant;
	return 0;
}

// ��������� ������� ��������
void calculateKirchhoffMatrix() {
	for (int i = 0; i < v; i++)
	{
		int count = 0;
		for (int j = 0; j < v; j++)
		{
			if (graph[i][j] == 1) {
				count++;
				martix[i][j] = -1;
			}
		}
		martix[i][i] = count;
	}
}

// �������� �������� ������
void initGraph() {
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> v;

	for (int i = 0; i < v; i++)
	{
		getline(inputFile, line);
		istringstream ss(line);
		for (size_t j = 0; j < v; j++)
		{
			ss >> graph[i][j];
			if (graph[i][j] > 0) graph[i][j] = 1;
		}
	}
}

// ����� ������������ ������� ������� �����
int gaussDeterm(int a[MAX][MAX], int n) {

	for (int col = 0; col < n; ++col) {
		bool found = false;
		for (int row = col; row < n; ++row) {
			if (a[row][col]) {
				if (row != col)
				{
					swap(a[row], a[col]);
				}
				found = true;
				break;
			}
		}

		if (!found) {
			return 0;
		}

		for (int row = col + 1; row < n; ++row) {
			while (true) {
				int del = a[row][col] / a[col][col];
				for (int j = col; j < n; ++j) {
					a[row][j] -= del * a[col][j];
				}
				if (a[row][col] == 0)
				{
					break;
				}
				else
				{
					swap(a[row], a[col]);
				}
			}
		}
	}
	long res = 1;
	for (int i = 0; i < n; ++i) {
		res *= a[i][i];
	}
	return abs(res);
}
