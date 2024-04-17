﻿#include "AdminMenu.h"

AdminMenu::AdminMenu(DataBase* database, int user_id) : Menu(database, user_id)
{

}

void AdminMenu::printMenu() const
{
	Menu::printMenu();

	std::cout << " 14 - Добавить песню  " << std::endl;
	std::cout << " 15 - Добавить автора " << std::endl;
	std::cout << " 16 - Добавить альбом " << std::endl;
	std::cout << " 17 - Редактировать песню  " << std::endl;
	std::cout << " 18 - Редактировать автора " << std::endl;
	std::cout << " 19 - Редактировать альбом " << std::endl;
}

Result AdminMenu::runSelected(int selected)
{
	Result result = Menu::runSelected(selected);

	if (result != Result::NOT_SUPPORTED)
	{
		return result;
	}

	if (selected <= 19)
	{
		bool ok = true;
		switch (selected)
		{
		case 14:
			ok = AdminMenu::addSong();
			break;
		case 15:
			ok = AdminMenu::addAuthor();
			break;
		case 16:
			ok = AdminMenu::addAlbum();
			break;
		case 17:
			ok = AdminMenu::editSong();
			break;
		case 18:
			ok = AdminMenu::editAuthor();
			break;
		case 19:
			ok = AdminMenu::editAlbum();
			break;
		default:
			return Result::WITH_ERROR;
			break;
		}

		system("pause");

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
				const MyVector<Song>& songs = m_database->getSongs();
				int size = songs.size();

				for (int j = 0; j < size; ++j)
				{
					if (songs[j].m_name == new_song.m_name && songs[j].m_album == new_song.m_album)
					{
						std::cout << "В альбоме в таким id уже есть песня с таким именем." << '\n';
					}
				}

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

		const MyVector<Author>& authors = m_database->getAuthors();
		int size = authors.size();

		for (int i = 0; i < size; ++i)
		{
			if (authors[i].m_id == authors_id)
			{
				std::cout << "Автор с таким id: " << authors[i].m_name << std::endl;
				std::cout << "Подтвердите выбор:" << std::endl;
				std::cout << "1 - Да." << std::endl;
				std::cout << "2 - Нет." << std::endl;

				int selection = 0;

				inputInt(selection);

				switch (selection)
				{
				case 1:
					flag_3 = true;
					break;
				case 2:
					break;
				default:
					break;
				}
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

	m_database->addAlbum(new_album);

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

		int size = m_database->getAuthors().size();

		if (size != 0)
		{
			for (int i = 0; i < size; ++i)
			{
				if (m_database->getAuthors()[i].m_name == new_author.m_name)
				{
					std::cout << "Автор с таким именем уже существует." << std::endl;
					std::cout << "Введите другое имя." << std::endl;
				}
				else
				{
					flag = true;
					break;
				}
			}
		}

		else
		{
			m_database->addAuthor(new_author);
			flag = true;
		}
	}

	return true;
}

bool AdminMenu::editSong()
{
	const MyVector<Song>& songs = m_database->getSongs();
	int size_songs = songs.size();

	if (size_songs == 0) { return false; }

	const MyVector<Album>& albums = m_database->getAlbums();
	int size_albums = albums.size();

	Song new_song;
	int id;
	bool f = false;

	for (int i = 0; i < size_songs; ++i)
	{
		std::cout << songs[i] << std::endl;
	}

	std::cout << std::endl;

	while (f == false)
	{
		std::cout << "Введите id песни, которую вы хотите редактировать: ";
		std::cin >> id;

		for (int i = 0; i < size_songs; ++i)
		{
			if (songs[i].m_id == id)
			{
				new_song = songs[i];
				f = true;
			}
		}

		if (f == false)
		{
			std::cout << "Песни с таким id нет." << std::endl;
		}
	}

	std::cout << "\nЧто хотите поменять?" << '\n';
	int choice;
	std::cout << "+--------------+\n";
	std::cout << "| 1 - Имя      |\n";
	std::cout << "| 2 - Альбом   |\n";
	std::cout << "| 3 - Жанр     |\n";
	std::cout << "+-------------+\n";
	std::cin >> choice;

	bool flag = false;
	bool flag_for_name = false;

	switch (choice)
	{
	case 1:
		while (flag == false)
		{
			std::cout << "Введите новое имя: ";
			std::cin.ignore();
			getline(std::cin, new_song.m_name);

			for (int i = 0; i < size_songs; ++i)
			{
				if (songs[i].m_name == new_song.m_name && songs[i].m_album == new_song.m_album)
				{
					std::cout << "В этом альбоме уже существует песня с таким именем." << "\n";
					flag_for_name = true;
				}
			}

			if (flag_for_name == false)
			{
				m_database->editSong(id, &new_song);
				flag = true;
			}
		}
		break;

	case 2:
		std::cout << "Альбомы: " << std::endl;

		for (int i = 0; i < size_albums; ++i)
		{
			std::cout << albums[i] << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "Введите id нового альбома: ";

		while (flag == false)
		{
			inputInt(new_song.m_album);

			for (int i = 0; i < size_albums; ++i)
			{
				if (albums[i].m_id == id)
				{
					std::cout << "Имя альбома с таким id: ";
					std::cout << albums[i].m_name << std::endl;

					std::cout << "Подтвердите выбор альбома:\n ";
					std::cout << "1 - да \n";
					std::cout << "2 - нет \n";

					int selection;
					inputInt(selection);

					switch (selection)
					{
					case 1:
						flag = true;
						break;
					case 2:
						break;
					default:
						break;
					}
				}
			}

			if (flag == false) { std::cout << "Нет альбома с таким id.\n"; }
		}
		m_database->editSong(id, &new_song);
		break;

	case 3:
		std::cout << "\nВыберите новый жанр: \n";

		int selection;

		std::cout << "+-------------------+\n";
		std::cout << "| 1. Рок            |\n";
		std::cout << "| 2. Джаз           |\n";
		std::cout << "| 3. Поп            |\n";
		std::cout << "| 4. Классическая   |\n";
		std::cout << "| 5. Электронная    |\n";
		std::cout << "+-------------------+\n";

		inputInt(selection);

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
		m_database->editSong(id, &new_song);
		break;
	default:
		break;
	}

	return true;
}

bool AdminMenu::editAuthor()
{
	Author new_author;
	const MyVector<Author>& authors = m_database->getAuthors();
	int size_authors = authors.size();
	bool flag = false;
	bool flag_2 = false;

	for (int i = 0; i < size_authors; ++i)
	{
		std::cout << authors[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Введите id автора, имя которого вы хотите редактировать: ";
	int id;
	inputInt(id);


	while (flag == false)
	{
		std::cout << "Введите новое имя имя автора: ";
		std::cin.ignore();
		getline(std::cin, new_author.m_name);

		for (int i = 0; i < size_authors; ++i)
		{
			if (authors[i].m_name == new_author.m_name)
			{
				std::cout << "Автор с таким именем уже есть. " << std::endl;
			}
		}
	}
	m_database->editAuthor(id, &new_author);
	return true;
}

bool AdminMenu::editAlbum()
{
	Album new_album;
	const MyVector<Album>& albums = m_database->getAlbums();
	const MyVector<Author>& authors = m_database->getAuthors();
	int size_authors = authors.size();

	int size_albums = albums.size();

	if (size_albums == 0)
	{
		std::cout << "Список альбомов пуст, нчеего редактировать." << std::endl;
		return false;
	}

	bool flag = false;
	bool flag_2 = false;

	int id;

	std::cout << "Альбомы: " << std::endl;

	for (int i = 0; i < size_albums; ++i)
	{
		std::cout << albums[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	while (flag == false)
	{
		std::cout << "Введите id альбома, который вы хотите редактировать: ";

		inputInt(id);

		for (int i = 0; i < size_albums; ++i)
		{
			if (albums[i].m_id == id)
			{
				new_album = albums[i];
				flag = true;
			}
		}

		if (flag == false) { std::cout << "Альбома с таким id не найдено.\n"; }
	}

	std::cout << "\nЧто хотите поменять?" << '\n';
	int choice;
	std::cout << "+---------------+\n";
	std::cout << "| 1 - Имя       |\n";
	std::cout << "| 2 - Авторов   |\n";
	std::cout << "+---------------+\n";
	std::cin >> choice;

	bool f = false;

	switch (choice)
	{
	case 1:
		while (flag_2 == false)
		{
			std::cout << "Введите новое название альбома: ";
			std::cin.ignore();
			getline(std::cin, new_album.m_name);

			for (int i = 0; i < size_albums; ++i)
			{
				if (albums[i].m_name == new_album.m_name && new_album.m_authors == albums[i].m_authors)
				{
					std::cout << "У этого исполнителя уже есть альбом с таким именем. ";
					f = true;
				}
			}

			if (f == false)
			{
				m_database->editAlbum(id, &new_album);
				flag = true;
			}
		}
		break;
	case 2:
		std::cout << "Авторы: \n";

		for (int i = 0; i < size_authors; ++i)
		{
			std::cout << authors[i] << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;

		while (flag == false)
		{
			std::cout << "Введите новых авторов альбома: ";
			int authors_id;
			std::cin >> authors_id;

			for (int i = 0; i < size_authors; ++i)
			{
				if (authors[i].m_id == id)
				{
					new_album.m_authors.clear();
					new_album.m_authors.push_back(authors_id);
					flag = true;
				}
			}
			if (flag == false) { std::cout << "Такого исполнителя нетю"; }
		}

		break;
	default:
		break;
	}


	return true;
}

AdminMenu::~AdminMenu()
{}