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
	//std::cout << "Авторы: " << album.m_authors << std::endl;
	std::cout << "Id: " << album.m_id << std::endl;


	return p_out;
}
