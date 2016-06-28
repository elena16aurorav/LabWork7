#include <tchar.h>
#include <iostream>
#include "template_all.h"
#include "MyString.h"
//����������

//�������: 
	//		������� �������,
	//		������� �������,

//#include <stdexcept>

#define stop __asm nop

int _tmain(int argc, _TCHAR* argv[])
{
////////////////////////////////////////////////////////////////////////////
	//����. ������� �������.
	//�������� ������ ������� ������������ ������� ����
	//�������� - Swap(). ��������� ����������������� ����������
	//������� � ������� ������������ ���� ��������� ����.
	//��������� 1: ���������� ������� ���������� ��������� � .h-����.
	int iX = 1, iY = -1;
	Swap(iX, iY);

	double dX = 0.5, dY = -5.5;
	Swap(dX, dY);
	//��������� 2: ���������, ��� ����� �����������, ��� ����,
	//			����� ��������� ����� ������� � ��������� MyString
	//			�� ������ ���������, �� � ����������
	MyString str1("One"), str2("Two");
	Swap(str1, str2);
/////////////////////////////////////////////////////////////////////
	//����. ������� �������.
	//������� 1.
	//���������� ����� �� ������ �������
	//�������� ������ ������ MyStack ��� �������� ��������� ������ ���� T.
	//���������:1.�������� ����� ���-�� ������� - ������� � ������� ���������
	//			��� �������� ��������������� ������������� � ������ ���������
	//			�������� ������, 
	//			2.��� ������� ������������� ������� ����� ����� ���� �����������
	//			��������-��������� �������
	//			3.������������� ���������� �� ������ �������� "push" � "pop". ���
	//			����, ����� ������������� ���������� ���������� ���� �������� 
	//			������ ���� �� ������������ ���������� � ��������� ��������
	//			4. ������������� ���������� operator[] ����� �������, ����� ������������
	//			��� ������/�������� �������� ������ ��� ���������, ������� �� ����������
	//� ������� ������� MyStack �������� ���� �� 5 ��������� int - iStack �
	//���� �� 10 ��������� MyString - strStack � ������������������� � ���������
	//push() � pop(), operator[]
	MyStack<MyString, 10> strStack = MyStack<MyString, 10>();
	try {
		strStack.push("tvelwe");//1
		strStack.push("eleven");//2
		strStack.push("ten");//3
		strStack.push("nine");//4
		strStack.push("eight");//5
		strStack.push("seven");//6
		strStack.push("six");//7
		strStack.push("five");//8
		strStack.push("four");//9
		strStack.push("three");//10
		strStack.push("two");//!!!!!
		
	}
	catch (const char* error) {
		cout << error << endl;
	}
	strStack.getCount();

	try {
		strStack[5] = "newnewnew";
	}
	catch (const char* error) {
		cout << error << endl;
	}	

	try {
		strStack.pop();//10
		strStack.pop();//9
		strStack.pop();//8
		strStack.pop();//7
		strStack.pop();//6
		strStack.pop();//5
		strStack.pop();//4
		strStack.pop();//3
		strStack.pop();//2
		strStack.pop();//1
		strStack.pop();//!!!!!
	}
	catch (const char* error) {
		cout << error << endl;
	}
	strStack.getCount();

	/////////////////////////////////////////////////////////////
	MyStack<int, 5> iStack = MyStack<int, 5>();
	try {
		iStack.push(9);
		iStack.push(8);
		iStack.push(7);
		iStack.push(6);
		iStack.push(5);
		iStack.push(4);//!!!!!
		iStack.getCount();
	}
	catch (const char* error) {
		cout << error << endl;
	}
	iStack.getCount();

	try {
		iStack[4] = 987654321;
	}
	catch (const char* error) {
		cout << error << endl;
	}

	try {
		iStack.pop();
		iStack.pop();
		iStack.pop();
		iStack.pop();
		iStack.pop();
		iStack.pop();//!!!!!
	}
	catch (const char* error) {
		cout << error << endl;
	}
	iStack.getCount();

	//������� 2. ���������� ������ ����� - MyStack2 ����� �������, ����� 
	//��� �������� ��������� ������������� ����������� ������.
	//���������� ����������� ����������� �������� ����� � ��� �������, � ������� �� ������� (push())
	//������������
	MyStack2<int> iStack2 = MyStack2<int>();
	iStack2.push(9);
	iStack2.push(8);
	iStack2.push(7);
	iStack2.push(6);
	iStack2.push(5);
	iStack2.push(4);
	iStack2.getCount();
	iStack2.printStack();
	int n = iStack2.getCount();
	for (int i = 0; i < n; i++) {
		iStack2.pop();
	}
	iStack2.getCount();

	MyStack2<int> iStack3 = MyStack2<int>();
	iStack3.push(0);
	iStack3.push(1);
	iStack3.push(2);
	iStack3.push(3);
	iStack3.push(4);
	iStack3.push(5);
	MyStack2<int> iStack4 = MyStack2<int>();
	iStack4.push(11);
	iStack4.push(22);
	iStack4.push(33);
	iStack4.push(44);
	
	//iStack3.~MyStack2();
	//MyStack2<int> iStack6(iStack3);
	//MyStack2<int> iStack6 = std::move(iStack3);
	MyStack2<int> iStack6;
	//iStack6 = std::move(iStack3);
	//iStack6 = iStack3;//1
	//iStack3 = iStack4;//2
	iStack4 = iStack3;//3
	
	//������� 3. ���������� ������ ������� - MyQueue ����� �������, ����� 
	//��� �������� ��������� ������������� ������������ ������ (�� ����������).
	//��� ������������� ������� ������� ������ ��������� �������, �� ����
	//����� �������� "�����", � "������" ������ ����� ��� ������� ��������� ��������
	//=> ������ ���� ����������� ��������� �����
	MyQueue<int> iQueue = MyQueue<int>();//1
	iQueue.getCount();//1
	iQueue.printQueue();//1

	iQueue.push(11);//2
	iQueue.push(22);//2
	iQueue.push(33);//2
	iQueue.push(44);//2
	iQueue.push(55);//2
	iQueue.push(66);//2
	iQueue.push(77);//2
	iQueue.push(88);//2 
	iQueue.push(99);//2
	iQueue.getCount();//2
	iQueue.printQueue();//2

	iQueue.pop();//3
	iQueue.pop();//3
	iQueue.pop();//3
	iQueue.getCount();//3
	iQueue.printQueue();//3

	iQueue.push(111);//4
	iQueue.getCount();//4
	iQueue.printQueue();//4

	iQueue.push(222);//5
	iQueue.getCount();//5
	iQueue.printQueue();//5

	iQueue.push(333);//6
	iQueue.push(444);//6
	iQueue.getCount();//6
	iQueue.printQueue();//6

	iQueue.pop();//7
	iQueue.pop();//7
	iQueue.getCount();//7
	iQueue.printQueue();//7

	iQueue.push(555);//8
	iQueue.push(999);//8
	iQueue.printQueue();//8
	iQueue.push(9999);//8
	iQueue.getCount();//8
	iQueue.printQueue();//8

	iQueue[2] = 4;
	iQueue.printQueue();

	return 0;
};

