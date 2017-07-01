#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

std::vector<std::pair<int, int>> bridges;
std::vector<int> junctionPoints;
std::vector<std::vector<int>> m_graph;
std::vector<bool> used;
std::vector<int> timerIn;
std::vector<int> timerUp;
int timer;

int InitGraph(vector<vector<int>>& adjacencyMatrix);
void SetGraph(std::vector<std::vector<int>> graph);
void FindPoints(int vertex, int parent);
void FindBridges(int vertex, int parent);

int main(int argc, char** argv[])
{
	vector<vector<int>> graph;
	InitGraph(graph);

	SetGraph(graph);
	FindPoints(0, -1);
	
	SetGraph(graph);
	for (size_t i = 0; i < m_graph.size(); ++i)
	{
		if (!used[i])
		{
			FindBridges(i, -1);
		}
	}

	cout << "Junction points:" << endl;
	for (size_t i = 0; i < junctionPoints.size(); ++i)
	{
		cout << junctionPoints[i] << " ";
	}
	cout << endl;

	cout << "Bridges:" << endl;
	for (size_t i = 0; i < bridges.size(); ++i)
	{
		cout << bridges[i].first << "-" << bridges[i].second << " ";
	}
	cout << endl;

	getchar();
}

int InitGraph(vector<vector<int>>& adjacencyMatrix)
{
	ifstream inputFS;
	inputFS.open("input.txt");

	if (!inputFS.is_open())
	{
		cerr << "Error open file" << endl;
		return 1;
	}

	string line;
	getline(inputFS, line);

	stringstream sStream(line);

	int vertixCount;
	int edgeCount;
	sStream >> vertixCount;
	if (sStream.good())
	{
		sStream >> edgeCount;
	}
	else
	{
		cerr << "wrong first row second argument" << endl;
		return 1;
	}

	adjacencyMatrix.resize(vertixCount);

	if (!inputFS.good())
	{
		cerr << "error while read second row" << endl;
		return 1;
	}
	for (int i = 0; i < edgeCount; i++)
	{
		int firstVertix;
		int secondVertix;

		string tempString;
		getline(inputFS, tempString);
		sStream.clear();
		sStream.str(tempString);
		sStream >> firstVertix;

		if (firstVertix >= vertixCount)
		{
			cerr << firstVertix << " wrong index of vertix in row" << i + 2 << endl;
			return 1;
		}

		if (sStream.good())
		{
			sStream >> secondVertix;
		}
		else
		{
			cerr << "row structure in " << i + 2 << " is incorrect" << endl;
			return 1;
		}

		if (secondVertix >= vertixCount)
		{
			cerr << firstVertix << " wrong index of vertix in row " << i + 2 << endl;
			return 1;
		}

		adjacencyMatrix[firstVertix].push_back(secondVertix);
		adjacencyMatrix[secondVertix].push_back(firstVertix);
	}

	return 0;
}

void SetGraph(std::vector<std::vector<int>> graph)
{
	m_graph.swap(graph);
	size_t matrixSize = m_graph.size();
	used = vector<bool>(matrixSize, false);
	timerIn.resize(matrixSize);
	timerUp.resize(matrixSize);
}

void FindPoints(int vertex, int parent)
{
	used[vertex] = true;
	timerIn[vertex] = timerUp[vertex] = timer++;
	int children = 0;
	for (size_t i = 0; i < m_graph[vertex].size(); ++i)
	{
		int to = m_graph[vertex][i];
		if (to == parent)
		{
			continue;
		}
		if (used[to])
		{
			timerUp[vertex] = min(timerUp[vertex], timerIn[to]);
		}
		else
		{
			FindPoints(to, vertex);
			timerUp[vertex] = min(timerUp[vertex], timerUp[to]);
			if (timerUp[to] >= timerIn[vertex] && parent != -1)
			{
				junctionPoints.push_back(vertex);
			}
			++children;
		}
	}
	if (parent == -1 && children > 1)
	{
		junctionPoints.push_back(vertex);
	}
}

void FindBridges(int vertex, int parent)
{
	used[vertex] = true;
	timerIn[vertex] = timerUp[vertex] = timer++;
	for (size_t i = 0; i < m_graph[vertex].size(); ++i)
	{
		int to = m_graph[vertex][i];
		if (to == parent)
		{
			continue;
		}
		if (used[to])
		{
			timerUp[vertex] = min(timerUp[vertex], timerIn[to]);
		}
		else
		{
			FindBridges(to, vertex);
			timerUp[vertex] = min(timerUp[vertex], timerUp[to]);
			if (timerUp[to] > timerIn[vertex])
			{
				bridges.push_back(pair<int, int>(vertex, to));
			}
		}
	}
}