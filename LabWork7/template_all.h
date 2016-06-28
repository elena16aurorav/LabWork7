#pragma once
#include <iostream>
#include "MyString.h"
#define PLUS_CAPACITY 2

template <typename T> void Swap(T& a, T& b) {
	//T tmp = a;
	//a = b;
	//b = tmp;
	T tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
};

template <> void Swap<MyString>(MyString& a, MyString& b){
	a.Swap(b);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
//			1.элементы нужно где - то хранить - простым и удобным средством
//			для хранения последовательно расположенных в памяти элементов
//			является массив, 
//			2.для задания максимального размера стека может быть использован
//			параметр-константа шаблона
//			3.обязательными операциями со стеком являются "push" и "pop". Для
//			того, чтобы гарантировать корректное выполнение этих операций 
//			хорошо было бы генерировать исключение в аварийной ситуации
//			4. дополнительно реализуйте operator[] таким образом, чтобы пользователь
//			мог читать/изменять значения только тех элементов, которые он формировал
template <typename T, int size> class MyStack {//реализация стека на основе массива
	int m_count=0;
	T m_ar[size];
public:
	void push(const T& element) {//вставка элемента
		if (m_count < size) {
			m_count++;
			m_ar[m_count - 1] = element;
		}
		else {
			throw "Error! Out of limits of arroy!";
		}
	};
	
	T pop() {//удаление элемента
		if (m_count > 0) {
			T tmp = m_ar[m_count - 1];
			m_ar[m_count - 1] = 0;
			m_count--;
			return tmp;
		}
		else {
			throw "Error! Out of limits of arroy!";
		}
	};

	int getCount() const{
		return m_count;
	}
	T& operator[](int index) {
		if (m_count <= size&&m_count > 0) {
			return m_ar[index - 1];
		}
		else {
			throw "Error! Out of limits of arroy!";
		}
	}
	////////////
	MyStack() {};
	~MyStack() {};

	MyStack(const MyStack& other) {
		for (int j = 0; j < m_count; j++) {
			m_ar[j] = other.m_ar[j];
		}
		m_count = other.m_count;
	}

	MyStack(MyStack&& other) {
		for (int j = 0; j < m_count; j++) {
			m_ar[j] = std::move(other.m_ar[j]);
		}
		m_count = other.m_count;
		other.m_count = 0;
	}

	MyStack& operator=(const MyStack& other) {
		if (this != &other) {
			for (int j = 0; j < m_count; j++) {
				m_ar[j] = other.m_ar[j];
			}
			m_count = other.m_count;
		}
			return *this;
	}

	MyStack& operator=(MyStack&& other) {
		if (this != &other) {
			for (int j = 0; j < m_count; j++) {
				m_ar[j] = std::move(other.m_ar[j]);
			}
			m_count = other.m_count;
			other.m_count = 0;
		}
			return *this;
	}
	////////////////////
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T> class MyStack2 {//реализация стека на основе односвязного списка
public:
	class Node {
	public:
		Node* pNext=nullptr;
		T m_data;
		Node(){};
		Node(const T& data) : m_data(data){};
	};

	Node* pHead = nullptr;//new Node();
	int m_count;

	MyStack2() {
		m_count = 0;
	};

	~MyStack2() {
		while (pHead != nullptr) { 
			Node* tmp = pHead;  //tmp = pHead; pHead = pHead->pNext; del...
			pHead = pHead->pNext;
			delete tmp;
		}		
		m_count = 0;
	};
		
	void push(const T& element) {
		if (sizeof(element)>0) {
			Node* pNode = new Node(element);
			pNode->pNext=pHead;
			pHead = pNode;
			m_count++;
		}
	};
	int getCount() {
		return m_count;
	};
	T pop() {
		if (m_count > 0) {
			T tmp = pHead->m_data;
			pHead = pHead->pNext;
			m_count--;
			return tmp;
		}
		return T();
	};
	void printStack() {
		if (m_count > 0) {
			Node* pNode = pHead;
			while (pNode->pNext != nullptr) {
				std::cout << pNode->m_data << std::endl;
				pNode=pNode->pNext;
			};
		};
	};
	//////////////
	MyStack2(const MyStack2& other) {
		if (other.m_count>0) {
			this->m_count = other.m_count;
			this->pHead = new Node(other.pHead->m_data);
			Node* tmp = this->pHead;
			Node* other_tmp = other.pHead;
			for (int i = 1; i < m_count; i++) {
				tmp->pNext = new Node(other_tmp->pNext->m_data);
				tmp = tmp->pNext;
				other_tmp = other_tmp->pNext;
			}
		}
	}

	MyStack2(MyStack2&& other) {
		if (other.m_count) {
			this->pHead = other.pHead;
			this->m_count = other.m_count;
			other.pHead = nullptr;
			other.m_count = 0;
		}
	}

	MyStack2& operator= (const MyStack2& other) {
		if (this != &other) {
			if (other.m_count) {
				if (m_count == other.m_count) {
					Node* tmp = &pHead;
					const Node* other_tmp = &other.pHead;
					for (int i = 0; i < m_count; i++) {
						tmp->pNext->m_data = other_tmp->pNext->m_data;
						tmp = tmp->pNext;
						other_tmp = other_tmp->pNext;
					}
					return *this;
				}
				else if (m_count > other.m_count) {
					Node* tmp = &pHead;
					Node* tmp2;
					Node* tmp3;
					const Node* other_tmp = &other.pHead;
					for (int i=0; i < other.m_count; i++) {
						tmp->pNext->m_data = other_tmp->pNext->m_data;
						tmp3 = tmp;
						tmp = tmp->pNext;
						other_tmp = other_tmp->pNext;
					}
					tmp = tmp->pNext;
					for (int i=0; i < m_count; i++) {
						tmp2 = tmp->pNext;
						delete tmp;
						tmp = tmp2;
					}
					tmp3->pNext->pNext = nullptr;
					m_count = other.m_count;
					return *this;
				}
				else if (m_count < other.m_count) {
					Node* tmp = &pHead;
					const Node* other_tmp = &other.pHead;
					for (int i=0; i < m_count; i++) {
						tmp->pNext->m_data = other_tmp->pNext->m_data;
						tmp = tmp->pNext;
						other_tmp = other_tmp->pNext;
					}
					for (int i=0; i < other.m_count; i++) {
						tmp->pNext = new Node;
						tmp->pNext->m_data = other_tmp->pNext->m_data;
						tmp = tmp->pNext;
						other_tmp = other_tmp->pNext;
					}
					m_count = other.m_count;
					//return *this;
				}
			}
			else {
				*this = MyStack();
			}
		}
		return *this;
	}

	MyStack2& operator=(MyStack2&& other) {
		if (this != &other) {
			if (other.m_size) {
				this->~MyStack2();
				m_size = other.m_count;
				other.m_count = 0;
				pHead.pNext = other.pHead.pNext;
				other.pHead.pNext = nullptr;
				//return *this;
			}
			else {
				*this = MyStack();
			}
		}
		return *this;
	}
	/////////////
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T> class MyQueue //реализация кругового буфера (кольцевой очереди)
{
	int m_cap;
	int m_n = 0;
	int m_first = 0;
	int m_last = 0;
	T* m_arDyn;
public:
	MyQueue(int cap = 10): m_cap(cap), m_n(0), m_first(0), m_last(0), m_arDyn(new T[m_cap]) {};
	~MyQueue() { delete[] m_arDyn; };
	void push(const T& element) {
		if (m_n < m_cap) {
			m_arDyn[m_last] = element;
			m_n++;
			m_last = (m_last + 1) % m_cap;
		}
		else {
			int new_cap = m_cap + PLUS_CAPACITY;
			T* tmp = new T[new_cap];
			int j = m_first;
			for (int i = 0; i < m_cap; i++) {
				tmp[i]= m_arDyn[j];
				j = (j + 1) % m_cap;
			};
			tmp[m_cap] = element;
			m_cap = new_cap;
			m_n++;
			m_first = 0;
			m_last = (m_first + m_n) % m_cap;
			delete[] m_arDyn;
			m_arDyn = new T[m_cap];
			m_arDyn = tmp;
		}
	};
	T pop() {
		T tmp;
		if (m_n <= m_cap&&m_n>0) {
			tmp = m_arDyn[m_first];
			m_first++;
			m_n--;
		}
		return tmp;
	};
	void printQueue() {
		std::cout <<"*************************************Queue*************************************"<<std::endl;
		for (int i = 0; i < m_n; i++)
		{
			int m = (m_first + i) % m_cap;
			std::cout << m_arDyn[m] << "     ";
		}
		std::cout << std::endl;
		std::cout << "*******************************************************************************" << std::endl;
	};
	int getCount() {
		return m_n;
	};

	MyQueue(const MyQueue& other): m_cap(other.cap), m_n(other.m_n), m_first(0), last(other.m_n) {
		m_arDyn = nullptr;
		if (other.m_n > 0)
		{
			m_arDyn = new T[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int m = (other.m_first + i) % other.m_cap;
				m_arDyn[i] = other.arDyn[m];
			}
		}
	};
	MyQueue(MyQueue&& other) {
		if (other.m_n > 0)
		{
			m_first = other.m_first;
			m_n = other.m_n;
			m_cap = other.m_n;
			m_last = other.m_last;
			m_arDyn = other.m_arDyn;
			other.m_arDyn = nullptr;
		}
		return *this;
	};
	MyQueue& operator=(const MyQueue& other) {
		if (this != &other)
		{
			if (m_n < other.m_n)
			{
				delete[] m_arDyn;
				m_cap = other.m_n;
				m_adDyn = new T[m_cap];
			}
			m_n = other.m_n;
			for (int i = 0; i < m_n; i++)
			{
				int m = (other.m_first + i) % other.m_cap;
				m_arDyn[i] = other.m_arDyn[m];
			}
		}
		return *this;
	};
	MyQueue& operator=(MyQueue&& other) {
		if (other.m_n > 0)
		{
			m_first = other.m_first;
			m_n = other.m_n;
			m_cap = other.m_n;
			m_last = other.m_last;
			m_arDyn = other.m_arDyn;
			other.m_arDyn = nullptr;
		}
		return *this;
	};
	
	T& operator[](int index) {
		if (index<m_n&&index>=0) {
			int m = (m_first + index) % m_cap;
			return m_arDyn[m];
		}
		else {
			throw "Error! Out of limits of arroy!";
		}
	}
};