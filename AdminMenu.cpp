#include "AdminMenu.h"

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

void AdminMenu::enterAlbum(Song& new_song, bool& success)
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
				if (songs[j] == new_song)
				{
					std::cout << "В альбоме в таким id уже есть песня с таким именем." << '\n';
				}
			}
			success = true;
		}
	}

	if (success == false)
	{
		std::cout << "Альбома с таким id не существует. Хотите создать?" << std::endl;
		std::cout << "1. Да\n";
		std::cout << "2. Нет\n";
		int choice;
		inputInt(choice);

		switch (choice)
		{
		case 1:
		{
			addAlbum();
		    const MyVector<Album>& albums_2 = m_database->getAlbums();
			new_song.m_album = albums_2.back().m_id;
			success = true;
		}
			break;
		case 2:
			std::cout << "Тогда попробуйте ввести id снова\n";
			success = false;
			break;
		default:
			break;
		}
	}
}

void AdminMenu::chooseGenre(Song& new_song, bool& success)
{
	std::cout << "\nВыберите жанр: \n";

	for (int i = 0; i < (int)Genre::COUNT; ++i)
	{
		std::cout << i + 1 << ". " << GENRES_NAMES[i] << std::endl;
	}

	success = false;

	int selection;

	while (success == false)
	{
		inputInt(selection);

		if (selection > (int)Genre::COUNT || selection <= 0)
		{
			continue;
		}

		new_song.m_genre = (Genre)(selection - 1);
		success = true;
	}
}

bool AdminMenu::addSong()
{
	Song new_song;
	std::cout << "Введите название песни: ";
	//std::cin.ignore(); // Первая буква названия игнорировалась почему-то
	std::cin.clear();
	std::cin.sync();
	std::getline(std::cin, new_song.m_name);

	bool success = false;

	while (success == false)
	{
		enterAlbum(new_song, success);
	}

	chooseGenre(new_song, success);

	m_database->addSong(new_song);
	return true;
}

void AdminMenu::enterAuthors(Album& new_album, int authors_size, bool& success, const MyVector<Author>& authors)
{
	std::cout << "\nВведите id автора или авторов альбома: ";
	int authors_id;
	inputInt(authors_id);

	for (int i = 0; i < authors_size; ++i)
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
				new_album.m_authors.push_back(authors_id);
				success = true;
				break;
			case 2:
				break;
			default:
				break;
			}
		}
	}

	if (success == false)
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
			new_album.m_authors.push_back(authors.back().m_id);
			success = true;
			break;
		case 2:
			std::cout << "Тогда попробуйте ввести id снова.\n";
			success = false;
			break;
		default:
			break;
		}
	}

	
	//MyVector<int> new_authors;
	//int authors_id = 0;
	//bool enter_authors = false;
	//
	//while (enter_authors == false)
	//{
	//	std::cout << "Введите авторов альбома и -1 в конце: ";

	//	while (authors_id != -1)
	//	{
	//		std::cin >> authors_id;
	//		new_authors.push_back(authors_id);
	//	}

	//	bool all_authors_are_good = true;
	//	
	//	for (int i = 0; i < new_authors.size() - 1; ++i)
	//	{
	//		bool author_found = false;

	//		for (int j = 0; j < authors.size() - 1; ++j)
	//		{
	//			if (authors[j].m_id == new_authors[i])
	//			{
	//				author_found = true;
	//			}
	//		}

	//		all_authors_are_good = all_authors_are_good && author_found;
	//	}

	//	if (all_authors_are_good)
	//	{
	//		new_album.m_authors = new_authors;
	//		enter_authors = true;
	//		success = true;
	//	}

	//	else
	//	{
	//		std::cout << "Автора с таким id нет.\nХотите добавить нового автора?\n\n";
	//		std::cout << "1. Да\n";
	//		std::cout << "2. Нет\n";

	//		int choice;

	//		inputInt(choice);

	//		switch (choice)
	//		{
	//		case 1:
	//			addAuthor();
	//			new_album.m_authors.push_back(authors.back().m_id);
	//			enter_authors = true;
	//			success = true;
	//			break;
	//		case 2:
	//			std::cout << "Тогда попробуйте ввести id снова.\n";
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
}

bool AdminMenu::addAlbum()
{
	Album new_album;
	const MyVector<Author>& authors = m_database->getAuthors();
	int authors_size = authors.size();
	bool success = false;

	while (success == false)
	{
		enterAuthors(new_album, authors_size, success, authors);
	}

	bool same_name = false;
	success = false;

	while (success == false)
	{
		std::cout << "\nВведите название альбома: ";
		//std::cin.ignore();
		std::cin.clear();
		std::cin.sync();
		getline(std::cin, new_album.m_name);

		const MyVector<Album>& albums = m_database->getAlbums();
		int albums_size = albums.size();

		for (int j = 0; j < albums_size; ++j)
		{
			if (albums[j].m_authors == new_album.m_authors && albums[j].m_name == new_album.m_name)
			{
				std::cout << "У автора уже есть альбом с таким именем." << std::endl;
				same_name = true;
			}
		}

		if (same_name == false)
		{
			success = true;
		}
	}

	m_database->addAlbum(new_album);
	return true; // Дважды вызывается деструтор 
}

bool AdminMenu::addAuthor()
{
	Author new_author;
	std::cout << "Введите имя автора, которого хотите добавить: ";
	bool success = false;

	while (success == false)
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
					success = true;
					break;
				}
			}
		}
		else
		{
			success = true;
		}
	}
	m_database->addAuthor(new_author);
	return true;
}

void AdminMenu::editSongsAlbum(Song& new_song, int& size_albums, bool& success, const MyVector<Album>& albums, int& id)
{
	std::cout << "Альбомы: " << std::endl;

	for (int i = 0; i < size_albums; ++i)
	{
		std::cout << albums[i] << std::endl;
	}

	std::cout << std::endl;

	bool re_entry = false;

	while (success == false)
	{
		re_entry = false;
		std::cout << "Введите новый id альбома: ";
		inputInt(new_song.m_album);

		for (int i = 0; i < size_albums; ++i)
		{
			if (albums[i].m_id == new_song.m_album)
			{
				std::cout << "Имя альбома с таким id: ";
				std::cout << albums[i].m_name << std::endl;
				std::cout << "Подтвердите выбор альбома: " << std::endl;
				std::cout << "1 - Да" << std::endl;
				std::cout << "2 - Нет" << std::endl;

				int selection;
				inputInt(selection);

				switch (selection)
				{
				case 1:
					success = true;
					break;
				case 2:
					re_entry = true;
					break;
				default:
					break;
				}
			}
		}
		if (success == false && re_entry == false) { std::cout << "Нет альбома с таким id.\n"; }
	}
}

void AdminMenu::editSongsName(Song& new_song, int& size_songs, bool& success, const MyVector<Song>& songs, int& id)
{
	bool flag_for_name = false;

	while (success == false)
	{
		std::cout << "Введите новое имя: ";
		std::cin.ignore();
		getline(std::cin, new_song.m_name);

		for (int i = 0; i < size_songs; ++i)
		{
			if (songs[i] == new_song)
			{
				std::cout << "В этом альбоме уже существует песня с таким именем." << "\n";
				flag_for_name = true;
			}
		}

		if (flag_for_name == false)
		{
			m_database->editSong(id, new_song);
			success = true;
		}
	}
}

void AdminMenu::enterId(Song& new_song, int& size_songs, const MyVector<Song>& songs, int& id)
{
	bool correct_id = false;

	while (correct_id == false)
	{
		std::cout << "Введите id песни, которую вы хотите редактировать: ";
		inputInt(id);

		for (int i = 0; i < size_songs; ++i)
		{
			if (songs[i].m_id == id)
			{
				new_song = songs[i];
				correct_id = true;
			}
		}

		if (correct_id == false)
		{
			std::cout << "Песни с таким id нет." << std::endl;
		}
	}
}

bool AdminMenu::editSong()
{
	const MyVector<Song>& songs = m_database->getSongs();
	const MyVector<Album>& albums = m_database->getAlbums();
	int size_songs = songs.size();
	int size_albums = albums.size();
	Song new_song;
	int id;

	if (size_songs == 0) 
	{ 
		std::cout << "Список песен пуст." << std::endl;
		return false; 
	}

	std::cout << std::endl;

	for (int i = 0; i < size_songs; ++i)
	{
		std::cout << songs[i] << std::endl;
	}

	std::cout << std::endl;

	enterId(new_song, size_songs, songs, id);

	std::cout << "\nЧто хотите поменять?" << '\n';
	int choice;
	std::cout << "+--------------+\n";
	std::cout << "| 1 - Имя      |\n";
	std::cout << "| 2 - Альбом   |\n";
	std::cout << "| 3 - Жанр     |\n";
	std::cout << "+--------------+\n";

	inputInt(choice);

	bool success = false;

	switch (choice)
	{
	case 1:
		editSongsName(new_song, size_songs, success, songs, id);
		success = false;
		break;

	case 2:
		editSongsAlbum(new_song, size_albums, success, albums, id);
		m_database->editSong(id, new_song);
		break;
	case 3:
		chooseGenre(new_song, success);
		m_database->editSong(id, new_song);
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

	if (size_authors == 0)
	{
		std::cout << "Список авторов пуст." << std::endl;
		return false;
	}

	bool success = false;
	bool same_author_found = false;

	for (int i = 0; i < size_authors; ++i)
	{
		std::cout << authors[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Введите id автора, имя которого вы хотите редактировать: ";
	int id;
	inputInt(id);

	while (success == false)
	{
		std::cout << "Введите новое имя автора: ";
		std::cin.ignore();;
		getline(std::cin, new_author.m_name);

		same_author_found = false;
		for (int i = 0; i < size_authors; ++i)
		{
			if (authors[i].m_name == new_author.m_name)
			{
				std::cout << "Автор с таким именем уже есть. " << std::endl;
				same_author_found = true;
			}
		}

		if (!same_author_found)
		{
			m_database->editAuthor(id, new_author);
			success = true;
		}
	}

	return true;
}

void AdminMenu::editAlbumsName(Album& new_album, int& size_albums, const MyVector<Album>& albums, int& id)
{
	bool is_it_changed = false;
	bool same_name = false;

	while (is_it_changed == false)
	{
		std::cout << "Введите новое название альбома: ";
		std::cin.ignore();
		getline(std::cin, new_album.m_name);

		same_name = false;

		for (int i = 0; i < size_albums; ++i)
		{
			if (albums[i].m_name == new_album.m_name && new_album.m_authors == albums[i].m_authors)
			{
				std::cout << "У этого исполнителя уже есть альбом с таким именем. ";
				same_name = true;
			}
		}

		if (same_name == false)
		{
			m_database->editAlbum(id, new_album);
			is_it_changed = true;
		}
	}
}

void AdminMenu::editAlbumsAuthors(Album& new_album, int& size_authors, const MyVector<Author>& authors, int& id)
{
	std::cout << "Авторы: \n";

	for (int i = 0; i < size_authors; ++i)
	{
		std::cout << authors[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	bool edit_authors = false;

	while (edit_authors == false)
	{
		MyVector<int> new_authors;
		int authors_id = 0;

		std::cout << "Введите новых авторов альбома и -1 в конце: ";

		while (authors_id != -1)
		{
			std::cin >> authors_id;
			new_authors.push_back(authors_id);
		}

		bool all_authors_are_good = true;

		for (int i = 0; i < new_authors.size(); ++i)
		{
			bool author_found = false;

			for (int j = 0; j < authors.size(); ++j)
			{
				if (authors[j].m_id == new_authors[i])
				{
					author_found = true;
				}
			}

			all_authors_are_good = all_authors_are_good && author_found;
		}

		if (all_authors_are_good)
		{
			new_album.m_authors = new_authors;
			edit_authors = true;
		}
	}
}

void AdminMenu::enterAlbumsId(Album& new_album, int& size_albums, const MyVector<Album>& albums, int& id)
{
	bool correct_id = false;

	while (correct_id == false)
	{
		std::cout << "Введите id альбома, который вы хотите редактировать: ";
		inputInt(id);

		for (int i = 0; i < size_albums; ++i)
		{
			if (albums[i].m_id == id)
			{
				new_album = albums[i];
				correct_id = true;
			}
		}

		if (correct_id == false)
		{
			std::cout << "Альбома с таким id не найдено.\n";
		}
	}
}

bool AdminMenu::editAlbum()
{
	Album new_album;
	const MyVector<Album>& albums = m_database->getAlbums();
	const MyVector<Author>& authors = m_database->getAuthors();
	int size_authors = authors.size();
	int size_albums = albums.size();
	int id;

	if (size_albums == 0)
	{
		std::cout << "Список альбомов пуст, нечего редактировать." << std::endl;
		return false;
	}

	std::cout << "Альбомы: " << std::endl;

	for (int i = 0; i < size_albums; ++i)
	{
		std::cout << albums[i] << std::endl;
	}

	std::cout << std::endl;

	enterAlbumsId(new_album, size_albums, albums, id);

	std::cout << "\nЧто хотите поменять?" << '\n';
	int choice;
	std::cout << "+---------------+\n";
	std::cout << "| 1 - Имя       |\n";
	std::cout << "| 2 - Авторов   |\n";
	std::cout << "+---------------+\n";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		editAlbumsName(new_album, size_albums, albums, id);
		break;
	case 2:
		editAlbumsAuthors(new_album, size_authors, authors, id);
		break;
	default:
		break;
	}
	return true;
}

AdminMenu::~AdminMenu()
{}