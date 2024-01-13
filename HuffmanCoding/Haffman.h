#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

class Node
{
	int count;
	char letter;
	Node* left_kid;
	Node* right_kid;

public:
	Node(char letter, int count)
	{
		this->count = count;
		this->letter = letter;
		this->left_kid = nullptr;
		this->right_kid = nullptr;
	}

	Node(int count)
	{
		this->count = count;
		this->left_kid = nullptr;
		this->right_kid = nullptr;
	}

	Node(Node* obj1, Node* obj2)
	{
		count = obj1->count + obj2->count;
		left_kid = obj1;
		right_kid = obj2;
	}

	Node(const Node& object)
	{
		count = object.count;
		left_kid = object.left_kid;
		right_kid = object.right_kid;
	}

	bool operator > (Node& object)
	{
		if (count > object.count)
			return true;

		return false;
	}

	Node& operator =(Node& object)
	{
		if (this == &object)
			return *this;

		count = object.count;
		letter = object.letter;
		left_kid = object.left_kid;
		right_kid = object.right_kid;

		return *this;
	}

	friend class Haffman;
};

class Haffman
{
	Node* head = nullptr;								// вершина дерева
	vector<int> code_let;								// вектор для кодировки букв
	map <char, vector<int>> map_letters_code;			// словарь для записи кодировки букв
	map<char, int> map_letters;							// частота встречи символов
public:
	double encode(const string str, string& code_str)
	{
		int beg_coef = str.length() * 8;					// 1 символ = 8 бит

		if (!build(str))
			return -1;

		map_letters_code.clear(); code_let.clear();		// очищение кодировки букв, очищение вектора
		build_code(head);

		vector<int> sup;
		for (int i = 0; i < str.length(); i++)
		{
			sup = map_letters_code[str[i]];
			for (int i = 0; i < sup.size(); i++)
				code_str += to_string(sup[i]);
		}

		for (int i = 0; i < code_str.length(); i++)
			if ((code_str[i] != '0') && (code_str[i] != '1'))
				return -1;


		double end_coef = 0;
		char key; int count_of_meet = 0;

		for (auto it = map_letters.begin(); it != map_letters.end(); it++)
		{
			key = it->first;
			count_of_meet = it->second;

			end_coef += count_of_meet * map_letters_code[key].size();
		}

		map_letters.clear();
		return double(beg_coef / end_coef);
	}

	bool decode(const string& code_str, string& decode_str)
	{
		if (head == nullptr)
		{
			cout << "Error: строка не была закодирована\n\n";
			return false;
		}

		for (int i = 0; i < code_str.length(); i++)
			if ((code_str[i] != '0') && (code_str[i] != '1'))
			{
				cout << "Error: строка закодирована неверно\n\n";
				return false;
			}

		Node* temp = head;
		for (int i = 0; i < code_str.length(); i++)
		{
			if (code_str[i] == '0')
			{
				temp = temp->left_kid;
				if (temp->letter)
				{
					decode_str += temp->letter;
					temp = head;
				}
			}
			else if (code_str[i] == '1')
			{
				temp = temp->right_kid;
				if (temp->letter)
				{
					decode_str += temp->letter;
					temp = head;
				}
			}
		}

		return true;
	}

private:
	bool build(const string& text)
	{
		deleteTree(head);

		for (int i = 0; i < text.length(); i++)
		{
			char ch = text[i];
			map_letters[ch]++;
		}

		list <Node*> list_nodes;

		for (auto it = map_letters.begin(); it != map_letters.end(); it++)
		{
			Node* node = new Node(it->first, it->second);
			list_nodes.push_back(node);
		}

		if (list_nodes.size() > 1)
		{
			while (list_nodes.size() != 1)				// построение дерева
			{
				sort(list_nodes);
				Node* temp_1 = list_nodes.front();
				list_nodes.pop_front();
				Node* temp_2 = list_nodes.front();
				list_nodes.pop_front();

				Node* parent = new Node(temp_1, temp_2);
				list_nodes.push_back(parent);
			}

			head = list_nodes.front();

			return true;
		}
		else if (list_nodes.size() == 1)				// случай, если введена строка с одной и той же буквой
		{
			Node* temp_1 = list_nodes.front();
			list_nodes.pop_front();
			head = new Node(temp_1->count);
			head->left_kid = temp_1;
			return true;
		}

		return false;
	}

	void build_code(Node* parent)						// кодирование символов
	{
		if (parent->left_kid != nullptr)
		{
			code_let.push_back(0);
			build_code(parent->left_kid);
		}

		if (parent->right_kid != nullptr)
		{
			code_let.push_back(1);
			build_code(parent->right_kid);
		}

		if (parent->letter)
			map_letters_code[parent->letter] = code_let;

		if (code_let.size() != 0)
			code_let.pop_back();
	}

	void deleteTree(Node* parent)						// удаление дерева
	{
		if (parent == nullptr)
			return;

		deleteTree(parent->left_kid);
		deleteTree(parent->right_kid);
		delete parent;
	}

	void sort(list<Node*>& list_nodes)					// нужна для сортировки списка при построении дерева
	{
		vector<Node*> vec;
		for (Node* el : list_nodes)
			vec.push_back(el);

		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = 0; j < vec.size() - 1; j++)
			{
				if (vec[j]->count > vec[j + 1]->count)
				{
					Node* temp = vec[j];
					vec[j] = vec[j + 1];
					vec[j + 1] = temp;
				}
			}
		}

		list_nodes.clear();
		for (int i = 0; i < vec.size(); i++)
			list_nodes.push_back(vec[i]);
	}		
};