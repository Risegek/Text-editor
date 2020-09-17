#include "binary.h"
#include "Error.h"
#pragma warning(disable:4996)

//����� ��������� �����, ����������� �� fstream.�������� ���� ��������
//�������� ��������� ������.��������� ������ ������������ ����� ������� ���������
//��������, ������������ ��������� ������ ��� �������������� ��������
//�������������� �����.������ ���� ����������� �������� �������� � ����������
//��������� ����� �� ��������� ���������� ����� � ���������� ����������� ���������
//����� � ��������� ����, 
//� ����� �������� ����������, ��������, ������� �
//�������������� �����.
//��������� ������ ������������� ��������� ���� ��������.��������������
//��������� ������.��������� ������������ ������ ��������� ����, ��������������
//����� ��������.

//����� � �������� ����, ����������� �� fstream.���� �������� ������ ���������� ��
//������, �������������� �������� ���������� ����� : ����� ������� �
//������������������ �������� ������(��� 0 - ������������).������ ����� : � ������ �
//�����, ����������� ������� ����������, ������� ���������� ����������, �����
//(��������) ������� ���������� � �����.


binary::binary(const char* name_file) : std::fstream(name_file, std::ios::trunc |std::ios::in | std::ios::out | std::ios::binary) {

	name_text = nullptr;
	int cpy_len = strlen(name_file);
	binary_name = new char[cpy_len + 1];
	strcpy(binary_name, name_file); //���������� ����� ��������� �����

	int size = 4;
	int k = 0;
	int ad = 12;

	int *mas = new int[size];
	for (int i = 0; i < size; i++) mas[i] = 0;

	write(reinterpret_cast <char *> (&size), sizeof(int));
	write(reinterpret_cast <char *> (&k), sizeof(int));
	write(reinterpret_cast <char *> (&ad), sizeof(int));

	write(reinterpret_cast <char *> (mas), sizeof(int) * size);//������ �������
	delete[] mas;
}

void binary::addElem(int  _pos, int num) {
	int copyPosArr;
	seekg(sizeof(int) * 2, std::ios::beg);
	read(reinterpret_cast <char *> (&copyPosArr), sizeof(int));//��������� ����� ������� � �����

	seekp(copyPosArr + sizeof(int) * num, std::ios::beg); //��������� � ������� �������� � �������

	write(reinterpret_cast <char *> (&_pos), sizeof(int));//���������� ������� ������

	int asd = num + 1;
	seekp(sizeof(int), std::ios::beg);
	write(reinterpret_cast <char *> (&asd), sizeof(int));//�������� ������� ���������� ���������� � �����

}

void binary::resizeArr() {
	int copyPosArr = tellp();//����������� ������� ������� ������
	seekp(0, std::ios::beg);

	int size;
	read(reinterpret_cast <char *> (&size), sizeof(int));
	size = size * 2;//���������� ������� ������� � ���������� ��� �����

	seekp(0, std::ios::beg);
	write(reinterpret_cast <char *> (&size), sizeof(int));//������ ������ ������� � ����

	int cpy_pos;
	seekg(sizeof(int) * 2, std::ios::beg);
	read(reinterpret_cast <char *> (&cpy_pos), sizeof(int));

	seekg(cpy_pos, std::ios::beg);

	int* cpyArr = new int[size];//�������� ������� ����� ������ �����������
	for (int i = 0; i < size; i++)	cpyArr[i] = 0;

	read(reinterpret_cast <char *> (cpyArr), sizeof(int) * (size / 2)); //���������� ������� ������� � �����

	seekp(sizeof(int) * 2, std::ios::beg);
	write(reinterpret_cast <char *> (&copyPosArr), sizeof(int));//������ ������ ������ ������� � �����

	seekp(copyPosArr, std::ios::beg);
	write(reinterpret_cast <char *> (cpyArr), sizeof(int) * size);//������ �������

	delete[] cpyArr;
}

void binary::TextToBinary(const char* nameText) {
		
	std::ifstream in(nameText, std::ios::in);
	if (!in) throw file_open_error("������ �������� �����");
	if (in.peek() == EOF) throw empty_error("������, ���� ������");

	name_text = new char[strlen(nameText) + 1];
	strcpy(name_text, nameText);
	int size;
	seekp(0, std::ios::beg);
	read(reinterpret_cast<char*>(&size), sizeof(int));

	for (int i = 0; !in.eof(); i++) {
		seekp(0, std::ios::end);

		if (i >= size) {//���� ����� ������ ��� ������ �������, ���������� ��� �����
			resizeArr();
			size *= 2;
		}	
		int adr_1 = tellp();
		
		char* arr = new char[128];
		in.getline(arr, 128, '\n');//���������� ������ � ���������� �����

		int len = strlen(arr);
		write(reinterpret_cast <char *> (&len), sizeof(int));
		write(arr, len);//������ ������ � �������� ����
		delete[] arr;

		addElem(adr_1, i); //����� ���������� �������� � ������

	}
	in.close();
	
}

void binary::binaryToText(const char* nameText) {
	if (is_empty()) throw empty_error("������, ���� �� �������� ");
	seekg(0, std::ios::beg);
	std::ofstream out(nameText, std::ios::out);
	if (!out) throw file_open_error("������ �������� �����");

	int count_uk;
	int arr_pos;
	int size;
	read(reinterpret_cast <char *> (&size), sizeof(int));// ���������� ����������
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	read(reinterpret_cast <char *> (&arr_pos), sizeof(int));

	for (int i = 0; i < count_uk; i++) {
		seekg(arr_pos + sizeof(int) * i, std::ios::beg);
		int index;
		read(reinterpret_cast <char *> (&index), sizeof(int));
		seekg(index, std::ios::beg);   //������� � ������ � �����
									   
		int len;					   
		read(reinterpret_cast <char *> (&len), sizeof(int));
		char* arr = new char[len+1];
		read(arr, len); //���������� ������
		arr[len] = 0;
		out << arr;//�������� � ��������� ����
		if (i != count_uk) out << '\n';

	}
	out.close();
}


void binary::deleteStr(int num) {
	if (is_empty()) throw empty_error("������, ���� �� �������� ");

	seekg(0, std::ios::beg);
	int size;
	int count_uk;
	int cpy_adr_mas;
								   
	read(reinterpret_cast <char *> (&size), sizeof(int)); //���������� ����������
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	
	if (num >= count_uk) {
		throw -1;
	}

	read(reinterpret_cast <char *> (&cpy_adr_mas), sizeof(int));
	seekg(cpy_adr_mas, std::ios::beg);

	int* cpyArr = new int[size];
	for (int i = 0; i < size; i++) cpyArr[i] = 0;
	read(reinterpret_cast <char *> (cpyArr), sizeof(int)* count_uk);//���������� �������

	count_uk--; 
	seekp(0, std::ios::beg);
	write(reinterpret_cast <char *> (&size), sizeof(int));
	write(reinterpret_cast <char *> (&count_uk), sizeof(int));

	for (int i = num; i < size-1; i++) {//c������� ������� ����������
		cpyArr[i] = cpyArr[i + 1];
	}

	seekp(cpy_adr_mas, std::ios::beg);
	write(reinterpret_cast <char *> (cpyArr), sizeof(int)* size); //������ ������ ������� � �������� ����

	seekp(0, std::ios::beg);
	delete[] cpyArr;
}


void binary::printFile() {
	if (is_empty()) throw empty_error("������, ���� �� �������� ");

	int cpy_adr_mas;
	int cpy_size;
	int count_uk;
	seekg(0, std::ios::beg);
	read(reinterpret_cast <char *> (&cpy_size), sizeof(int));
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	read(reinterpret_cast <char *> (&cpy_adr_mas), sizeof(int));

	for (int i = 0; i < count_uk; i++) {
		int a = cpy_adr_mas + sizeof(int) * i;
		seekg(a, std::ios::beg);
		int index;
		read(reinterpret_cast <char *> (&index), sizeof(int));
		seekg(index, std::ios::beg);
		
		int cpy_len;
		read(reinterpret_cast <char *> (&cpy_len), sizeof(int));
		char* cpystr = new char[cpy_len + 1];
		read(cpystr, cpy_len);
		cpystr[cpy_len] = 0;
		std::cout << i << ") ";
		for (int j = 0; cpystr[j] != 0; j++) 
			std::cout << cpystr[j];
		std::cout << std::endl;
	}

}


void binary::changeStr(int num, const char* str) {
	if (is_empty()) throw empty_error("������, ���� �� �������� ");
	int count_uk;
	seekg(sizeof(int), std::ios::beg);
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	if (num > count_uk) {
		throw 1;
	}
	
	seekp(0,std::ios::end);
	int copy_pos = tellp();
	int len = strlen(str);
	write(reinterpret_cast <char *> (&len), sizeof(int));
	write(str, len); //������ ������ � ����� �����

	int cpy_adr;
	seekg(sizeof(int) * 2, std::ios::beg);
	read(reinterpret_cast <char *> (&cpy_adr), sizeof(int));

	seekp(cpy_adr + sizeof(int) * num, std::ios::beg);
	write(reinterpret_cast <char *> (&copy_pos), sizeof(int)); //������� ������ ��������� � ������
}


void binary::addStr(int num, const char* str) {
	if (is_empty()) throw empty_error("������, ���� �� �������� ");
	int cpy_adr_mas;
	int cpy_size;
	int count_uk;
	seekg(0, std::ios::beg);
	read(reinterpret_cast <char *> (&cpy_size), sizeof(int));//���������� ����������
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	
	if (num > count_uk) {
		throw 1;
	}

	seekp(0, std::ios::end);
	int copy_pos = tellp();
	int len = strlen(str);
	write(reinterpret_cast <char *> (&len), sizeof(int));
	write(str, len);

	if (cpy_size == count_uk) { 
		resizeArr();
	}

	seekg(0, std::ios::beg);
	read(reinterpret_cast <char *> (&cpy_size), sizeof(int));
	read(reinterpret_cast <char *> (&count_uk), sizeof(int));
	read(reinterpret_cast <char *> (&cpy_adr_mas), sizeof(int));

	seekg(cpy_adr_mas, std::ios::beg);
	int* mas = new int[cpy_size];
	read(reinterpret_cast <char *> (mas), sizeof(int)* cpy_size); //���������� ������� ����������
	
	int* mas1 = new int[cpy_size];
	for (int i = 0; i < cpy_size; i++) { //�������� ������� � ������
		if (i < num) mas1[i] = mas[i];
		else if (i == num) mas1[i] = copy_pos;
		else mas1[i] = mas[i-1];
	}
	
	
	seekp(cpy_adr_mas, std::ios::beg);

	write(reinterpret_cast <char *> (mas1), sizeof(int)* cpy_size); //������ ������ ������� � ����

	seekp(sizeof(int), std::ios::beg);
	count_uk++;
	write(reinterpret_cast <char *> (&count_uk), sizeof(int));
	delete[] mas;
	delete[] mas1;
}

bool binary::is_empty() {
	if (name_text) return false;
	else return true;
}




