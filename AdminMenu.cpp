#include "AdminMenu.h"

AdminMenu::AdminMenu(DataBase* database, int user_id) : Menu(database, user_id)
{

}

void AdminMenu::printMenu() const
{
	Menu::printMenu();

	std::cout << " 12 - Добавить песню  " << std::endl;
	std::cout << " 13 - Добавить автора " << std::endl;
	std::cout << " 14 - Добавить альбом " << std::endl;
}

Result AdminMenu::runSelected(int selected)
{
	Result result = Menu::runSelected(selected);

	if (result != Result::NOT_SUPPORTED)
	{
		return result;
	}

	if (selected <= 14)
	{
		bool ok = true;
		switch (selected)
		{
		case 12:
			ok = AdminMenu::addSong();
			break;
		case 13:
			ok = AdminMenu::addAuthor();
			break;
		case 14:
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

	std::cout << "Неверная команда!" << std::endl;
	system("pause");
	return Result::NOT_SUPPORTED;
}


bool AdminMenu::addSong()
{
	Song new_song;

	std::cout << "Введите название песни: ";
	std::cin.ignore();
	std::getline(std::cin, new_song.m_name);

	bool flag_1 = false;

	while (flag_1 == false)
	{
		std::cout << "Введите id альбома, в который хотите внести песню: ";

		inputInt(new_song.m_album);

		const MyVector<Album>& albums = m_database->getAlbums();

		int size = albums.size();

		for (int i = 0; i < size; ++i)
		{
			if (albums[i].m_id == new_song.m_album)
			{
				flag_1 = true;
			}
		}

		if (flag_1 == false)
		{
			std::cout << "Альбома с таким id не существует. Хотите создать?" << std::endl;
			std::cout << "1. Да\n";
			std::cout << "2. Нет\n";

			int choice;

			inputInt(choice);

			switch (choice)
			{
			case 1:
				addAlbum();
				flag_1 = true;
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

	bool flag_2 = false;

	while (flag_2 == false)
	{
		std::cin >> selection;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Введите корректное число: ";
		}

		else
		{
			flag_2 = true;
		}
	}

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
	std::cin.ignore();
	getline(std::cin, new_album.m_name);

	bool flag_3 = false;

	while (flag_3 == false)
	{
		std::cout << "\nВведите id автора или авторов альбома: ";

		int authors_id;

		inputInt(authors_id);

		int size = m_database->m_authors.size();

		for (int i = 0; i < size; ++i)
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

			inputInt(choice);

			switch (choice)
			{
			case 1:
				addAuthor();
				flag_3 = true;
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

	//bool flag = false;

	m_database->m_albums.push_back(new_album);

	return true;
}

bool AdminMenu::addAuthor()
{
	Author new_author;

	std::cout << "Введите имя автора, которого хотите добавить: ";

	bool flag = false;

	while (flag == false)
	{
		std::cin.ignore();
		getline(std::cin, new_author.m_name);

		int size = m_database->m_authors.size();

		if (size != 0)
		{
			for (int i = 0; i < size; ++i)
			{
				if (m_database->m_authors[i].m_name == new_author.m_name)
				{
					std::cout << "Автор с таким именем уже существует." << std::endl;
					std::cout << "Введите другое имя." << std::endl;
				}
				else
				{
					m_database->m_authors.push_back(new_author);
					flag = true;
					break;
				}
			}
		}

		else
		{
			m_database->m_authors.push_back(new_author);
			flag = true;
		}
	}

	return true;
}

AdminMenu::~AdminMenu()
{}