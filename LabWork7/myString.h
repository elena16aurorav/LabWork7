#pragma once
using namespace std;

class MyString
{
	char* m_pStr;	//строка-член класса
public:
	//Конструкторы////////////////////////////////////////////////////	
	MyString();
	MyString(const char* str);
	//конструктор копирования (поверхностное копирование)
	MyString(const MyString& other);
	//конструктор перемещения (конструктор копирования с семантикой перемещения)
	//(глубокое копирование)
	MyString(MyString && tmp);
	//Деструктор//////////////////////////////////////////////////////
	~MyString();
	//Перегрузка операторов://////////////////////////////////////////
	//1.Перегрузку оператора без семантики перемещения	
	MyString& operator=(const MyString& str);
	MyString& operator=(const char* str);
	//2.Перегрузку оператора с семантикой перемещения
	MyString& operator=(MyString&& other);
	void Swap(MyString& a);
};