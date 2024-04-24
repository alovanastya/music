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
	std::cout << " 11 - Сортировать песни по имени  " << std::endl;
	std::cout << " 12 - Сортировать альбомы по имени " << std::endl;
	std::cout << " 13 - Сортировать авторов по имени " << std::endl;

}

Result Menu::runSelected(int selected)
{
	if (selected == 0)
	{
		return Result::EXIT;
	}

	else if (selected > 0 && selected <= 13)
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
		case 12:
			sortAlbumsByName();
			return Result::DONE;
			break;
		case 13:
			sortAuthorsByName();
			return Result::DONE;
			break;
		default:
			break;
		}

		system("pause");
	}

	else if (selected > 13)
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
	const MyVector <Song> &songs = m_database->getSongs();
	int size = songs.size();
	
	if (size == 0)
	{
		std::cout << "Песен нет.";
		return false;
	}

	bool correct_id = false;
	int id;

	while (correct_id == false)
	{
		std::cout << "Введите id песни: ";
		inputInt(id);

		for (int i = 0; i < size; ++i)
		{
			if (songs[i].m_id == id)
			{
				m_database->addFavoriteSong(m_user_id, id);
				correct_id = true;
			}
		}

		if (correct_id == false)
		{
			std::cout << "Песня с таким id отсутствует." << std::endl;
		}
	}
	
	return true;
}

bool Menu::addFavoriteAuthor()
{

	std::cout << "Введите id автора: ";
	const MyVector <Author>& authors = m_database->getAuthors();
	int size = authors.size();
	
	if (size == 0)
	{
		std::cout << "Список авторов пуст.";
		return false;
	}
	bool flag = false;
	int id;

	while (flag == false)
	{
		std::cout << "Введите id:";
		inputInt(id);

		for (int i = 0; i < size; ++i)
		{
			if (authors[i].m_id == id)
			{
				m_database->addFavoriteAuthor(m_user_id, id);
				flag = true;
			}
		}

		if (flag == false)
		{
			std::cout << "Автор с таким id отсутствует." << std::endl;
		}
	}

	return true;
}

bool Menu::addFavoriteAlbum()
{
	std::cout << "Введите id альбома: ";
	const MyVector <Album>& albums = m_database->getAlbums();
	int size = albums.size();

	if (size == 0)
	{
		std::cout << "Список альбомов пуст.";
		return false;
	}

	bool flag = false;
	int id;

	while (flag == false)
	{
		std::cout << "Введите id:";
		inputInt(id);

		for (int i = 0; i < size; ++i)
		{
			if (albums[i].m_id == id)
			{
				m_database->addFavoriteAlbum(m_user_id, id);
				flag = true;
			}
		}

		if (flag == false)
		{
			std::cout << "Автор с таким id отсутствует." << std::endl;
		}
	}

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
	inputInt(id);

	m_database->deleteFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAuthor()
{
	std::cout << "Введите id автора: ";

	int id;
	inputInt(id);

	m_database->deleteFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAlbum()
{
	std::cout << "Введите id альбома: ";

	int id;
	inputInt(id);

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

	system("pause");
}

void Menu::sortSongsByName()
{
	int size = m_database->getSongs().size();

	if (size != 0)
	{
		MyVector<int> id = m_database->sortSongsByName();

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (m_database->getSongs()[j].m_id == id[i])
				{
					std::cout << m_database->getSongs()[j] << std::endl;
				}
			}
		}
	}

	else
	{
		std::cout << "Список песен пуст." << '\n';
	}

	system("pause");
}

void Menu::sortAlbumsByName()
{
	int size = m_database->getAlbums().size();

	if (size != 0)
	{
		MyVector<int> id = m_database->sortAlbumsByName();

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (m_database->getAlbums()[j].m_id == id[i])
				{
					std::cout << m_database->getAlbums()[j] << std::endl;
				}
			}
		}
	}

	else
	{
		std::cout << "Список альбомов пуст." << '\n';
	}

	system("pause");
}

void Menu::sortAuthorsByName()
{
	int size = m_database->getAuthors().size();

	if (size != 0)
	{
		MyVector<int> id = m_database->sortAuthorsByName();

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (m_database->getAuthors()[j].m_id == id[i])
				{
					std::cout << m_database->getAuthors()[j] << std::endl;
				}
			}
		}
	}

	else
	{
		std::cout << "Список авторов пуст." << '\n';
	}

	system("pause");
}

Menu::~Menu()
{}