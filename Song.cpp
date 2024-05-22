#include "Song.h"

std::ostream& operator << (std::ostream& p_out, const Song& song)
{
	p_out << "ID: " << song.m_id << std::endl;
	p_out << "Имя: " << song.m_name << std::endl;
	p_out << "Альбом: " << song.m_album << std::endl;
	p_out << "Жанр: " << GENRES_NAMES[(int)song.m_genre] << std::endl;

	return p_out;
}

int inputInt()
{
	int result;
	std::string tmp_str;
	bool error = true;

	while (error)
	{

		error = false;
		try
		{
			std::cin >> tmp_str;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			result = stoi(tmp_str);
		}

		catch (...)
		{
			error = true;
			std::cout << "Вы ввели некорректное число. Попробуйте еще раз: ";
		}
	}

	return result;
}

std::istream& operator >> (std::istream& p_in, Song& song)
{
	std::cout << "Введите имя: ";
	std::getline(p_in, song.m_name);

	std::cout << "Введите ID альбома: ";
	p_in >> song.m_album;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Доступные жанры:" << std::endl;
	for (int i = 0; i < GENRES_NAMES.size(); ++i)
	{
		std::cout << i << " " << GENRES_NAMES[i] << std::endl;
	}

	std::cout << std::endl << "Введите жанр: ";

	int genre;
	bool genre_ok = false;
	while (!genre_ok)
	{
		p_in >> genre;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		genre_ok = genre >= 0 && genre < GENRES_NAMES.size();
		if (!genre_ok)
		{
			std::cout << "Вы ввели несуществующий жанр. Попробуйте еще раз" << std::endl;
		}
	}

	switch (genre)
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
		throw std::exception("Вы ввели несуществующий жанр");
		break;
	}

	return p_in;
}

bool Song::operator == (const Song& song) const
{
	return m_name == song.m_name && m_album == song.m_album;
}

bool Song::operator>(const Song& s) const
{
	if (m_name > s.m_name)
	{
		return true;
	}

	return false;
}
