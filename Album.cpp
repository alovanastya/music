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

	int authors_size = album.m_authors.size();

	for (int i = 0; i < authors_size; ++i)
	{
		std::cout << album.m_authors[i] << " ";
	}
	 
	std::cout << std::endl;

	std::cout << "Id: " << album.m_id << std::endl;

	return p_out;
}

bool Album::operator > (const Album& album) const 
{
	if (m_name > album.m_name)
	{
		return true;
	}

	return false;
}