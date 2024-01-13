#include "hashTable.h"

const int length_str = 5;

string generate()
{
	string str;
	for (int i = 0; i < length_str; i++)
		str += 'a' + rand() % ('z' - 'a');

	return str;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	hashTable table;

	int n;
	cout << "Введите кол-во добавляемых элементов в таблицу: ";
	cin >> n;

	cout << "\nСгенерированные строки:\n";

	for (int i = 0; i < n; i++)
	{
		Node el(generate());
		cout << el;
		table.append(el);
	}
	cout << endl;

	table.print();

	int key;
	cout << "Введите ключ для поискового (затем удаляемого) элемента: ";
	cin >> key;

	Node el(key);
	if (table.search(el))
		cout << "\nЭлемент найден\n";
	else
		cout << "\nError: не удалось НАЙТИ элемент\n";

	if (table.del_str(el.getKey()))
		cout << "Объект успешно удален\n\n";
	else
		cout << "Error: не удалось УДАЛИТЬ объект\n\n";

	table.print();


	cout << "Демонстрация КОНСТРУКТОРА КОПИРОВАНИЯ\n";
	hashTable table_2 = table, table_3;
	table_2.print();


	cout << "Демонстрация ПЕРЕГРУЗКИ ОПЕРАТОРА РАВНО\n";
	table_3 = table_2;
	table_3.print();


	cout << "Демонстрация перегрузки операта []\n";
	int key_search;
	cout << "Введите ключ: ";
	cin >> key_search;

	cout << "Значение: " << table[key_search] << endl;

	return 0;
}