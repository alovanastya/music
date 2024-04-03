#include "Menu.h"

Menu::Menu() {}

Menu::Menu(DataBase* database, int user_id) : IMenu(database, user_id)
{}

Selection Menu::showMenu()
{
	std::cout << (int)Selection::ADD_FAVORITE_SONG << " - �������� ������� �����" << std::endl;
	std::cout << (int)Selection::DELETE_FAVORITE_SONG << " - ������� ������� �����" << std::endl;
	std::cout << (int)Selection::PRINT_FAVORITE_SONG << " - ���������� ������� �����" << std::endl;

	std::cout << (int)Selection::ADD_FAVORITE_AUTHOR << " - �������� �������� ������" << std::endl;
	std::cout << (int)Selection::DELETE_FAVORITE_AUTHOR << " - ������� �������� ������" << std::endl;
	std::cout << (int)Selection::PRINT_FAVORITE_AUTHOR << " - ���������� ����� �������" << std::endl;

	std::cout << (int)Selection::ADD_FAVORITE_ALBUM << " - �������� ������� ������" << std::endl;
	std::cout << (int)Selection::DELETE_FAVORITE_ALBUM << " - ������� ������� ������" << std::endl;
	std::cout << (int)Selection::PRINT_FAVORITE_ALBUM << " - ���������� ������ �������" << std::endl;

	std::cout << (int)Selection::EXIT << " - �����" << std::endl;

	int selection = 0;
	std::cin >> selection;
	std::cin.ignore();

	return (Selection)selection;
}


bool Menu::addFavoriteSong()
{
	std::cout << "������� id �����: ";

	int id;
	std::cin >> id;

	m_database->addFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::addFavoriteAuthor()
{
	std::cout << "������� id ������: ";

	int id;
	std::cin >> id;

	m_database->addFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::addFavoriteAlbum()
{
	std::cout << "������� id �������: ";

	int id;
	std::cin >> id;

	m_database->addFavoriteAlbum(m_user_id, id);

	return true;
}

bool Menu::printFavoriteSongs()
{
	const std::vector<int>* tmp_vec;
	m_database->getFavoriteSongs(m_user_id, tmp_vec);

	const Song* tmp_song;
	for (int item : *tmp_vec)
	{
		m_database->getSong(item, tmp_song);
		std::cout << (*tmp_song);
	}

	return true;
}

bool Menu::printFavoriteAuthors()
{
	const std::vector<int>* tmp_vec;
	m_database->getFavoriteAuthors(m_user_id, tmp_vec);

	const Author* tmp_author;
	for (int item : *tmp_vec)
	{
		m_database->getAuthor(item, tmp_author);
		std::cout << (*tmp_author);
	}

	return true;
}

bool Menu::printFavoriteAlbums()
{
	const std::vector<int>* tmp_vec;
	m_database->getFavoriteSongs(m_user_id, tmp_vec);

	const Album* tmp_album;
	for (int item : *tmp_vec)
	{
		m_database->getAlbum(item, tmp_album);
		std::cout << (*tmp_album);
	}

	return true;
}

bool Menu::deleteFavoriteSong()
{
	std::cout << "������� id �����: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAuthor()
{
	std::cout << "������� id ������: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAlbum()
{
	std::cout << "������� id �������: ";

	int id;
	std::cin >> id;

	m_database->deleteFavoriteAlbum(m_user_id, id);

	return true;
}

bool Menu::show()
{
	Selection selection = showMenu();

	if (selection == Selection::EXIT)
	{
		return true;
	}

	bool ok = true;
	switch (selection)
	{
	case Selection::ADD_FAVORITE_SONG:
		ok = addFavoriteSong();
		break;
	case Selection::DELETE_FAVORITE_SONG:
		ok = deleteFavoriteSong();
		break;
	case Selection::PRINT_FAVORITE_SONG:
		ok = printFavoriteSongs();
		break;
	case Selection::ADD_FAVORITE_AUTHOR:
		ok = addFavoriteAuthor();
		break;
	case Selection::DELETE_FAVORITE_AUTHOR:
		ok = deleteFavoriteAuthor();
		break;
	case Selection::PRINT_FAVORITE_AUTHOR:
		ok = printFavoriteAuthors();
		break;
	case Selection::ADD_FAVORITE_ALBUM:
		ok = addFavoriteAlbum();
		break;
	case Selection::DELETE_FAVORITE_ALBUM:
		ok = deleteFavoriteAlbum();
		break;
	case Selection::PRINT_FAVORITE_ALBUM:
		ok = printFavoriteAlbums();
		break;
	case Selection::EXIT:
		return true;
		break;
	default:
		std::cout << "������";
		break;
	}

	// TODO
	// �������� �����, ������, ������ (��� ��������)
	// ��� ������������ �������� �����, ������, ������ (��� ��������) 
	// ��� ������������ ������� �����, ������, ������ (��� ��������)
	// ��� ������������ ������ ������� �����, ��������, ������� (��� ��������)

	return false;
}