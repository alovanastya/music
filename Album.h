#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Album
{
	Album();

	Album(int, const std::string&);

	int m_id;
	std::vector<int> m_authors;
	std::string m_name;

	friend std::ostream& operator << (std::ostream& p_out, const Album& album);
};

std::ostream& operator << (std::ostream& p_out, const Album& album);