#include "MyVector.h"

template <class T>
MyVector<T>::MyVector()
{}

template <class T>
MyVector<T>::MyVector(T value, int size)
{
	T* m_vector = new T[size];
	int m_capacity = size;
	int m_size = size;

	for (int i = 0; i < size; ++i)
	{
		m_vector[i] = value;
	}
}

template <class T>
void MyVector<T>::push_back(T data)
{
	if (m_capacity == 0)
	{
		m_vector = new T;
		*m_vector = data;

		m_capacity = 1;
		m_size = 1;
	}

	else if (m_capacity > m_size)
	{
		m_vector[m_size] = data;
		m_size++;
	}

	else
	{
		T* vector_2 = new T[m_capacity * 2];

		for (int i = 0; i < m_capacity; ++i)
		{
			vector_2[i] = m_vector[i];
		}

		//delete[] m_vector;

		m_vector = vector_2;

		m_capacity *= 2;
		m_vector[m_size] = data;
		m_size++;
	}
}

template<class T>
T& MyVector<T>::front()
{
	return m_vector[0];
}

template<class T>
T& MyVector<T>::back()
{
	return m_vector[m_size - 1];
}

template<class T>
void MyVector<T>::clear()
{
	m_size = 0;
}

template <class T>
void MyVector<T>::deleteElement(int number)
{
	if (number > m_size - 1 || number < 0)
	{
		return;
	}

	if (number != m_size - 1)
	{
		for (int i = number; i < m_size - 1; ++i)
		{
			m_vector[i] = m_vector[i + 1];
		}
	}

	m_size--;
}

template <class T>
T& MyVector<T>::operator[](int number)
{
	return m_vector[number];
}

template <class T>
const T& MyVector<T>::operator[](int number) const
{
	return m_vector[number];
}

template<class T>
int MyVector<T>::size() const
{
	return m_size;
}

template<class T>
MyVector<T>::~MyVector()
{
	delete[] m_vector; //
}

template <class T>
std::ostream& operator << (std::ostream& cout, const MyVector<T>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << '\n';
	return cout;
}