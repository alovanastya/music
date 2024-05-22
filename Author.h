#pragma once
#include <string>
#include <iostream>

struct Author
{
	int m_id = 0;
	std::string m_name;

	friend std::ostream& operator << (std::ostream&, const Author&);

	friend std::istream& operator >> (std::istream&, Author&);

	bool operator > (const Author&) const;
};

std::ostream& operator << (std::ostream&, const Author&);

std::istream& operator >> (std::istream&, Author&);