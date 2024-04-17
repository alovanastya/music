#pragma once
#include <iostream>

template <class T>
class MyVector
{
private:
	T* m_vector = nullptr;
	int m_capacity = 0;
	int m_size = 0;


public:
	MyVector();

	MyVector(T value, int size);

	void push_back(T);

	T& front();

	T& back();

	void clear();

	void deleteElement(int);

	T& operator[](int);

	const T& operator[](int) const;

	bool operator == (const MyVector<T>) const;

	int size() const;

	~MyVector();

	friend std::ostream& operator << (std::ostream& p_out, const MyVector&);
};

template <class T>
std::ostream& operator << (std::ostream& p_out, const MyVector<T>& vector);
