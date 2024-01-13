#include <iostream>
#include <string>
using namespace std;

class Node
{
	int key;
	string value;
	Node* pNode = nullptr;

public:
	Node(string value)
	{
		this->key = rand() % 1000;
		this->value = value;
		pNode = nullptr;
	}

	Node(int key, string value)
	{
		this->key = key;
		this->value = value;
		pNode = nullptr;
	}

	Node(int key)
	{
		this->key = key;
		this->value = "";
		pNode = nullptr;
	}

	Node& operator =(Node& object)						//возвращает ссылку на текущий объект (смотрит только значения из объекта)
	{
		if (this == &object)							//Проверка является ли объект тем же самым объектом (чтобы не присвоить a - а (если это сделаем выдаст ошибку т.к. длина строки будет 0))
			return *this;

		key = object.key;
		value = object.value;
		pNode = object.pNode;

		return *this;
	}

	Node(const Node& object)
	{
		key = object.key;
		value = object.value;
		pNode = object.pNode;
	}

	int getKey()
	{
		return key;
	}

	friend ostream& operator << (ostream& out, const Node& p)
	{
		out << p.key << "-" << p.value << endl;
		return out;
	}

	friend class hashTable;
};

class hashTable
{
	int size;
	Node** table;

public:
	hashTable()
	{
		this->size = 10;

		table = new Node * [size];
		for (int i = 0; i < size; i++)
			table[i] = nullptr;
	}

	~hashTable()
	{
		for (int i = 0; i < size; i++)
			delete table[i];

		delete[] table;
	}

	void append(const Node& object)
	{
		int index = getHash(object.key);

		if (table[index] == nullptr)
		{
			table[index] = new Node(object);

			return;
		}
		else
		{
			if (checkEl(object) == 0)
			{
				Node* sup = table[index];
				while (sup->pNode != nullptr)
					sup = sup->pNode;

				sup->pNode = new Node(object);

				return;
			}
		}

		cout << "Error:  НЕУДАЛОСЬ ДОБАВИТЬ ЭЛЕМЕНТ: " << object << "\tЭЛЕМЕНТ С ТАКИМ КЛЮЧОМ ИЛИ ЗНАЧЕНИЕМ УЖЕ СУЩЕСТВУЕТ\n";
	}

	bool search(const Node& object)
	{
		int index = getHash(object.key);

		if (table[index] == nullptr)
			return false;

		if (table[index]->key == object.key)
			return true;

		Node* sup = table[index];
		while (sup != nullptr)
		{
			if (sup->key == object.key)
				return true;
			else
				sup = sup->pNode;
		}

		return false;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "Хэш " << i << ": ";

			if (table[i] == nullptr)
			{
				cout << endl;
			}
			else
			{
				Node* sup = table[i];
				while (sup != nullptr)
				{
					cout << sup->key << "-" << sup->value << "| ";
					sup = sup->pNode;
				}

				cout << endl;
			}
		}
		cout << endl;
	}

	bool del_str(int key)
	{
		int index = getHash(key);

		if (table[index] == nullptr)
			return false;

		Node* del = table[index];
		//		Node* temp = table[index];
		Node* prev_sup = table[index];

		if (table[index]->pNode == nullptr && table[index]->key == key)
		{
			table[index] = nullptr;
			return true;
		}

		while (del != nullptr)
		{
			if (del->key == key && del->pNode == nullptr)
			{
				prev_sup->pNode = nullptr;
				delete del;
				return true;
			}
			else if (del->key == key && del->pNode != nullptr)
			{
				prev_sup = del->pNode;
				del->key = prev_sup->key;
				del->value = prev_sup->value;
				del->pNode = prev_sup->pNode;

				delete prev_sup;
				return true;
			}
			else
			{
				prev_sup = del;
				del = del->pNode;
			}
		}

		return false;
	}

	hashTable(const hashTable& object)
	{
		size = object.size;

		table = new Node * [size];
		for (int i = 0; i < size; i++)
			table[i] = nullptr;

		for (int i = 0; i < size; i++)
		{
			if (object.table[i] == nullptr)
			{
				continue;
			}
			else if (object.table[i] != nullptr && object.table[i]->pNode == nullptr)
			{
				table[i] = new Node(object.table[i]->key, object.table[i]->value);
			}
			else if (object.table[i] != nullptr && object.table[i]->pNode != nullptr)
			{
				Node* sup = object.table[i];
				table[i] = new Node(sup->key, sup->value);
				Node* sup_2 = table[i];
				while (sup != nullptr)
				{
					sup = sup->pNode;
					sup_2->pNode = (sup);
					sup_2 = sup_2->pNode;
				}
			}
		}
	}

	hashTable& operator =(hashTable& object)						//возвращает ссылку на текущий объект (смотрит только значения из объекта)
	{
		if (this == &object)										//Проверка является ли объект тем же самым объектом (чтобы не присвоить a - а (если это сделаем выдаст ошибку т.к. длина строки будет 0))
			return *this;

		for (int i = 0; i < size; i++)
			delete table[i];
		delete[] table;

		size = object.size;

		table = new Node * [size];
		for (int i = 0; i < size; i++)
			table[i] = nullptr;

		for (int i = 0; i < size; i++)
		{
			if (object.table[i] == nullptr)
			{
				continue;
			}
			else if (object.table[i] != nullptr && object.table[i]->pNode == nullptr)
			{
				table[i] = new Node(object.table[i]->key, object.table[i]->value);
			}
			else if (object.table[i] != nullptr && object.table[i]->pNode != nullptr)
			{
				Node* sup = object.table[i];
				table[i] = new Node(sup->key, sup->value);
				Node* sup_2 = table[i];
				while (sup != nullptr)
				{
					sup = sup->pNode;
					sup_2->pNode = (sup);
					sup_2 = sup_2->pNode;
				}
			}
		}

		return *this;
	}

	string& operator[](int key)
	{
		if (key >= 0)
		{
			int index = getHash(key);

			if (table[index] != nullptr && table[index]->key == key)
				return table[index]->value;
			else if (table[index] != nullptr && table[index]->pNode != nullptr)
			{
				Node* sup = table[index];
				while (sup != nullptr)
				{
					if (sup->key == key)
						return sup->value;
					else
						sup = sup->pNode;
				}
			}
		}
	}

private:
	int getHash(const int key)
	{
		return  key % size;
	}

	//	Вспомогательная функция, чтобы исключить элементы-дубликаты по ключу или по значению
	//	Для корректного удаления элементов таблицы
	int checkEl(const Node& object)
	{
		int index = getHash(object.key);

		if (table[index] == nullptr)
			return 0;

		if (table[index]->key == object.key)
			return 1;
		if (table[index]->value == object.value)
			return 2;

		Node* sup = table[index];
		while (sup != nullptr)
		{
			if (sup->key == object.key)
				return 1;
			else if (sup->value == object.value)
				return 2;
			else
				sup = sup->pNode;
		}

		return 0;
	}

};