#include "Menu.h"
#include <iostream>

Menu::Menu(DataBase* database, int user_id) : IMenu(database, user_id)
{}

void Menu::printMenu() const
{
	std::cout << "0 �����                         " << std::endl;
	std::cout << std::endl;
	std::cout << "1 �������� ������������		  " << std::endl;
	std::cout << std::endl;
	std::cout << "2 �������� ������� �����        " << std::endl;
	std::cout << "3 ������� ������� �����         " << std::endl;
	std::cout << "4 ���������� ������� �����      " << std::endl;
	std::cout << std::endl;
	std::cout << "5 �������� �������� ������      " << std::endl;
	std::cout << "6 ������� �������� ������       " << std::endl;
	std::cout << "7 ���������� ������� �������    " << std::endl;
	std::cout << std::endl;
	std::cout << "8 �������� ������� ������       " << std::endl;
	std::cout << "9 ������� ������� ������        " << std::endl;
	std::cout << "10 ���������� ������� �������    " << std::endl;
	std::cout << std::endl;
	std::cout << "11 ���������� ��� �����         " << std::endl;
	std::cout << "12 ���������� ���� �������      " << std::endl;
	std::cout << "13 ���������� ��� �������       " << std::endl;
	std::cout << std::endl;
	std::cout << "14 ����������� ����� �� �����   " << std::endl;
	std::cout << "15 ����������� ������� �� ����� " << std::endl;
	std::cout << "16 ����������� ������� �� ����� " << std::endl;
	std::cout << std::endl;
}

Result Menu::runSelected(int selected)
{
	if (selected == 0)
	{
		return Result::EXIT;
	}

	else if (selected > 0 && selected <= 16)
	{
		try
		{
			switch (selected)
			{
			case 1:
				addUser();
				break;
			case 2:
				addFavoriteSong();
				break;
			case 3:
				deleteFavoriteSong();
				break;
			case 4:
				printFavoriteSongs();
				break;
			case 5:
				addFavoriteAuthor();
				break;
			case 6:
				deleteFavoriteAuthor();
				break;
			case 7:
				printFavoriteAuthors();
				break;
			case 8:
				addFavoriteAlbum();
				break;
			case 9:
				deleteFavoriteAlbum();
				break;
			case 10:
				printFavoriteAlbums();
				break;
			case 11:
				printSongs();
				break;
			case 12:
				printAuthors();
				break;
			case 13:
				printAlbums();
				break;
			case 14:
				sortSongsByName();
				break;
			case 15:
				sortAlbumsByName();
				break;
			case 16:
				sortAuthorsByName();
				break;
			default:
				return Result::WITH_ERROR;
				break;
			}
		}
		catch (const std::exception& error)
		{
			std::cout << error.what() << std::endl;

			return Result::WITH_ERROR;
		}

		return Result::DONE;
	}

	return Result::NOT_SUPPORTED;
}

int Menu::inputInt() const
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
			std::cout << "�� ����� ������������ �����. ���������� ��� ���: ";
		}
	}

	return result;
}

void Menu::addUser()
{
	std::string login, password, password_2;

	bool success = false;

	while (!success)
	{
		std::cout << "������� �����: ";
		std::cin >> login;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();


		if (m_database->userExists(login))
		{
			std::cout << "����� ������������ ��� ����������!" << std::endl;
			continue;
		}

		std::cout << "������� ������: ";
		std::cin >> password;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();

		std::cout << "������� ������ ��� ���: ";
		std::cin >> password_2;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();

		if (password != password_2)
		{
			std::cout << "������ �� ���������!" << std::endl;
			continue;
		}

		m_database->saveUserToTxt(login, password);

		success = true;
	}

	m_database->addUser(login, password);
	std::cout << "������������ ��������" << std::endl;
}

void Menu::addFavoriteSong()
{
	std::cout << "������� id �����: ";
	const int song_id = inputInt();
	m_database->addFavoriteSong(m_user_id, song_id);
}

void Menu::addFavoriteAuthor()
{
	std::cout << "������� id ������: ";
	const int author_id = inputInt();
	m_database->addFavoriteAuthor(m_user_id, author_id);
}

void Menu::addFavoriteAlbum()
{
	std::cout << "������� id �������: ";
	const int album_id = inputInt();
	m_database->addFavoriteAuthor(m_user_id, album_id);
}

void Menu::printFavoriteSongs() const
{
	const MyVector<Song>& songs = m_database->getSongs();
	const MyVector<int>& ids = m_database->getFavoriteSongs(m_user_id);

	std::cout << "+----------------------+\n";
	std::cout << "|     ������� �����    |\n";
	std::cout << "+----------------------+\n";

	if (ids.size() == 0)
	{
		std::cout << "������ ����� ����." << std::endl;
		return;
	}

	for (int i = 0; i < ids.size(); ++i)
	{
		std::cout << songs[ids[i]] << std::endl;
	}
}

void Menu::printFavoriteAuthors() const
{
	const MyVector<Author>& authors = m_database->getAuthors();
	const MyVector<int>& ids = m_database->getFavoriteAuthors(m_user_id);

	std::cout << "+----------------------+\n";
	std::cout << "|     ������� ������   |\n";
	std::cout << "+----------------------+\n";

	if (ids.size() == 0)
	{
		std::cout << "������ ������� ����." << std::endl;
		return;
	}

	for (int i = 0; i < ids.size(); ++i)
	{
		std::cout << authors[ids[i]] << std::endl;
	}
}

void Menu::printFavoriteAlbums() const
{
	const MyVector<Album>& albums = m_database->getAlbums();
	const MyVector<int>& ids = m_database->getFavoriteAlbums(m_user_id);

	std::cout << "+----------------------+\n";
	std::cout << "|     ������� �������  |\n";
	std::cout << "+----------------------+\n";

	if (ids.size() == 0)
	{
		std::cout << "������ �������� ����." << std::endl;
		return;
	}

	for (int i = 0; i < ids.size(); ++i)
	{
		std::cout << albums[ids[i]] << std::endl;
	}
}

void Menu::deleteFavoriteSong()
{
	std::cout << "������� id �����: ";
	const int song_id = inputInt();
	m_database->deleteFavoriteSong(m_user_id, song_id);
}

void Menu::deleteFavoriteAuthor()
{
	std::cout << "������� id ������: ";
	const int author_id = inputInt();
	m_database->deleteFavoriteAuthor(m_user_id, author_id);
}

void Menu::deleteFavoriteAlbum()
{
	std::cout << "������� id �������: ";
	const int album_id = inputInt();
	m_database->deleteFavoriteAlbum(m_user_id, album_id);
}

void Menu::printSongs() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|      �����      |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Song>& tmp_vector = m_database->getSongs();

	if (tmp_vector.size() == 0)
	{
		std::cout << "������ ����� ����." << std::endl;
		return;
	}

	for (int i = 0; i < tmp_vector.size(); ++i)
	{
		std::cout << tmp_vector[i] << std::endl;
	}
}

void Menu::printAlbums() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|     �������     |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Album>& tmp_vector = m_database->getAlbums();

	if (tmp_vector.size() == 0)
	{
		std::cout << "������ �������� ����." << std::endl;
		return;
	}

	for (int i = 0; i < tmp_vector.size(); ++i)
	{
		std::cout << tmp_vector[i] << std::endl;
	}
}

void Menu::printAuthors() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|     ������      |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Author>& tmp_vector = m_database->getAuthors();

	if (tmp_vector.size() == 0)
	{
		std::cout << "������ ������� ����." << std::endl;
		return;
	}

	int size = tmp_vector.size();

	for (int i = 0; i < size; ++i)
	{
		std::cout << tmp_vector[i] << std::endl;
	}
}

void Menu::sortSongsByName() const
{
	int size = m_database->getSongs().size();

	if (size == 0)
	{
		std::cout << "������ ����� ����." << '\n';
		return;
	}

	const MyVector<Song>& songs = m_database->getSongs();
	const MyVector<int> ids = m_database->sortSongsByName();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (songs[j].m_id == ids[i])
			{
				std::cout << songs[j] << std::endl;
			}
		}
	}
}

void Menu::sortAlbumsByName() const
{
	int size = m_database->getAlbums().size();

	if (size == 0)
	{
		std::cout << "������ �������� ����." << '\n';
		return;
	}

	const MyVector<Album>& albums = m_database->getAlbums();
	const MyVector<int> ids = m_database->sortAlbumsByName();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (albums[j].m_id == ids[i])
			{
				std::cout << albums[j] << std::endl;
			}
		}
	}
}

void Menu::sortAuthorsByName() const
{
	int size = m_database->getAuthors().size();

	if (size == 0)
	{
		std::cout << "������ �������� ����." << '\n';
		return;
	}

	const MyVector<Author>& authors = m_database->getAuthors();
	const MyVector<int> ids = m_database->sortAuthorsByName();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (authors[j].m_id == ids[i])
			{
				std::cout << authors[j] << std::endl;
			}
		}
	}
}

Menu::~Menu()
{}