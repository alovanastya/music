#include "AdminMenu.h"

AdminMenu::AdminMenu()
{

}

AdminMenu::AdminMenu(DataBase* database, int user_id)
{

}

Selection AdminMenu::showMenu()
{
	IMenu::showMenu();

	std::cout << (int)Selection::ADD_AUTHOR << " - �������� �����������" << std::endl;
	std::cout << (int)Selection::ADD_ALBUM  << " - �������� ������" << std::endl;
	std::cout << (int)Selection::ADD_SONG   << " - �������� �����" << std::endl;

	int selection;
	std::cin >> selection;
	std::cin.ignore();

	return (Selection)selection;
}

bool AdminMenu::addSong()
{
	Song new_song;

	std::cout << "������� �������� �����: ";

	std::getline(std::cin, new_song.m_name);

	std::cout << "������� id �������: ";

	bool flag_1 = false;

	while (flag_1 == false)
	{
		std::cin >> new_song.m_album;

		const std::vector<Album>& albums = m_database->getAlbums();
		for (int i = 0; i < albums.size(); ++i)
		{
			if (albums[i].m_id == new_song.m_album)
			{
				flag_1 = true;
			}
		}

		if (flag_1 == false)
		{
			std::cout << "������� � ����� id �� ����������. ������ �������? ";
			std::cout << "1. ��\n";
			std::cout << "2. ���\n";

			int choice;

			std::cin >> choice;

			switch (choice)
			{
			case 1:
				addAlbum();
				break;

			case 2:
				std::cout << "����� ���������� ������ id �����\n";
				flag_1 = false;
				break;

			default:
				break;
			}
		}
	}

	std::cout << "\n�������� ����: \n";

	int selection;

	std::cout << "1. ��� \n";
	std::cout << "2. ���� \n";
	std::cout << "3. ��� \n";
	std::cout << "4. ������������ \n";
	std::cout << "5. ����������� \n";

	std::cin >> selection;

	bool flag = false;

	while (flag == false)
	{
		switch (selection)
		{
		case 1:
			new_song.m_genre = Genre::ROCK;
			flag = true;
			break;
		case 2:
			new_song.m_genre = Genre::JAZZ;
			flag = true;
			break;
		case 3:
			new_song.m_genre = Genre::POP;
			flag = true;
			break;
		case 4:
			new_song.m_genre = Genre::CLASSICAL;
			flag = true;
			break;
		case 5:
			new_song.m_genre = Genre::ELECTRONIC;
			flag = true;
			break;
		default:
			std::cout << "������ ����� ���";
			flag = false;
			break;
		}
	}

	m_database->addSong(new_song);

	return true;
}

bool AdminMenu::addAlbum()
{
	Album new_album;

	std::cout << "\n������� �������� �������: ";
	getline(std::cin, new_album.m_name);

	bool flag_3 = false;

	while (flag_3 == false)
	{
		std::cout << "\n������� id ������ ��� ������� �������: ";

		int authors_id;

		std::cin >> authors_id;
		for (int i = 0; i < m_database->m_authors.size(); ++i)
		{
			if (m_database->m_authors[i].m_id == authors_id)
			{
				new_album.m_authors.push_back(authors_id);
				flag_3 = true;
			}
		}

		if (flag_3 == false)
		{
			std::cout << "������ � ����� id ���.\n������ �������� ������ ������?\n\n";

			std::cout << "1. ��\n";
			std::cout << "2. ���\n";

			int choice;

			std::cin >> choice;

			switch (choice)
			{
			case 1:
				addAuthor();
				break;

			case 2:
				std::cout << "����� ���������� ������ id �����.\n";
				flag_3 = false;
				break;

			default:
				break;
			}
		}
	}

	bool flag = false;

	m_database->m_albums.push_back(new_album);

	return true;
}

bool AdminMenu::addAuthor()
{
	Author new_author;

	getline(std::cin, new_author.m_name);

	m_database->m_authors.push_back(new_author);

	return true;
}

bool AdminMenu::show()
{
	Selection selection = showMenu();

	switch (selection)
	{
	case Selection::ADD_ALBUM:
		addAlbum();
		break;
	case Selection::ADD_AUTHOR:
		addAuthor();
		break;
	case Selection::ADD_SONG:
		addSong();
		break;
	default:
		break;
	}

	return true;
}