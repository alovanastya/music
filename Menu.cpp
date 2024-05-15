#include "Menu.h"
#include <iostream>
//#include <fstream>

Menu::Menu(DataBase* database, int user_id) : IMenu(database, user_id)
{}

void Menu::printMenu() const
{
	std::cout << " 0 - Выход                         " << std::endl;
	std::cout << " 1 - Добавить пользователя         " << std::endl;
	std::cout << std::endl;							 
	std::cout << " 2 - Добавить любимую песню        " << std::endl;
	std::cout << " 3 - Удалить любимую песню         " << std::endl;
	std::cout << " 4 - Напечатать любимые песни      " << std::endl;
	std::cout << std::endl;							 
	std::cout << " 5 - Добавить любимого автора      " << std::endl;
	std::cout << " 6 - Удалить любимого автора       " << std::endl;
	std::cout << " 7 - Напечатать любимых авторов    " << std::endl;
	std::cout << std::endl;							 
	std::cout << " 8 - Добавить любимый альбом       " << std::endl;
	std::cout << " 9 - Удалить любимый альбом        " << std::endl;
	std::cout << " 10 - Напечатать любимые альбомы    " << std::endl;
	std::cout << std::endl;							 
	std::cout << " 11 - Напечатать все песни         " << std::endl;
	std::cout << " 12 - Напечатать все альбомы       " << std::endl;
	std::cout << " 13 - Напечатать всех авторов      " << std::endl;
	std::cout << std::endl;
	std::cout << " 14 - Сортировать песни по имени   " << std::endl;
	std::cout << " 15 - Сортировать альбомы по имени " << std::endl;
	std::cout << " 16 - Сортировать авторов по имени " << std::endl;
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
			printAlbums();
			break;
		case 13:
			printAuthors();
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
			break;
		}
		getchar();
		return Result::DONE;
	}

	else if (selected > 16)
	{
		return Result::NOT_SUPPORTED;
	}

	std::cout << "Ошибка!\n";
	getchar();
	return Result::WITH_ERROR;
}

void Menu::inputInt(int& result)
{
	bool success = false;
	bool error = false;
	std::string string_result;

	while (!success) {

		try
		{
			std::cin >> string_result;
			result = stoi(string_result);
		}

		catch (std::exception& exception)
		{
			error = true;
			std::cerr << "Пойманное исключение: " << exception.what() << std::endl;
			std::cerr << "Введите корректное число: ";
		}

		if (!error)
		{
			success = true;
		}

		error = false;
	}
}

//bool Menu::saveUserToTextFile()
//{
//	MyVector<std::string>* names;
//	MyVector<std::string>* passwords;
//
//	m_database->getUsers(names, passwords);
//
//	int size = names->size();
//
//	std::string filename = "users.txt";
//
//	std::ofstream file(filename, std::ios::trunc);
//	if (!file.is_open())
//	{
//		std::cout << "Не удалось открыть файл для записи.\n";
//		return false;
//	}
//
//	for (int i = 0; i < size; i++)
//	{
//		file << names[i] << " " << passwords[i];
//
//		if (i != size - 1)
//		{
//			file << std::endl;
//		}
//	}
//
//	file.close();
//
//	return true;
//}

bool Menu::addUser()
{
	std::string login, password, password_2;

	std::cout << "Введите логин: ";
	std::cin >> login;

	bool success = false;

	while (!success)
	{
		std::cout << "Введите пароль: ";
		std::cin >> password;
		std::cout << "Введите пароль еще раз: ";
		std::cin >> password_2;

		if (password == password_2) 
		{
			std::cout << "Верно!\n";
			success = true;
		}

		else
		{
			std::cout << "Пароли не совпадают. Повторите ввод еще раз.\n";
		}
	}

	m_database->addUser(login, password);

	//saveUserToTextFile(); 

	return true;
}

bool Menu::addFavoriteSong()
{
	const MyVector <Song> &songs = m_database->getSongs();
	int size_songs = songs.size();
	
	if (size_songs == 0)
	{
		std::cout << "Песен нет.";
		return false;
	}

	std::cout << "+----------------------------+\n";
	std::cout << "|   Список доступных песен   |\n";
	std::cout << "+----------------------------+\n";

	for (int i = 0; i < size_songs; ++i)
	{
		std::cout << songs[i] << std::endl;
	}

	bool correct_id = false;
	int id;

	while (correct_id == false)
	{
		std::cout << "Введите id песни: ";
		inputInt(id);

		for (int i = 0; i < size_songs; ++i)
		{
			if (songs[i].m_id == id)
			{
				if (m_database->addFavoriteSong(m_user_id, id))
				{
					std::cout << "Добавлена любимая песня." << std::endl;
				}

				correct_id = true;
			}
		}

		if (correct_id == false)
		{
			std::cout << "Песня с таким id отсутствует." << std::endl;
		}
	}
	
	getchar();
	return true;
}

bool Menu::addFavoriteAuthor()
{
	const MyVector <Author>& authors = m_database->getAuthors();
	int authors_size = authors.size();
	
	if (authors_size == 0)
	{
		std::cout << "Список авторов пуст.";
		return false;
	}
	std::cout << "+----------------------------+\n";
	std::cout << "|  Список доступных авторов  |\n";
	std::cout << "+----------------------------+\n";

	for (int i = 0; i < authors_size; ++i)
	{
		std::cout << authors[i] << std::endl;
	}

	bool correct_id = false;
	int id;

	while (correct_id == false)
	{
		std::cout << "Введите id автора:";
		inputInt(id);

		for (int i = 0; i < authors_size; ++i)
		{
			if (authors[i].m_id == id)
			{
				if (m_database->addFavoriteAuthor(m_user_id, id))
				{
					std::cout << "Добавлен любимый автор." << std::endl;
				}

					correct_id = true;
			}
		}

		if (correct_id == false)
		{
			std::cout << "Автор с таким id отсутствует." << std::endl;
		}
	}

	getchar();
	return true;
}

bool Menu::addFavoriteAlbum()
{
	const MyVector <Album>& albums = m_database->getAlbums();
	int albums_size = albums.size();

	if (albums_size == 0)
	{
		std::cout << "Список альбомов пуст.";
		return false;
	}

	std::cout << "+-----------------------------+\n";
	std::cout << "|   Список любимых альбомов   |\n";
	std::cout << "+-----------------------------+\n";

	for (int i = 0; i < albums_size; ++i)
	{
		std::cout << albums[i] << std::endl;										 
	}																				 
																					 
	bool correct_id = false;														 
	int id;																			 
																					 
	while (correct_id == false)														 
	{																				 
		std::cout << "Введите id альбома:";											 
		inputInt(id);																 
																					 
		for (int i = 0; i < albums_size; ++i)										 
		{																			 
			if (albums[i].m_id == id)												 
			{																		 
				if (m_database->addFavoriteAlbum(m_user_id, id))
				{
					std::cout << "Добавлен любимый альбом." << std::endl;
				}

				correct_id = true;													 
			}																		 
		}																			 
																					 
		if (correct_id == false)													 
		{																			 
			std::cout << "Альбом с таким id отсутствует." << std::endl;				 
		}
	}

	getchar();
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

	int size = tmp_vec->size();

	if (size == 0)
	{
		std::cout << "Список пуст." << std::endl;
		return true;
	}

	std::cout << "+----------------------+\n";
	std::cout << "|     Любимые песни    |\n";
	std::cout << "+----------------------+\n";

	for (int i = 0; i < size; ++i)
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

	int size = tmp_vec->size();

	if (size == 0)
	{
		std::cout << "Список пуст." << std::endl;
		return true;
	}

	std::cout << "+----------------------+\n";
	std::cout << "|    Любимые авторы    |\n";
	std::cout << "+----------------------+\n";

	for (int i = 0; i < size; ++i)
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

	int size = tmp_vec->size();

	if (size == 0)
	{
		std::cout << "Список пуст." << std::endl;
		return true;
	}

	std::cout << "+------------------------+\n";
	std::cout << "|     Любимые альбомы    |\n";
	std::cout << "+------------------------+\n";

	const Album* tmp_album;
	for (int i = 0; i < size; ++i)
	{
		m_database->getAlbum(tmp_vec->operator[](i), tmp_album);
		std::cout << (*tmp_album);
	}

	return true;
}

bool Menu::deleteFavoriteSong()
{
	const MyVector<int>* favorite_songs;

	m_database->getFavoriteSongs(m_user_id, favorite_songs);

	int favorite_songs_size = (*favorite_songs).size();

	if (favorite_songs_size == 0)
	{
		std::cout << "Список любимых песен пуст." << std::endl;
		return false;
	}

	printFavoriteSongs();

	std::cout << "Введите id песни, которую хотите удалить: ";

	int id;
	inputInt(id);

	m_database->deleteFavoriteSong(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAuthor()
{
	const MyVector<int>* favorite_authors;

	m_database->getFavoriteAuthors(m_user_id, favorite_authors);

	int favorite_authors_size = (*favorite_authors).size();

	if (favorite_authors_size == 0)
	{
		std::cout << "Список любимых авторов пуст." << std::endl;
		return false;
	}

	printFavoriteAuthors();

	std::cout << "Введите id автора, которого хотите удалить: ";

	int id;
	inputInt(id);

	m_database->deleteFavoriteAuthor(m_user_id, id);

	return true;
}

bool Menu::deleteFavoriteAlbum()
{
	const MyVector<int>* favorite_albums;

	m_database->getFavoriteAlbums(m_user_id, favorite_albums);

	int favorite_albums_size = (*favorite_albums).size();

	if (favorite_albums_size == 0)
	{
		std::cout << "Список любимых альбомов пуст." << std::endl;
		return false;
	}

	printFavoriteAlbums();

	std::cout << "Введите id альбома, который хотите удалить: ";

	int id;
	inputInt(id);

	m_database->deleteFavoriteAlbum(m_user_id, id);

	return true;
}

void Menu::printSongs() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|      Песни      |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Song>& tmp_vector = m_database->getSongs();

	if (tmp_vector.size() == 0)
	{
		std::cout << "Список песен пуст." << std::endl;
		return;
	}

	for (int i = 0; i < tmp_vector.size(); ++i)
	{
		std::cout << tmp_vector[i] << "\n";
	}
}

void Menu::printAlbums() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|     Альбомы     |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Album>& tmp_vector = m_database->getAlbums();

	if (tmp_vector.size() == 0)
	{
		std::cout << "Список альбомов пуст." << std::endl;
		return;
	}

	for (int i = 0; i < tmp_vector.size(); ++i)
	{
		std::cout << tmp_vector[i] << "\n";
	}

	//for (auto& i : tmp_vector)
	//{
	//	std::cout << i;
	//}
}

void Menu::printAuthors() const
{
	std::cout << "+-----------------+\n";
	std::cout << "|     Авторы      |\n";
	std::cout << "+-----------------+\n";

	const MyVector<Author>& tmp_vector = m_database->getAuthors();

	if (tmp_vector.size() == 0)
	{
		std::cout << "Список авторов пуст." << std::endl;
		return;
	}

	int size = tmp_vector.size();

	for (int i = 0; i < size; ++i)
	{
		std::cout << tmp_vector[i] << "\n";
	}
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
}

Menu::~Menu()
{}