#include "Song.h"

std::ostream& operator << (std::ostream& p_out, const Song& song)
{
	std::cout << "ID: " << song.m_id << std::endl;
	std::cout << "Name: " << song.m_name << std::endl;
	std::cout << "Album: " << song.m_album << std::endl;
	std::cout << "Genre : " << GENRES_NAMES[(int)song.m_genre] << std::endl;

	return p_out;
}