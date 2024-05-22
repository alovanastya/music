#include "Author.h"

bool Author::operator > (const Author& author) const
{
	if (m_name > author.m_name)
	{
		return true;
	}

	return false;
}

std::ostream& operator << (std::ostream& p_out, const Author& author)
{
	p_out << "Имя: " << author.m_name << std::endl;
	p_out << "Id: " << author.m_id << std::endl;

	return p_out;
}

std::istream& operator >> (std::istream& p_in, Author& author)
{
	std::cout << "Введите имя: ";
	std::getline(p_in, author.m_name);

	return p_in;
}