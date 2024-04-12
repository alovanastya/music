#include "Song.h"

std::ostream& operator << (std::ostream& p_out, const Song& song)
{
	std::cout << "ID: " << song.m_id << std::endl;
	std::cout << "Name: " << song.m_name << std::endl;
	std::cout << "Album: " << song.m_album << std::endl;
	std::cout << "Genre : " << GENRES_NAMES[(int)song.m_genre] << std::endl;

	return p_out;
}


std::istream& operator >> (std::istream& cin, Song& song)
{
	std::string name;
	cin >> name;
	song.m_name = name;

	int album;
	cin >> album;
	song.m_album = album;

	int genre_1;
	cin >> genre_1;


	switch (genre_1)
	{
	case 0:
		song.m_genre = Genre::ROCK;
		break;
	case 1:
		song.m_genre = Genre::JAZZ;
		break;
	case 2:
		song.m_genre = Genre::POP;
		break;
	case 3:
		song.m_genre = Genre::CLASSICAL;
		break;
	case 4:
		song.m_genre = Genre::ELECTRONIC;
		break;
	default:
		break;
	}

	return cin;
}


bool Song::operator>(const Song& s) const
{
	if (m_name > s.m_name)
	{
		return true;
	}

	return false;
}


