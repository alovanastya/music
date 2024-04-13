#include "Menu.h"
#include <iostream>


Menu::Menu(DataBase* database, int user_id) : IMenu(database, user_id)
{}

void Menu::printMenu() const
{
	std::cout << " 0 - Выход                        " << std::endl;
	std::cout << " 1 - Добавить любимую песню       " << std::endl;
	std::cout << " 2 - Удалить любимую песню        " << std::endl;
	std::cout << " 3 - Напечатать любимые песни     " << std::endl;
	std::cout << " 4 - Добавить любимого автора     " << std::endl;
	std::cout << " 5 - Удалить любимого автора      " << std::endl;
	std::cout << " 6 - Напечатать любимых авторов   " << std::endl;
	std::cout << " 7 - Добавить любимый альбом      " << std::endl;
	std::cout << " 8 - Удалить любимый альбом       " << std::endl;
	std::cout << " 9 - Напечатать любимые альбомы   " << std::endl;
	std::cout << " 10 - Напечатать все песни        " << std::endl;
	std::cout << " 11 - Сортировать песни           " << std::endl;

}


Result Menu::runSelected(int selected)
{
	if (selected == 0)
	{
		return Result::EXIT;
	}

	else if (selected > 0 && selected <= 11)
	{
		switch (selected)
		{
		case 1:
			addFavoriteSong();
			return Result::DONE;
			break;
		case 2:
			deleteFavoriteSong();
			return Result::DONE;
			break;
		case 3:
			printFavoriteSongs();
			return Result::DONE;
			break;
		case 4:
			addFavoriteAuthor();
			return Result::DONE;
			break;
		case 5:
			deleteFavoriteAuthor();
			return Result::DONE;
			break;
		case 6:
			printFavoriteAuthors();
			return Result::DONE;
			break;
		case 7:
			addFavoriteAlbum();
			return Result::DONE;
			break;
		case 8:
			deleteFavoriteAlbum();
			return Result::DONE;
			break;
		case 9:
			printFavoriteAlbums();
			return Result::DONE;
			break;
		case 10:
			printSongs();
			return Result::DONE;
			break;
		case 11:
			sortSongsByName();
			return Result::DONE;
			break;
		default:
			break;
		}

		system("pause");
	}

	else if (selected > 11)
	{
		return Result::NOT_SUPPORTED;
	}

	return Result::WITH_ERROR;
}

void Menu::inputInt(int& result)
{
	while (true) {

		std::cin >> result;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Введите корректное число: ";
		}

		else {
			return;
		}
	}
}


bool Menu::addFavoriteSong()
{
	std::cout << "Введите id песни: ";

	int id;
	inputInt(id);

	m_database->addFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::addFavoriteAuthor()
{
	std::cout << "Введите id автора: ";

	int id;
	inputInt(id);

	m_database->addFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::addFavoriteAlbum()
{
	std::cout << "Введите id альбома: ";

	int id;
	inputInt(id);

	m_database->addFavoriteAlbum(m_user_id, id);

	return true;
}

bool Menu::printFavoriteSongs()
{
	const MyVector<int>* tmp_vec;
	const Song* tmp_song;

	if (!m_database->getFavoriteSongs(m_user_id, tmp_vec))
	{
		return false;
	}

	for (int i = 0; i < tmp_vec->size(); ++i)
	{
		m_database->getSong(tmp_vec->operator[](i), tmp_song);
		std::cout << (*tmp_song);
	}

	return true;
}


bool Menu::printFavoriteAuthors()
{
	const MyVector<int>* tmp_vec;

	if (!m_database->getFavoriteAuthors(m_user_id, tmp_vec))
	{
		return false;
	}

	const Author* tmp_author;

	for (int i = 0; i < tmp_vec->size(); ++i)
	{
		m_database->getAuthor(tmp_vec->operator[](i), tmp_author);
		std::cout << (*tmp_author);
	}
	return true;
}

bool Menu::printFavoriteAlbums()
{
	const MyVector<int>* tmp_vec;

	if (!m_database->getFavoriteAlbums(m_user_id, tmp_vec))
	{
		return false;
	}

	const Album* tmp_album;
	for (int i = 0; i < tmp_vec->size(); ++i)
	{
		m_database->getAlbum(tmp_vec->operator[](i), tmp_album);
		std::cout << (*tmp_album);
	}
	return true;
}

bool Menu::deleteFavoriteSong()
{
	std::cout << "Введите id песни: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAuthor()
{
	std::cout << "Введите id автора: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAlbum()
{
	std::cout << "Введите id альбома: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteAlbum(m_user_id, id);

	return true;
}

void Menu::printSongs()
{
	const MyVector<Song>& tmp_vector = m_database->getSongs();

	for (int i = 0; i < tmp_vector.size(); ++i)
	{
		std::cout << tmp_vector[i] << "\n";
	}
}

void Menu::sortSongsByName()
{
	// TODO:
	// доабавить в database метод
	// MyVector<int> sortSongsByName();
	// который будет возвращать id песен, отсортированных по имени
	// а тут просто шагать по этому вектору и печатать песни на экран
}

Menu::~Menu()
{}