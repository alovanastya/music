#pragma once
#include <string>
#include <iostream>

struct Author
{
	Author();

	Author(int, const std::string&);

	int m_id;
	std::string m_name;

	friend std::ostream& operator << (std::ostream& p_out, const Author& author);
};

std::ostream& operator << (std::ostream& p_out, const Author& author);