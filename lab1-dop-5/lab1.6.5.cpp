#include <string>
#include <algorithm>
#include <locale>
#include <iostream>
#include <fstream>

using namespace std;

enum operation
{
	PLUS = 0,
	MINUS,
	MULT
};

enum type
{
	operation,
	number
};

string process(string& str);

class TreeNode
{
public:
	TreeNode(type type = number, int value = 0, TreeNode* left = 0, TreeNode* right = 0);
	TreeNode(const TreeNode& node);
	virtual ~TreeNode(void);
	// Возвращает указатель на левую ветвь
	TreeNode* const Left(void) const;
	// Возвращает указатель на правую ветвь
	TreeNode* const Right(void) const;
	type Type(void) const;
	int Value(void) const;
	bool Brackets(void) const;
	// Оператор присваивания
	TreeNode& operator=(const TreeNode& node);
protected:
	// Ветвь дерева
	TreeNode* _left;
	// Ветвь дерева
	TreeNode* _right;
	// Значение
	int _value;
	// Тип(операция/число)
	type _type;
	bool _brackets;
	friend TreeNode* term(string& str);
	friend bool nextOp(TreeNode& tree);
};

int main()
{	
	ifstream inputFile("input.txt");

	if (inputFile)
	{
		ofstream out;
		out.open("output.txt");

		if (out)
		{
			while (!inputFile.eof())
			{
				string str;
				getline(inputFile, str);
				string res = process(str);
				cout << res << endl;
				out << res << endl;
			}
			out.close();
		}
		else cout << "Can't open file " << "output.txt";
		inputFile.close();
	}
	else cout << "Can't open file " << "input.txt";
	system("PAUSE");
	return 0;
}

// Удаляет лишние whitespaces
void trim(string &str)
{
	while (str.length() && iswspace(str[0]))str.erase(0, 1);
	while (str.length() && iswspace(str[str.length() - 1]))str.resize(str.length() - 1);
	for (int i = 0; i<static_cast<int>(str.length()) - 1;)
	{
		if (iswspace(str[i]) && iswspace(str[i + 1]))
		{
			str[i] = ' ';
			str.erase(i + 1, 1);
		}
		else i++;
	}
}

// Извлекает подстроку в скобках
string extract(string& str)
{
	int numL = 0;
	string::iterator it = str.begin();
	while (it != str.end())
	{
		switch (*it)
		{
			case '(':
				numL++;
				break;
			case ')':
				numL--;
				if (!numL)
				{
					string res = str.substr(1, it - str.begin() - 1);
					str.erase(str.begin(), it + 1);
					return res;
				}
		}
		it++;
	}
	return "";
}

TreeNode* parsestr(string& str);

// Возвращает следующий элемент дерева
TreeNode* term(string& str)
{
	trim(str);
	if (str[0] == '(')
	{
		string
			tmp = extract(str);
		if (tmp.length())
		{
			TreeNode* tree = parsestr(tmp);
			if (tree)tree->_brackets = true;
			return tree;
		}
		else return 0;
	}
	if (str.length() && iswdigit(str[0]))
	{
		int value = 0;
		while (str.length() && iswdigit(str[0]))
		{
			string digit = str.substr(0, 1);
			value = value * 10 + atoi(digit.c_str());
			str.erase(0, 1);
		}
		return new TreeNode(number, value);
	}
	else return 0;
}

// Преобразует строку в бинарное дерево
TreeNode* parsestr(string& str)
{
	if (TreeNode* l = term(str))
	{
		while (str.length())
		{
			if (str[0] == ' ')
			{
				str.erase(0, 1);
				if (TreeNode* r = term(str))
				{
					l = new TreeNode(operation, 0, l, r);
				}
				else
				{
					delete l;
					return 0;
				}
			}
			else return 0;
		}
		return l;
	}
	else return 0;
}

// Вычисляет значение выражения сохраненного в дереве

int calc(const TreeNode& tree)
{
	switch (tree.Type())
	{
	case number:
		return tree.Value();
	case operation:
		switch (tree.Value())
		{
			case PLUS:
				return calc(*tree.Left()) + calc(*tree.Right());
			case MINUS:
				return calc(*tree.Left()) - calc(*tree.Right());
			case MULT:
				return calc(*tree.Left())*calc(*tree.Right());
		}
	}
	return 0;
}

// Изменить порядок операций
bool nextOp(TreeNode& tree)
{
	if (tree.Type() == operation)
	{
		++tree._value %= 3;
		if (!tree._value)
		{
			return nextOp(*tree._left) || nextOp(*tree._right);
		}
		else return true;
	}
	else return false;
}

// Обратное преобразование дерева в строку
string format(const TreeNode& tree)
{
	char num[10];
	string res;
	switch (tree.Type())
	{
		case number:
			_itoa(tree.Value(), num, 10);
			res = num;
			break;
		case operation:
			switch (tree.Value())
			{
				case PLUS:
						res = format(*tree.Left()) + '+' + format(*tree.Right());
						break;
				case MINUS:
					res = format(*tree.Left()) + '-' + format(*tree.Right());
					break;
				case MULT:
					res = format(*tree.Left()) + '*' + format(*tree.Right());
					break;
			}
	}
	if (tree.Brackets())res = '(' + res + ')';
	return res;
}

// Основные вычисления
string process(string& str)
{
	trim(str);
	string::iterator it = find(str.begin(), str.end(), '=');
	if (it != str.end())
	{
		string resultStr = str.substr(0, it - str.begin());
		trim(resultStr);
		int result = atoi(resultStr.c_str());
		str.erase(str.begin(), it + 1);
		TreeNode *tree = parsestr(str);
		if (tree)
		{
			do
			{
				if (calc(*tree) == result)
				{
					string res = resultStr + '=' + format(*tree);
					delete tree;
					return res;
				}
			} while (nextOp(*tree));
			delete
				tree;
			return "Does not exist";
		}
		else return "Invalid expression";
	}
	else return "Invalid input format";
}

TreeNode::TreeNode(type type, int value, TreeNode* left, TreeNode* right)
	: _left(left)
	, _right(right)
	, _value(value)
	, _type(type)
	, _brackets(false)
{
}

TreeNode::~TreeNode(void)
{
	if (_left)
	{
		delete _left;
		_left = 0;
	}
	if (_right)
	{
		delete _right;
		_right = 0;
	}
}

TreeNode::TreeNode(const TreeNode& node)
	: _left(0)
	, _right(0)
	, _value(node._value)
	, _type(node._type)
	, _brackets(node._brackets)
{
	if (node._left)_left = new TreeNode(*node._left);
	if (node._right)_right = new TreeNode(*node._right);
}

// Оператор присваивания
TreeNode& TreeNode::operator=(const TreeNode& node)
{
	if (&node != this)
	{
		if (_left)delete _left;
		if (_right)delete _right;
		if (node._left)_left = new TreeNode(*node._left);
		else
			_left = 0;
		if (node._right)_right = new TreeNode(*node._right);
		else _right = 0;
		_value = node._value;
		_type = node._type;
		_brackets = node._brackets;
	}
	return *this;
}

// Возвращает указатель на левую ветвь
TreeNode* const TreeNode::Left(void) const
{
	return _left;
}

// Возвращает указатель на правую ветвь
TreeNode* const TreeNode::Right(void) const
{
	return _right;
}

type TreeNode::Type(void) const
{
	return _type;
}

int TreeNode::Value(void) const
{
	return _value;
}

bool TreeNode::Brackets(void) const
{
	return _brackets;
}