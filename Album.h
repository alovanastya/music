#pragma once
#include "MyVector.h"
#include "MyVector.cpp"
#include <string>

struct Album
{
	int m_id = 0;
	MyVector <int> m_authors;
	std::string m_name;

	friend std::ostream& operator << (std::ostream&, const Album&);

	friend std::istream& operator >> (std::istream&, Album&);

	bool operator > (const Album&) const;
};

std::ostream& operator << (std::ostream&, const Album&);

std::istream& operator >> (std::istream&, Album&);