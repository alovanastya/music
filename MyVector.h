#pragma once
#include <iostream>

template <class T>
class MyVector
{
private:
	T* m_data = nullptr;
	int m_capacity = 0;		// ������� �������� ������
	int m_size = 0;			// ������� ��������

public:
	void pushBack(T);			// ����� ����� �� �������� ��������

	void deleteElement(int);	// ����� ����� �� database

	T operator[](int) const;

	int size() const;

	~MyVector();

	friend std::ostream& operator << (std::ostream& p_out, const MyVector&);
};

template <class T>
std::ostream& operator << (std::ostream& p_out, const MyVector<T>& vector);