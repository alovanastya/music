#include "MyVector.h"


template <class T> MyVector<T>::MyVector()
{
	vector = new T[10];
	m_capacity = 10;
}

template <class T> void MyVector<T>::push_back(T data)
{
	if (m_capacity > m_size)
	{
		vector[m_size] = data;
		m_size++;
	}

	else if (m_capacity <= m_size)
	{
		T* vector_2 = new T[m_capacity * 2];

		for (int i = 0; i < m_capacity; ++i)
		{
			vector_2[i] = vector[i];
		}

		delete[] vector;

		vector = new T[m_capacity * 2];

		for (int i = 0; i < m_capacity; ++i)
		{
			vector[i] = vector_2[i];
		}

		delete[] vector_2;

		m_capacity *= 2;
		vector[m_size] = data;
		m_size++;
	}
}

template<class T> T MyVector<T>::front() const
{
	return vector[0];
}

template<class T> T MyVector<T>::back() const
{
	return vector[m_size - 1];
}

template<class T> void MyVector<T>::clear()
{
	vector = new T[m_capacity];
	m_size = 0;
}



template <class T> void MyVector<T>::deleteElement(int number)
{
	if (m_size != 0)
	{
		T* vector_2 = new T[m_capacity];
		int j = 0;

		for (int i = 0; i < number; i++)
		{
			vector_2[j] = vector[i];
			j += 1;
		}

		for (int i = (number + 1); i < m_size; i++)
		{
			vector_2[j] = vector[i];
			j += 1;
		}

		delete[] vector;

		vector = new T[m_capacity];

		for (int i = 0; i < m_capacity; ++i)
		{
			vector[i] = vector_2[i];
		}

		delete[] vector_2;
		m_size--;

	}
}

template <class T> T MyVector<T>::operator[](int number) const
{
	return vector[number];
}

template<class T> void MyVector<T>::operator()(int data)
{
	vector[m_size] = { data };
	m_size++;
}

template<class T> int MyVector<T>::size() const
{
	return m_size;
}

template<class T> int MyVector<T>::capacity() const
{
	return m_capacity;
}

template<class T> MyVector<T>::~MyVector()
{
	delete[] vector;
}

template <class T> std::ostream& operator << (std::ostream& cout, const MyVector<T>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << '\n';
	return cout;
}