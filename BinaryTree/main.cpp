#include "BinaryTreeSearch.h"

int main()
{
//			БИНАРНОЕ ДЕРЕВО ПОИСКА

	srand(time(0));
	setlocale(LC_ALL, "ru");

//	создание бинарного дерева
	BinaryTreeSearch one(10);
	one.printTree(one.getHead(), 2, 3);

//	поиск минимального и максимального ключей
	cout << "\nМинимальный ключ: " << one.getMinKey() << endl;;
	cout << "Максимальный ключ: " << one.getMaxKey() << endl << endl;

//	проверка корректности конструктора копирования
	BinaryTreeSearch two = one;
	two.printTree(one.getHead(), 2, 3);

//	удаление узла/корня из дерева
	int choice;
	cout << "\nВведите ключ узла, который хотите удалить: ";
	cin >> choice;

	one.deleteNode(choice);
	one.printTree(one.getHead(), 2, 3);

	cout << endl << endl;

//	поиск узла по ключу
	int search_key;
	cout << "Введите ключ узла, который хотите найти: ";
	cin >> search_key;

	cout << one.searchNode(one.getHead(), search_key) << endl;					// вывод найденного ключа, если не найден, выведется соответствующее сообщение

//	за счёт public наследования в BinaryTreeSearch доступны public методы из класса BinaryTree (и protected методы, но они могут использоваться только внутри класс)
	cout << one.findCountNodes(one.getHead()) << endl;

	return 0;
}