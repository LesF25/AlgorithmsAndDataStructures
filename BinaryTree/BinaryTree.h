#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Node
{
	int key;							// значение
	Node* left_kid = nullptr;			// левый ребенок
	Node* right_kid = nullptr;			// правый ребенок
	Node* parent = nullptr;				// родитель

	friend class BinaryTree;
	friend class BinaryTreeSearch;
public:

//		конструктор без параметров (по умолчанию)
	Node()
	{
		this->key = rand() % 1000;
	}

//		конструктор с параметром (значение ключа)
	Node(int key)
	{
		this->key = key;
	}

//		получение значения ключа узла
	int getKey() { return key; }

//		получение кол-ва прямых потомков
	int getChild()
	{
		int count = 0;
		if (left_kid == nullptr)
			count++;
		if (right_kid == nullptr)
			count++;

		return count;
	}

//		перегрузка оператора вызова
	friend ostream& operator << (ostream& out, Node* p)
	{
		out << p->key << endl;
		return out;
	}

//		перегрузка оператора присваивания
	Node& operator =(Node& object)						//возвращает ссылку на текущий объект (смотрит только значения из объекта)
	{
		if (this == &object)							//Проверка является ли объект тем же самым объектом (чтобы не присвоить a - а (если это сделаем выдаст ошибку т.к. длина строки будет 0))
			return *this;

		key = object.key;
		left_kid = object.left_kid;
		right_kid = object.right_kid;
		parent = object.parent;

		return *this;
	}
};

class BinaryTree
{
	Node* head;						// корень дерева

private:
//	создание идеального дерева
	Node* createPerfectTree(int treeSize, Node* parent)
	{
		if (treeSize <= 0)
			return nullptr;

		int leftSubtreeSize = (treeSize - 1) / 2;
		int rightSubtreeSize = treeSize - 1 - leftSubtreeSize;

		Node* node = new Node();

		node->left_kid = createPerfectTree(leftSubtreeSize, node->left_kid);
		node->right_kid = createPerfectTree(rightSubtreeSize, node->right_kid);

		return node;
	}

//	добавление ключа в вектор для ф-ции getVecKeyTree
	void addKeyInVec(Node* root, vector<int>& vecKey)
	{
		if (root != nullptr)
		{
			vector <Node*> sup(1, root);
			while (!sup.empty())
			{
				Node* node = sup.front();
				vecKey.push_back(node->key);
				if (node->left_kid) {
					sup.push_back(node->left_kid);
				}
				if (node->right_kid) {
					sup.push_back(node->right_kid);
				}
				sup.erase(sup.begin());
			}
		}
	}

//	копирование (исп для перегрузки оператора и конструктора копирования)
	void copy(Node* q, Node* p, int choice)
	{
		if (q == nullptr)
			return;

		Node* temp = new Node(q->key);		// создаём новый узел и переписываем в него старый
		temp->parent = p;					//копируем предка

		if (choice == 0)
			p->left_kid = temp;				// если f = 0 - дерево будет левым потомком для p;
		else
			p->right_kid = temp;			// иначе f = 1 - дерево будет правым потомком для p.

		copy(q->left_kid, temp, 0);			//рекурсия для левой ветви
		copy(q->right_kid, temp, 1);		//рекурсия для правой 
	}

//	Получение минимального узла (для получения минимального ключа)
	Node* minNode(Node* root)
	{
		if (root == nullptr)
			return root;

		Node* min = root;

		if (root->left_kid != nullptr)
		{
			Node* sup = minNode(root->left_kid);
			if (sup->key < min->key)
				min = sup;
		}

		if (root->right_kid != nullptr)
		{
			Node* sup = minNode(root->right_kid);
			if (sup->key < min->key)
				min = sup;
		}

		return min;
	}

//	Получение максимального узла (для получения максимального ключа)
	Node* maxNode(Node* root)
	{
		if (root == nullptr)
			return root;

		Node* max = root;
		if (root->left_kid != nullptr)
		{
			Node* sup = minNode(root->left_kid);
			if (sup->key > max->key)
				max = sup;
		}

		if (root->right_kid != nullptr)
		{
			Node* sup = minNode(root->right_kid);
			if (sup->key > max->key)
				max = sup;
		}

		return max;
	}

//	функция, которая присваивает узлам их родителей (исп в конструкторе)
	void giveParent(Node* root)
	{
		if (root == nullptr)
			return;

		giveParent(root->left_kid);
		giveParent(root->right_kid);
		if (root->left_kid != nullptr)
			root->left_kid->parent = root;
		if (root->right_kid != nullptr)
			root->right_kid->parent = root;
	}

//	вспомогательная функция для удаления узла, у которого 2 ребенка
	bool deleteHead(Node* node)
	{
		Node* temp = node;

		if (node->left_kid == nullptr && node->right_kid == nullptr)
		{
			delete node;

			return true;
		}
		else if (node->left_kid != nullptr && node->right_kid != nullptr)
		{
			while (temp->left_kid != nullptr)				// поиск крайнего левого узла
				temp = temp->left_kid;

			if (temp->right_kid == nullptr)
			{
				node->key = temp->key;
				temp->parent->left_kid = nullptr;
			}
			else
			{
				node->key = temp->key;
				temp->right_kid->parent = temp->parent;
				temp->parent->left_kid = nullptr;
			}

			return true;
		}
		else if (node->left_kid != nullptr && node->right_kid == nullptr)
		{
			while (temp->left_kid != nullptr)				// поиск крайнего левого узла
				temp = temp->left_kid;

			if (temp->right_kid == nullptr)
			{
				node->key = temp->key;
				temp->parent->left_kid = nullptr;
			}
			else
			{
				node->key = temp->key;
				temp->right_kid->parent = temp->parent;
				temp->parent->left_kid = nullptr;
			}

			return true;
		}
		else if (node->left_kid == nullptr && node->right_kid != nullptr)
		{
			while (temp->right_kid != nullptr)				// поиск крайнего левого узла
				temp = temp->right_kid;

			if (temp->left_kid == nullptr)
			{
				node->key = temp->key;
				temp->parent->right_kid = nullptr;
			}
			else
			{
				node->key = temp->key;
				temp->left_kid->parent = temp->parent;
				temp->parent->right_kid = nullptr;
			}

			return true;
		}

		return false;
	}

//	очистка дерева (исп в деструкторе), основана на LRK обходе дерева
	void deleteTree(Node* parent)
	{
		if (parent == nullptr)
			return;

		deleteTree(parent->left_kid);
		deleteTree(parent->right_kid);
		delete parent;
	}

public:
//	конструктор
	BinaryTree() { head = nullptr; }

//	конструктор с параметром длина дерева
	BinaryTree(int sizeTree)
	{
		head = createPerfectTree(sizeTree, head);
		giveParent(head);
	}

//	конструктор копирования
	BinaryTree(const BinaryTree& object)
	{
		if (object.head == nullptr)
			head = nullptr;								// если дерево пустое
		else
		{
			head = new Node(object.head->key);			// создаём корень
			copy(object.head->left_kid, head, 0);		// копируем левую ветвь
			copy(object.head->right_kid, head, 1);		// копируем правую ветвь
		}
	}

//	деструктор
	~BinaryTree() { deleteTree(head); }

//	добавление узла в дерево
	virtual Node* add(Node* parent, int key)
	{
		if (parent == nullptr)
			return nullptr;
		else if (parent->left_kid == nullptr)
		{
			parent->left_kid = new Node(key);
			parent->left_kid->parent = parent;
			return parent->left_kid;
		}
		else if (parent->right_kid == nullptr)
		{
			parent->right_kid = new Node(key);
			parent->right_kid->parent = parent;
			return parent->right_kid;
		}
		else if (rand() % 2)
			return add(parent->left_kid, key);
		else
			return add(parent->right_kid, key);
	}

//	получение корня дерева
	Node* getHead() { return head; }

//	перегрузка оператора присваивания
	BinaryTree& operator =(BinaryTree& object)							// переделать
	{
		if (this == &object)								
			return *this;

		deleteTree(head);

		if (object.head == nullptr)
			head = nullptr;
		else
		{
			head = new Node(object.head->key); // создаём новый корень , копирую корень дерева b
			copy(object.head->left_kid, head, 0); // копируем левую ветвь дерева b
			copy(object.head->right_kid, head, 1); // копируем правую ветвь дерева b
		}

		return *this;
	}

//	вывод дерева на экран в горизонтальном виде
	void printTree(Node* parent, int marginLeft, int levelSpacing)
	{
		if (parent == nullptr)
			return;

		printTree(parent->right_kid, marginLeft + levelSpacing, levelSpacing);

		cout << std::string(marginLeft, ' ') << parent->key << endl;

		printTree(parent->left_kid, marginLeft + levelSpacing, levelSpacing);
	}

//	поиск количества узлов дерева
	int findCountNodes(Node* root)
	{
		if (root == nullptr)
			return 0;

		int count = 0;

		std::list<Node*> unprocessedNodes(1, root);
		while (!unprocessedNodes.empty()) {
			Node* node = unprocessedNodes.front();
			count++;
			if (node->left_kid) {
				unprocessedNodes.push_back(node->left_kid);
			}
			if (node->right_kid) {
				unprocessedNodes.push_back(node->right_kid);
			}
			unprocessedNodes.pop_front();
		}

		return count;
	}

//	получение вектора, содержащего все ключи дерева
	vector<int> getVecKeyTree()
	{
		vector<int> vecKeyNodes;
		addKeyInVec(head, vecKeyNodes);

		return vecKeyNodes;
	}

//	Пустое ли дерево
	bool isEmpty() 
	{
		if (head != nullptr)
			return false;
		else
			return true;
	}

//	Получение суммы ключей всех узлов дерева
	int sumNodes(Node* parent)
	{
		int sum = 0;
		vector<int> vec = getVecKeyTree();
		for (auto el : vec)
			sum += el;

		return sum;
	}

//	получение минимального ключа
	virtual int getMinKey()
	{
		Node* min = minNode(head);
		return min->key;
	}

//	получение максимального ключа
	virtual int getMaxKey()
	{
		Node* max = maxNode(head);
		return max->key;
	}

//	получение высоты дерева
	int getHeightTree(Node* head)
	{
		if (head == nullptr)
			return 0;

		int height = 0;
		if (head->right_kid != nullptr)
			height = getHeightTree(head->right_kid);

		if (head->left_kid != nullptr)
			height = max(height, getHeightTree(head->left_kid));

		return height + 1;
	}

//	метод удаления узла из дерева по ключу, возвращает bool
	virtual bool deleteNode(int search_key)
	{
		Node* parent = searchNode(head, search_key);

		if (parent == nullptr)										// проверка, что такой узел существует
		{
			cout << "Error: не удалось найти узел\n";
			return false;
		}

		// если удаляем корень дерева
		if (parent->parent == nullptr)
			return deleteHead(parent);

		Node* temp = parent->parent;

//		если у удаляемого узла нет потомков 
		if (parent->left_kid == nullptr && parent->right_kid == nullptr)
		{
			if (temp->left_kid == parent)
				temp->left_kid = nullptr;
			else
				temp->right_kid = nullptr;

			delete parent;
			return true;
		}
//		если у удаляемого узла есть только правый потомок
		else if (parent->left_kid == nullptr && parent->right_kid != nullptr)
		{
			if (temp->left_kid == parent)
				temp->left_kid = parent->right_kid;
			else
				temp->right_kid = parent->right_kid;

			parent->right_kid->parent = temp;

			delete parent; // удаляем узел
			return true;
		}
//		если у удаляемого узла есть только левый потомок
		else if (parent->left_kid != nullptr && parent->right_kid == nullptr)
		{
			if (temp->left_kid == parent)
				temp->left_kid = parent->left_kid;
			else
				temp->right_kid = parent->left_kid;
			
			parent->left_kid->parent = temp;
			
			delete parent;
			return true;
		}
		else if (parent->left_kid != nullptr && parent->right_kid != nullptr)
		{
			return deleteHead(parent);
		}

		return false;
	}

	//	Поиск узла по ключу (исп для удаления)
	virtual Node* searchNode(Node* root, int search_key)
	{
		if (root == nullptr)
			return nullptr;

		list<Node*> unprocessedNodes(1, root);
		while (!unprocessedNodes.empty())
		{
			Node* node = unprocessedNodes.front();

			if (node->key == search_key)
				return node;

			if (node->left_kid)
				unprocessedNodes.push_back(node->left_kid);

			if (node->right_kid)
				unprocessedNodes.push_back(node->right_kid);

			unprocessedNodes.pop_front();
		}

		return nullptr;
	}

//	обход дерева по уровням
	void bfsPrint(Node* root)
	{
		if (root == nullptr)
			return;

		std::list<Node*> unprocessedNodes(1, root);
		while (!unprocessedNodes.empty()) {
			Node* node = unprocessedNodes.front();
			std::cout << node->key << ' ';
			if (node->left_kid) {
				unprocessedNodes.push_back(node->left_kid);
			}
			if (node->right_kid) {
				unprocessedNodes.push_back(node->right_kid);
			}
			unprocessedNodes.pop_front();
		}
	}

//	обход дерева Л-П-К
	void lrnPrint(Node* root)
	{
		if (root == nullptr)
			return;

		lrnPrint(root->left_kid);
		lrnPrint(root->right_kid);
		std::cout << root->key << ' ';
	}
};