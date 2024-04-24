#pragma once
#include "MyVector.h"
#include "MyVector.cpp"
#include <string>

struct Album
{
	Album();

	Album(int, const std::string&);

	int m_id = 0;
	MyVector <int> m_authors;
	std::string m_name;

	friend std::ostream& operator << (std::ostream& p_out, const Album& album);

	bool operator > (const Album&) const;
};

std::ostream& operator << (std::ostream& p_out, const Album& album);