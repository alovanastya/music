#pragma once
#include <iostream>

template <class T>
class MyVector;

template<typename ValueType>
class Iterator
{
public:
	Iterator(const Iterator& it);

	bool operator!=(Iterator const& other) const;

	bool operator==(Iterator const& other) const;

	const ValueType &operator*() const;

	Iterator& operator++();

private:
	Iterator(ValueType* data);

	ValueType* m_data;

	friend class MyVector<ValueType>;
};

template <class T>
class MyVector
{
private:
	T* m_vector = nullptr;
	int m_capacity = 0;
	int m_size = 0;

public:
	Iterator<T> begin() const;

	Iterator<T> end() const;

	MyVector();

	MyVector(T, int);

	MyVector(const MyVector&);

	void push_back(const T&);

	T& front();

	T& back();

	const T& back() const;

	void clear();

	void deleteElement(int);

	T& operator[](int);

	const T& operator[](int) const;

	bool operator == (const MyVector<T>) const;

	MyVector operator = (const MyVector<T>&);

	int size() const;

	~MyVector();

	friend std::ostream& operator << (std::ostream& p_out, const MyVector&);
};

template <class T>
std::ostream& operator << (std::ostream& p_out, const MyVector<T>& vector);
