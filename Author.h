#pragma once
#include <string>
#include <iostream>

struct Author
{
	Author();

	Author(int, const std::string&);

	int m_id = 0;
	std::string m_name;

	friend std::ostream& operator << (std::ostream&, const Author&);
};

std::ostream& operator << (std::ostream&, const Author&);