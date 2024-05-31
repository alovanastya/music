#include "AdminMenu.h"

AdminMenu::AdminMenu(DataBase* database, int user_id) : Menu(database, user_id)
{}

void AdminMenu::printMenu() const
{
	Menu::printMenu();

	std::cout << "17 - Добавить песню  " << std::endl;
	std::cout << "18 - Добавить автора " << std::endl;
	std::cout << "19 - Добавить альбом " << std::endl;
	std::cout << std::endl;
	std::cout << "20 - Редактировать песню  " << std::endl;
	std::cout << "21 - Редактировать автора " << std::endl;
	std::cout << "22 - Редактировать альбом " << std::endl;
}

Result AdminMenu::runSelected(int selected)
{
	Result result = Menu::runSelected(selected);

	if (result != Result::NOT_SUPPORTED)
	{
		return result;
	}

	if (selected <= 22)
	{
		try
		{
			switch (selected)
			{
			case 17:
				addSong();
				break;
			case 18:
				addAuthor();
				break;
			case 19:
				addAlbum();
				break;
			case 20:
				editSong();
				break;
			case 21:
				editAuthor();
				break;
			case 22:
				editAlbum();
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

void AdminMenu::addSong()
{
	Song new_song;
	std::cin >> new_song;
	m_database->addSong(new_song);
	std::cout << "Песня добавлена." << std::endl;
}

void AdminMenu::addAlbum()
{
	Album new_album;
	std::cin >> new_album;
	m_database->addAlbum(new_album);
	std::cout << "Альбом добавлен." << std::endl;
}

void AdminMenu::addAuthor()
{
	Author new_author;
	std::cin >> new_author;
	m_database->addAuthor(new_author);
	std::cout << "Автор добавлен." << std::endl;
}


void AdminMenu::editSongsAlbum(Song& song) const
{
	int album_id;
	bool album_found = false;

	std::cout << "Введите новый альбом: ";
	while (!album_found)
	{
		album_id = inputInt();
		album_found = m_database->albumExists(album_id);

		if (!album_found)
		{
			std::cout << "Вы ввели несуществующий альбом. Попробуйте еще раз" << std::endl;
		}
	}

	song.m_album = album_id;
}

void AdminMenu::editSongsName(Song& song) const
{
	std::cout << "Введите новое имя: ";
	std::getline(std::cin, song.m_name);
}

void AdminMenu::editSongsGenre(Song& song) const
{
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
		std::cin >> genre;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();


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
}

void AdminMenu::editSong()
{
	const MyVector<Song>& songs = m_database->getSongs();
	if (songs.size() == 0)
	{
		std::cout << "Список песен пуст." << std::endl;
		return;
	}

	int song_id;
	bool song_found = false;

	std::cout << "Введите id песни: ";
	while (!song_found)
	{
		song_id = inputInt();

		if (m_database->songExists(song_id))
		{
			song_found = true;
		}

		else
		{
			std::cout << "Песни с таким id не существует. Попробуйте еще раз: ";
		}
	}

	std::cout << std::endl << "Что хотите поменять?" << std::endl;
	std::cout << "+--------------+\n";
	std::cout << "| 1 - Имя      |\n";
	std::cout << "| 2 - Альбом   |\n";
	std::cout << "| 3 - Жанр     |\n";
	std::cout << "+--------------+\n";

	Song new_song = m_database->getSong(song_id);
	bool song_edited = false;
	while (!song_edited)
	{
		const int choice = inputInt();

		switch (choice)
		{
		case 1:
			editSongsName(new_song);
			song_edited = true;
			break;
		case 2:
			editSongsAlbum(new_song);
			song_edited = true;
			break;
		case 3:
			editSongsGenre(new_song);
			song_edited = true;
			break;
		default:
			std::cout << "Выбран недопустимый вариант. Введите корретное число: ";
			break;
		}
	}

	m_database->editSong(song_id, new_song);
	std::cout << "Изменено." << std::endl;
}

void AdminMenu::editAuthor()
{
	const MyVector<Author>& authors = m_database->getAuthors();
	if (authors.size() == 0)
	{
		std::cout << "Список авторов пуст." << std::endl;
		return;
	}

	int author_id;
	bool author_found = false;
	std::cout << "Введите id автора: ";
	while (!author_found)
	{
		author_id = inputInt();

		if (m_database->authorExists(author_id))
		{
			author_found = true;
		}

		else
		{
			std::cout << "Автора с таким id не существует. Попробуйте еще раз: ";
		}
	}

	Author new_author = m_database->getAuthor(author_id);
	std::cout << "Введите новое имя автора: ";
	std::getline(std::cin, new_author.m_name);
	m_database->editAuthor(author_id, new_author);
}

void AdminMenu::editAlbumsName(Album& new_album) const
{
	bool album_is_unique = false;

	std::string new_name;

	std::cout << "Введите новое имя: ";
	while (!album_is_unique)
	{
		std::cin >> new_name;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();

		album_is_unique = true;
		for (int i = 0; i < new_album.m_authors.size(); ++i)
		{
			if (m_database->albumExists(new_album.m_authors[i], new_name))
			{
				album_is_unique = false;
			}
		}

		if (!album_is_unique)
		{
			std::cout << "У одного из исполнителей уже есть альбом с таким назваванем. Попробуйте еще раз: ";
		}
	}

	new_album.m_name = new_name;
}

void AdminMenu::editAlbumsAuthors(Album& new_album) const
{
	std::cout << "Введите новых авторов. Введите -1, чтобы закончить список" << std::endl;

	MyVector<int> new_authors;
	int new_author = 0;

	while (new_author != -1)
	{
		std::cin >> new_author;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();

		if (!m_database->authorExists(new_author))
		{
			std::cout << "Такого автора не существует. Введите другого автора" << std::endl;
			continue;
		}

		if (m_database->albumExists(new_author, new_album.m_name))
		{
			std::cout << "У этого автора уже есть альбом с таким названием. Введите другого автора" << std::endl;
			continue;
		}

		for (int i = 0; i < new_authors.size(); ++i)
		{
			if (new_authors[i] == new_author)
			{
				std::cout << "Этот автор уже есть в новом списке. Введите другого автора" << std::endl;
				continue;
			}
		}

		new_authors.push_back(new_author);
	}

	new_album.m_authors = new_authors;
}

void AdminMenu::editAlbum()
{
	int album_id;
	bool album_found = false;

	std::cout << "Введите id альбома: ";
	while (!album_found)
	{
		album_id = inputInt();

		if (m_database->songExists(album_id))
		{
			album_found = true;
		}

		else
		{
			std::cout << "Песни с таким id не существует. Попробуйте еще раз: ";
		}
	}

	std::cout << std::endl << "Что хотите поменять?" << std::endl;
	std::cout << "+--------------+\n";
	std::cout << "| 1 - Имя      |\n";
	std::cout << "| 2 - Авторов  |\n";
	std::cout << "+--------------+\n";

	Album new_album = m_database->getAlbum(album_id);
	bool album_edited = false;
	while (!album_edited)
	{
		const int choice = inputInt();

		switch (choice)
		{
		case 1:
			editAlbumsName(new_album);
			album_edited = true;
			break;
		case 2:
			editAlbumsAuthors(new_album);
			album_edited = true;
			break;
		default:
			std::cout << "Выбран недопустимый вариант. Введите корретное число: ";
			break;
		}
	}

	m_database->editAlbum(album_id, new_album);
	std::cout << "Изменено." << std::endl;
}

AdminMenu::~AdminMenu()
{}