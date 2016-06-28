//#include <string>
#include <iostream>
#include "myString.h" 
#pragma warning(disable : 4996)

using namespace std;

//Конструкторы////////////////////////////////////////////////////
MyString::MyString() {
	this->m_pStr = new char[1];
	*m_pStr = 0;
}
MyString::MyString(const char* str) {
	this->m_pStr = new char[strlen(str)+1];//как динамический массив выделить память
	strcpy(this->m_pStr, str);
}
//конструктор копирования (поверхностное копирование)
MyString::MyString(const MyString& other) {
	this->m_pStr = new char[strlen(other.m_pStr) + 1];
	strcpy(this->m_pStr, other.m_pStr);
}
//конструктор перемещения (конструктор копирования с семантикой перемещения)
//(глубокое копирование)
MyString::MyString(MyString && tmp){
	this->m_pStr = tmp.m_pStr;
	tmp.m_pStr = nullptr;
}

//Деструктор//////////////////////////////////////////////////////
MyString::~MyString() {
	//delete[] this->m_pStr;
};

//Перегрузка операторов://////////////////////////////////////////
//1.Перегрузку оператора без семантики перемещения	
MyString& MyString::operator=(const MyString& str) {
	if (this != &str) {
		delete[] this->m_pStr;
		this->m_pStr = new char[strlen(str.m_pStr) + 1];
		strcpy(this->m_pStr, str.m_pStr);
	}
	return *this;
};
MyString& MyString::operator=(const char* str) {
	delete[] this->m_pStr;
	if ((str) != nullptr) {
		this->m_pStr = new char[strlen(str) + 1];
		strcpy(this->m_pStr, str);
	}
	else {
		this->m_pStr = nullptr;
	}
	return *this;
};
//2.Перегрузку оператора с семантикой перемещения
MyString& MyString::operator=(MyString&& other) {
	if (this != &other) {
		delete[] this->m_pStr;
		this->m_pStr = other.m_pStr;
		other.m_pStr = nullptr;
	}
	return *this;
};

void MyString::Swap(MyString& a){
	char* tmp = a.m_pStr;
	a.m_pStr = m_pStr;
	this->m_pStr = tmp;
};
