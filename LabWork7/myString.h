#pragma once
using namespace std;

class MyString
{
	char* m_pStr;	//������-���� ������
public:
	//������������////////////////////////////////////////////////////	
	MyString();
	MyString(const char* str);
	//����������� ����������� (������������� �����������)
	MyString(const MyString& other);
	//����������� ����������� (����������� ����������� � ���������� �����������)
	//(�������� �����������)
	MyString(MyString && tmp);
	//����������//////////////////////////////////////////////////////
	~MyString();
	//���������� ����������://////////////////////////////////////////
	//1.���������� ��������� ��� ��������� �����������	
	MyString& operator=(const MyString& str);
	MyString& operator=(const char* str);
	//2.���������� ��������� � ���������� �����������
	MyString& operator=(MyString&& other);
	void Swap(MyString& a);
};