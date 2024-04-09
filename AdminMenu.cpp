#include "AdminMenu.h"

AdminMenu::AdminMenu(DataBase* database, int user_id) : Menu(database, user_id)
{

}

void AdminMenu::printMenu() const
{
	Menu::printMenu();

	std::cout << " 10 - Добавить песню  " << std::endl;
	std::cout << " 11 - Добавить автора " << std::endl;
	std::cout << " 12 - Добавить альбом " << std::endl;
}

Result AdminMenu::runSelected(int selected)
{
	Result result = Menu::runSelected(selected);

	if (result != Result::NOT_SUPPORTED)
	{
		return result;
	}

	if (selected <= 12)
	{
		bool ok = true;
		switch (selected)
		{
		case 10:
			ok = AdminMenu::addSong();
			break;
		case 11:
			ok = AdminMenu::addAuthor();
			break;
		case 12:
			ok = AdminMenu::addAlbum();
			break;
		default:
			return Result::WITH_ERROR;
			break;
		}

		if (ok)
		{
			return Result::DONE;
		}

		return Result::WITH_ERROR;
	}

	return Result::NOT_SUPPORTED;
}


bool AdminMenu::addSong()
{
	Song new_song;

	std::cout << "Введите название песни: ";

	std::getline(std::cin, new_song.m_name);

	bool flag_1 = false;

	while (flag_1 == false)
	{
		std::cin >> new_song.m_album;

		const MyVector<Album>& albums = m_database->getAlbums();

		for (int i = 0; i < albums.size(); ++i)
		{
			if (albums[i].m_id == new_song.m_album)
			{
				flag_1 = true;
			}
		}

		if (flag_1 == false)
		{
			std::cout << "Альбома с таким id не существует. Хотите создать? ";
			std::cout << "1. Да\n";
			std::cout << "2. Нет\n";

			int choice;

			std::cin >> choice;

			switch (choice)
			{
			case 1:
				addAlbum();
				break;

			case 2:
				std::cout << "Тогда попробуйте ввести id снова\n";
				flag_1 = false;
				break;

			default:
				break;
			}
		}
	}

	std::cout << "\nВыберите жанр: \n";

	int selection;

	std::cout << "1. Рок \n";
	std::cout << "2. Джаз \n";
	std::cout << "3. Поп \n";
	std::cout << "4. Классическая \n";
	std::cout << "5. Электронная \n";

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
			std::cout << "Такого жанра нет";
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

	std::cout << "\nВведите название альбома: ";
	getline(std::cin, new_album.m_name);

	bool flag_3 = false;

	while (flag_3 == false)
	{
		std::cout << "\nВведите id автора или авторов альбома: ";

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
			std::cout << "Автора с таким id нет.\nХотите добавить нового автора?\n\n";

			std::cout << "1. Да\n";
			std::cout << "2. Нет\n";

			int choice;

			std::cin >> choice;

			switch (choice)
			{
			case 1:
				addAuthor();
				break;

			case 2:
				std::cout << "Тогда попробуйте ввести id снова.\n";
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

AdminMenu::~AdminMenu()
{}