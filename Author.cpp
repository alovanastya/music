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

bool Author::operator > (const Author& author) const
{
	if (m_name > author.m_name)
	{
		return true;
	}

	return false;
}