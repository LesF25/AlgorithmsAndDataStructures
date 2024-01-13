#include "Header.h"

int main()
{
	setlocale(LC_ALL, "ru");

	Haffman object;

	string information = "SUSIE SAYS IT IS EASY";
	string decode_str, code_str;

//	Пример номер 1
	cout << "ПРИМЕР НОМЕР 1\n\n";
	cout << "Кодируемый текст:\n" << information << "\n\n";

	double result_code_1 = object.encode(information, code_str);
	if (result_code_1 != -1)
	{
		cout << "Закодированная строка:\n" << code_str << "\n\n";
		cout << "Коэффициент сжатия: " << result_code_1 << "\n\n";

		object.decode(code_str, decode_str);
		cout << "Раскодированная строка:\n" << decode_str << "\n\n\n\n";
	}
	else
		cout << "Кодирование не выполнено\n\n";


//	Пример номер 2
	cout << "ПРИМЕР НОМЕР 2\n\n";

	string information_2;
	cout << "Введите текст, который хотите закодировать:\n";
	cin >> information;

	decode_str = "", code_str = "";
	cout << "Кодируемый текст:\n" << information << "\n\n";

	double result_code_2 = object.encode(information, code_str);
	if (result_code_2 != -1)
	{
		cout << "Закодированная строка:\n" << code_str << "\n\n";
		cout << "Коэффициент сжатия: " << result_code_2 << "\n\n";

		object.decode(code_str, decode_str);
		cout << "Раскодированная строка:\n" << decode_str << "\n\n\n\n";
	}
	else
		cout << "Кодирование не выполнено\n\n";

	return 0;
}