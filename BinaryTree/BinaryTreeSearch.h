#pragma once
#include "BinaryTree.h"

class BinaryTreeSearch : public BinaryTree
{
	Node* head;

private:
//	метод удаления корня, если он имеет: 1 вершину слева/справа, не имеет вершин, имеет обе вершины (исп для удаления узлов в дереве)
	bool deleteHead(Node* parent)
	{
		if (parent->right_kid == nullptr && parent->left_kid == nullptr)
		{
			delete parent;
			return true;
		}
		else if (parent->right_kid != nullptr && parent->left_kid == nullptr)
		{
			Node* temp = parent->right_kid;
			int count = 0;

			while (temp->left_kid != nullptr)
			{
				temp = temp->left_kid;
				count++;
			}

			if (temp->right_kid == nullptr && count == 0)
			{
				parent->key = temp->key;
				temp->parent->right_kid = nullptr;
			}
			else if (temp->right_kid == nullptr && count > 0)
			{
				parent->key = temp->key;
				temp->parent->left_kid = nullptr;
			}
			else if (temp->right_kid != nullptr && count == 0)
			{
				Node* temp_address_kid = temp->right_kid;
				Node* temp_address_parent = temp->parent;

				parent->key = temp->key;
				temp->right_kid->parent = temp->parent;
				temp->parent->right_kid = nullptr;

				temp_address_parent->right_kid = temp_address_kid;
			}
			else if (temp->right_kid != nullptr && count > 0)
			{
				Node* temp_address_kid = temp->right_kid;
				Node* temp_address_parent = temp->parent;

				parent->key = temp->key;
				temp->right_kid->parent = temp->parent;
				temp->parent->left_kid = nullptr;

				temp_address_parent->left_kid = temp_address_kid;
			}

			return true;
		}
		else if (parent->right_kid == nullptr && parent->left_kid != nullptr)
		{
			Node* temp = parent->left_kid;
			int count = 0;

			while (temp->right_kid != nullptr)
			{
				temp = temp->right_kid;
				count++;
			}

			if (temp->left_kid == nullptr && count == 0)
			{
				parent->key = temp->key;
				temp->parent->left_kid = nullptr;
			}
			else if (temp->left_kid == nullptr && count > 0)
			{
				parent->key = temp->key;
				temp->parent->right_kid = nullptr;
			}
			else if (temp->left_kid != nullptr && count == 0)
			{
				Node* temp_address_kid = temp->left_kid;
				Node* temp_address_parent = temp->parent;

				parent->key = temp->key;
				temp->left_kid->parent = temp->parent;
				temp->parent->left_kid = nullptr;

				temp_address_parent->left_kid = temp_address_kid;
			}
			else if (temp->left_kid != nullptr && count > 0)
			{
				Node* temp_address_kid = temp->left_kid;
				Node* temp_address_parent = temp->parent;

				parent->key = temp->key;
				temp->left_kid->parent = temp->parent;
				temp->parent->right_kid = nullptr;

				temp_address_parent->right_kid = temp_address_kid;
			}

			return true;
		}
		else if (parent->right_kid != nullptr && parent->left_kid != nullptr)
		{
			Node* temp_right = parent->right_kid;
			Node* temp_left = parent->left_kid;
			int count_right = 0, count_left = 0;

			while (temp_right->left_kid != nullptr)
			{
				temp_right = temp_right->left_kid;
				count_right++;
			}

			while (temp_left->right_kid != nullptr)
			{
				temp_left = temp_left->right_kid;
				count_left++;
			}

			int left_key = 0, right_key = 0;

			left_key = parent->key - temp_left->key;
			right_key = temp_right->key - parent->key;

			if (left_key <= right_key)
			{

				if (temp_left->left_kid == nullptr && count_left == 0)
				{
					parent->key = temp_left->key;
					temp_left->parent->left_kid = nullptr;
				}
				else if (temp_left->left_kid == nullptr && count_left > 0)
				{
					parent->key = temp_left->key;
					temp_left->parent->right_kid = nullptr;
				}
				else if (temp_left->left_kid != nullptr && count_left == 0)
				{
					Node* temp_address_kid = temp_left->left_kid;
					Node* temp_address_parent = temp_left->parent;

					parent->key = temp_left->key;
					temp_left->left_kid->parent = temp_left->parent;
					temp_left->parent->left_kid = nullptr;

					temp_address_parent->left_kid = temp_address_kid;
				}
				else if (temp_left->left_kid != nullptr && count_left > 0)
				{
					Node* temp_address_kid = temp_left->left_kid;
					Node* temp_address_parent = temp_left->parent;

					parent->key = temp_left->key;
					temp_left->left_kid->parent = temp_left->parent;
					temp_left->parent->right_kid = nullptr;

					temp_address_parent->right_kid = temp_address_kid;
				}

				return true;
			}
			else
			{
				if (temp_right->right_kid == nullptr && count_right == 0)
				{
					parent->key = temp_right->key;
					temp_right->parent->right_kid = nullptr;
				}
				else if (temp_right->right_kid == nullptr && count_right > 0)
				{
					parent->key = temp_right->key;
					temp_right->parent->left_kid = nullptr;
				}
				else if (temp_right->right_kid != nullptr && count_right == 0)
				{
					Node* temp_address_kid = temp_right->right_kid;
					Node* temp_address_parent = temp_right->parent;

					parent->key = temp_right->key;
					temp_right->right_kid->parent = temp_right->parent;
					temp_right->parent->right_kid = nullptr;

					temp_address_parent->right_kid = temp_address_kid;
				}
				else if (temp_right->right_kid != nullptr && count_right > 0)
				{
					Node* temp_address_kid = temp_right->right_kid;
					Node* temp_address_parent = temp_right->parent;

					parent->key = temp_right->key;
					temp_right->right_kid->parent = temp_right->parent;
					temp_right->parent->left_kid = nullptr;

					temp_address_parent->left_kid = temp_address_kid;
				}

				return true;
			}
		}

		return false;
	}

//	нахождение минимального узла (исп для получения максимального ключа узла)
	Node* minNode(Node* root)
	{
		while (root->left_kid != nullptr)
			root = root->left_kid;

		return root;
	}

//	нахождение максимального узла (исп для получения минимального ключа узла)
	Node* maxNode(Node* root)
	{
		while (root->right_kid != nullptr)
			root = root->right_kid;

		return root;
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
public:

//	Конструктор по умолчанию (без параметров)
	BinaryTreeSearch() { head = nullptr; }

//	конструктор с параметром "длина дерева"
	BinaryTreeSearch(int treeSize)
	{
		for (int i = 0; i < treeSize; i++)
			head = add(head, rand() % 1000);
	}

//	конструктор копирования
	BinaryTreeSearch(const BinaryTreeSearch& object)
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

//	перегрузка оператора присваивания
	BinaryTreeSearch& operator =(BinaryTreeSearch& object)							// переделать
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

//	деструктор
	~BinaryTreeSearch() { deleteTree(head); }

//	получение корня дерева
	Node* getHead() { return head; }

//	добавление узла в дерево
	Node* add(Node* root, int key) override
	{
		if (root == nullptr)
		{
			root = new Node(key);
		}
		else if (key < root->key)
		{
			root->left_kid = add(root->left_kid, key);
			root->left_kid->parent = root;
		}
		else 
		{
			root->right_kid = add(root->right_kid, key);
			root->right_kid->parent = root;
		}

		return root;
	}

//	получение минимального ключа узла в дереве
	int getMinKey() override
	{
		Node* min = minNode(head);
		return min->key;
	}

//	получение максимального ключа узла в дереве
	int getMaxKey() override
	{
		Node* max = maxNode(head);
		return max->key;
	}

//	поиск узла с нужным ключом
	Node* searchNode(Node* root, int search_key) override
	{
		while (root != nullptr)
		{
			if (root->key == search_key)		// если узел с нужным ключом найден	
				return root;

			if (search_key > root->key)			// если ключ > ключа узла, то идём направо (принцип построения бин дерева поиска)
				root = root->right_kid;
			else
				root = root->left_kid;			// иначе идём налево
		}

		cout << "Error: не удалось найти узел\n";
		return nullptr;
	}

//	метод удаления узла из дерева по ключу, возвращает bool
	bool deleteNode(int search_key) override
	{
		Node* temp;
		Node* parent = searchNode(head, search_key);

		if (parent == nullptr)										// проверка, что такой узел существует
		{
			cout << "Error: не удалось найти узел\n";
			return false;
		}

		if (parent->parent == nullptr)
			return deleteHead(parent);

		if (parent->right_kid == nullptr && parent->left_kid == nullptr)
		{
			temp = parent->parent;
			if (temp->right_kid == parent)
			{
				temp->right_kid = nullptr;
				
				delete parent;
				return true;
			}
			else if (temp->left_kid == parent)
			{
				temp->left_kid = nullptr;
				delete parent;

				return true;
			}

			return true;
		}
		else if (parent->left_kid == nullptr && parent->right_kid != nullptr)
		{
			temp = parent->parent;

			if (temp->left_kid == parent)
				temp->left_kid = parent->right_kid;
			else
				temp->right_kid = parent->right_kid;

			parent->right_kid->parent = temp;

			delete parent;
			return true;
		}
		else if (parent->left_kid != nullptr && parent->right_kid == nullptr)
		{
			temp = parent->parent;

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
			temp = parent->parent;

			Node* t = parent->left_kid;
			if (t->right_kid == nullptr)
			{
				t->parent = temp;
				if (temp->left_kid == parent)
					temp->left_kid = t;
				else 
					temp->right_kid = t;
				
				t->right_kid = parent->right_kid;
				parent->right_kid->parent = t;
			}
			else
			{
				while (t->right_kid != nullptr)
					t = t->right_kid;
				t->parent->right_kid = t->left_kid;

				if (t->left_kid != nullptr)
					t->left_kid->parent = t->parent;

				t->left_kid = parent->left_kid;
				t->right_kid = parent->right_kid;

				parent->left_kid->parent = t;
				parent->right_kid->parent = t;

				t->parent = temp;

				if (temp->left_kid == parent)
					temp->left_kid = t;
				else
					temp->right_kid = t;
			}

			delete parent;
			return true;
		}


		return false;
	}
};