#include "Album.h"


bool Album::operator > (const Album& album) const
{
	if (m_name > album.m_name)
	{
		return true;
	}

	return false;
}

std::ostream& operator << (std::ostream& p_out, const Album& album)
{
	p_out << "»м€: " << album.m_name << std::endl;

	p_out << "јвторы: ";

	int authors_size = album.m_authors.size();

	for (int i = 0; i < authors_size; ++i)
	{
		p_out << album.m_authors[i] << " ";
	}

	p_out << std::endl;

	p_out << "Id: " << album.m_id << std::endl;

	return p_out;
}

std::istream& operator >> (std::istream& p_in, Album& album)
{
	album.m_authors.clear();

	std::cout << "¬ведите им€: ";
	std::getline(p_in, album.m_name);

	std::cout << "¬ведите авторов. ¬ведите -1, чтобы закончить: ";

	int author = 0;
	while (author != -1)
	{
		p_in >> author;
		p_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (author == -1)
		{
			continue;
		}

		album.m_authors.push_back(author);
	}

	return p_in;
}