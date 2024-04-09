#pragma once
#include <iostream>

template <class T>
class MyVector
{
private:
	T* vector = nullptr;
	int m_capacity = 0;		// сколько выделено памяти
	int m_size = 0;			// сколько хранится


public:

	MyVector();

	void push_back(T);	

	T front() const;

	T back() const;

	void clear();

	void deleteElement(int);	

	T operator[](int) const;

	void operator()(int);

	int size() const;

	int capacity() const;

	~MyVector();

	friend std::ostream& operator << (std::ostream& p_out, const MyVector&);
};

template <class T>
std::ostream& operator << (std::ostream& p_out, const MyVector<T>& vector);
