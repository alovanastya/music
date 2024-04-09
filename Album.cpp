#include "Album.h"

Album::Album()
{

}

Album::Album(int id, const std::string& name)
{
	m_id = id;
	m_name = name;
}

std::ostream& operator << (std::ostream& p_out, const Album& album)
{
	std::cout << "Имя: " << album.m_name << std::endl;

	std::cout << "Авторы: ";

	for (int i = 0; i < album.m_authors.size(); ++i)
	{
		std::cout << album.m_authors[i] << ",";
	}

	std::cout << "Id: " << album.m_id << std::endl;

	return p_out;
}
