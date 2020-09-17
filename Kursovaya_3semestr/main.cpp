#include "binary.h"
#include <iostream>
#include <Windows.h>
#include "Error.h"
#include <climits>
#include <time.h>

#if defined(max)
#undef max
#endif

void menu(binary &a) {
	std::cout << "\t\t---===Menu===---" << std::endl
		<< "1.Загрузить тектовый файл в бинарный" << std::endl
		<< "2.Выгрузить бинарный файл в текстовый" << std::endl
		<< "3.Удалить строку" << std::endl
		<< "4.Добавить строку" << std::endl
		<< "5.Вывести содержимое на экран" << std::endl
		<< "6.Изменить строку" << std::endl
		<< "0.Выход" << std::endl;
	if (!a.is_empty()) std::cout << "Текущий файл - " << a.getFile() << std::endl;
}

int main() {

	binary a("binary");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool n = true;
	while(n) {
		system("cls");
		menu(a);
		int k;
		std::cin >> k;
		switch (k) {
		case 1: {

			std::cout << "Введите имя текстового файла: ";
			char file_name[20];
			std::cin >> file_name;

			try {
				double beg_time = clock();
				a.TextToBinary(file_name);
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (file_open_error) {
				
				system("Pause");
			}
			catch (empty_error) {
			
				system("Pause");
			};

			break; }
		case 2: {
			std::cout << "Введите имя текстового файла: ";
			char file_name[20];
			std::cin >> file_name;
			try {
				double beg_time = clock();
				a.binaryToText(file_name);
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (file_open_error) {
				
				system("Pause");
			};

			break; }
		case 3: {
			std::cout << "Введите номер строки: ";
			char _num[5];
			std::cin >> _num;

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("Ошибка ввода");
					}
				}
				int num = atoi(_num);

				double beg_time = clock();
				a.deleteStr(num);
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (int) {
				std::cout << "Введен неверный номер\n";
				system("Pause");
			}
			catch (stringToInt) {
				system("Pause");
				break;
			}
			catch (empty_error) {

				system("Pause");
			};
			break; }
		case 4: {
			std::cout << "Введите строку и номер:\n";
			char str[40];

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.getline(str, 40, '\n');
			char _num[5];
			std::cin >> _num; 

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("Ошибка ввода");
					}
				}

				int num = atoi(_num);
				double beg_time = clock();
				a.addStr(num, str);
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (int) {
				std::cout << "Введен неверный номер\n";
				system("Pause");
			}
			catch (stringToInt) {
				system("Pause");
				break;
			}
			catch (empty_error) {
				system("Pause");

			};
			break; }
		case 5: {
			try {
				double beg_time = clock();
				a.printFile();
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (empty_error) {
				system("Pause");

			};

			break; }
		case 6: {
			std::cout << "Введите строку и номер:\n";
			char str[40];	
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.getline(str, 40, '\n');

			char _num[5];
			std::cin >> _num;

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("Ошибка ввода");
					}
				}

				int num = atoi(_num);
				double beg_time = clock();
				a.changeStr(num, str);
				std::cout << "Успешно! Время работы - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (empty_error) {
				system("Pause");

			}
			catch (int) {
				std::cout << "Введен неверный номер\n";
				system("Pause");
			}
			
			break; }
		case 0: {
			n = false;
			break; }

		}
	}

	system("Pause");
	return 0;
}