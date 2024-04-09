#pragma once
//#include <vector>
#include "MyVector.h"
#include <string>
#include <iostream>

struct Album
{
	Album();

	Album(int, const std::string&);

	int m_id;
	MyVector <int> m_authors;
	std::string m_name;

	friend std::ostream& operator << (std::ostream& p_out, const Album& album);
};

std::ostream& operator << (std::ostream& p_out, const Album& album);