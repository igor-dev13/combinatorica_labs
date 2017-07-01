#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

std::vector<std::vector<int>> m_grapgh;
std::vector<std::vector<int>> m_transposedGraph;
std::vector<char> m_used;
std::vector<int> m_order;
std::vector<int> m_component;

bool initMatrix(vector<vector<int>>& matrix);
void InitTransposedGraph();
void FirstDfs(int vertex);
void SecondDfs(int vertex);
bool CheckStrongConnection();

int main(int argc, char** argv[])
{
	vector<vector<int>> matrix;
	if (!initMatrix(matrix))
	{
		return 1;
	}

	m_grapgh.swap(matrix);
	InitTransposedGraph();

	if (CheckStrongConnection())
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	getchar();
	return 0;
}

bool initMatrix(vector<vector<int>>& matrix)
{
	ifstream inputFS;
	inputFS.open("input.txt");

	if (!inputFS.is_open())
	{
		cerr << "Error open file" << endl;
		return false;
	}

	string line;
	getline(inputFS, line);
	stringstream sStream(line);

	int vertexCount;
	sStream >> vertexCount;

	if (vertexCount < 1 || vertexCount > 400)
	{
		cerr << "Vertex count must be less then 400 and more then 1" << endl;
		return false;
	}

	matrix.resize(vertexCount);

	if (!inputFS.good())
	{
		cerr << "error while read second row" << endl;
		return false;
	}
	for (int i = 0; i < vertexCount; i++)
	{
		matrix[i].resize(vertexCount);
		string tempString;
		getline(inputFS, tempString);
		sStream.clear();
		sStream.str(tempString);
		for (int j = 0; j < vertexCount; j++)
		{
			if (!sStream.good())
			{
				cerr << "Bad row" << i + 2 << endl;
				return false;
			}

			sStream >> matrix[i][j];
		}
	}

	return true;
}

void InitTransposedGraph()
{
	m_transposedGraph = vector<vector<int>>(m_grapgh.size(), vector<int>(m_grapgh.size()));
	for (size_t i = 0; i < m_grapgh.size(); ++i)
	{
		for (size_t j = 0; j < m_grapgh[i].size(); ++j)
		{
			m_transposedGraph[j][i] = m_grapgh[i][j];
		}
	}
}

void FirstDfs(int vertex)
{
	m_used[vertex] = true;
	for (size_t i = 0; i < m_grapgh[vertex].size(); ++i)
	{
		if (!m_used[i] && m_grapgh[vertex][i] != 0)
		{
			FirstDfs(i);
		}
	}
	m_order.push_back(vertex);
}

void SecondDfs(int vertex)
{
	m_used[vertex] = true;
	m_component.push_back(vertex);

	for (size_t i = 0; i < m_transposedGraph[vertex].size(); ++i)
	{
		if (!m_used[i] && m_transposedGraph[vertex][i] != 0)
		{
			SecondDfs(i);
		}
	}
}

bool CheckStrongConnection()
{
	m_used.assign(m_grapgh.size(), false);
	for (size_t i = 0; i < m_grapgh.size(); ++i)
	{
		if (!m_used[i])
		{
			FirstDfs(i);
		}
	}

	m_used.assign(m_grapgh.size(), false);
	SecondDfs(m_order[m_grapgh.size() - 1]);

	return m_component.size() == m_grapgh.size();
}