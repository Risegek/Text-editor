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
		<< "1.��������� �������� ���� � ��������" << std::endl
		<< "2.��������� �������� ���� � ���������" << std::endl
		<< "3.������� ������" << std::endl
		<< "4.�������� ������" << std::endl
		<< "5.������� ���������� �� �����" << std::endl
		<< "6.�������� ������" << std::endl
		<< "0.�����" << std::endl;
	if (!a.is_empty()) std::cout << "������� ���� - " << a.getFile() << std::endl;
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

			std::cout << "������� ��� ���������� �����: ";
			char file_name[20];
			std::cin >> file_name;

			try {
				double beg_time = clock();
				a.TextToBinary(file_name);
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
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
			std::cout << "������� ��� ���������� �����: ";
			char file_name[20];
			std::cin >> file_name;
			try {
				double beg_time = clock();
				a.binaryToText(file_name);
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (file_open_error) {
				
				system("Pause");
			};

			break; }
		case 3: {
			std::cout << "������� ����� ������: ";
			char _num[5];
			std::cin >> _num;

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("������ �����");
					}
				}
				int num = atoi(_num);

				double beg_time = clock();
				a.deleteStr(num);
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (int) {
				std::cout << "������ �������� �����\n";
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
			std::cout << "������� ������ � �����:\n";
			char str[40];

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.getline(str, 40, '\n');
			char _num[5];
			std::cin >> _num; 

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("������ �����");
					}
				}

				int num = atoi(_num);
				double beg_time = clock();
				a.addStr(num, str);
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (int) {
				std::cout << "������ �������� �����\n";
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
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (empty_error) {
				system("Pause");

			};

			break; }
		case 6: {
			std::cout << "������� ������ � �����:\n";
			char str[40];	
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.getline(str, 40, '\n');

			char _num[5];
			std::cin >> _num;

			try {
				for (int i = 0; _num[i] != 0; i++) {
					if (!isdigit(_num[i])) {
						throw stringToInt("������ �����");
					}
				}

				int num = atoi(_num);
				double beg_time = clock();
				a.changeStr(num, str);
				std::cout << "�������! ����� ������ - " << clock() - beg_time << "ms\n";
				system("Pause");
			}
			catch (empty_error) {
				system("Pause");

			}
			catch (int) {
				std::cout << "������ �������� �����\n";
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