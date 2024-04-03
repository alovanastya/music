#include "Author.h"

Author::Author()
{
	
}

Author::Author(int id, const std::string& name)
{
	m_id = id;
	m_name = name;
}


std::ostream& operator << (std::ostream& p_out, const Author& author)
{
	std::cout << "Èìÿ: " << author.m_name << std::endl;
	std::cout << "Id: " << author.m_id << std::endl;

	return p_out;
}