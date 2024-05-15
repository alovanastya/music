#include "DataBase.h"

DataBase::DataBase()
{
	m_favorite_songs.push_back(MyVector<int>());
	m_favorite_authors.push_back(MyVector<int>());
	m_favorite_albums.push_back(MyVector<int>());
}

int DataBase::check_user(const std::string& name, const std::string& password) const
{
	int quantity = m_name.size();

	for (int i = 0; i < quantity; i++)
	{
		if (m_name[i] == name && m_password[i] == password)
		{
			return i;
		}
	}

	return -1;
}

bool DataBase::addSong(const Song& song)
{
	m_songs.push_back(song);
	m_songs.back().m_id = m_new_song_id;
	++m_new_song_id;

	return true;
}

bool DataBase::operator +(const Song& song)
{
	m_songs.push_back(song);
	m_songs.back().m_id = m_new_song_id;
	++m_new_song_id;

	return true;
}

bool DataBase::addAlbum(const Album& new_album)
{
	m_albums.push_back(new_album);
	m_albums.back().m_id = m_new_album_id;
	++m_new_album_id;
	return true;
}

bool DataBase::operator +(const Album& new_album)
{
	m_albums.push_back(new_album);
	m_albums.back().m_id = m_new_album_id;
	++m_new_album_id;

	return true;
}

bool DataBase::addAuthor(const Author& new_author)
{
	m_authors.push_back(new_author);
	m_authors.back().m_id = m_new_author_id;
	++m_new_author_id;
	return true;
}

bool DataBase::operator +(const Author& new_author)
{
	m_authors.push_back(new_author);
	m_authors.back().m_id = m_new_author_id;
	++m_new_author_id;

	return true;
}

bool DataBase::editSong(int id, const Song& result)
{
	int size_m_songs = m_songs.size();

	for (int i = 0; i < size_m_songs; i++)
	{
		if (m_songs[i].m_id == id)
		{
			m_songs[i] = result;
			return true;
		}
	}

	return false;
}

bool DataBase::editAlbum(int id, const Album& result)
{
	int size_m_albums = m_albums.size();

	for (int i = 0; i < size_m_albums; i++)
	{
		if (m_albums[i].m_id == id)
		{
			m_albums[i] = result;
			return true;
		}
	}
	return false;
}

bool DataBase::editAuthor(int id, const Author& result)
{
	int size_m_authors = m_authors.size();

	for (int i = 0; i < size_m_authors; i++)
	{
		if (m_authors[i].m_id == id)
		{
			m_authors[i] = result;
			return true;
		}
	}
	return false;
}

bool DataBase::getSong(int id, const Song*& result) const
{
	int size_m_songs = m_songs.size();

	for (int i = 0; i < size_m_songs; i++)
	{
		if (m_songs[i].m_id == id)
		{
			result = &m_songs[i];
			return true;
		}
	}

	return false;
}

bool DataBase::getAlbum(int id, const Album*& result) const
{
	int size_m_albums = m_albums.size();

	for (int i = 0; i < size_m_albums; i++)
	{
		if (m_albums[i].m_id == id)
		{
			result = &m_albums[i];
			return true;
		}
	}
	return false;
}

bool DataBase::getAuthor(int id, const Author*& result) const
{
	int size_m_authors = m_authors.size();

	for (int i = 0; i < size_m_authors; i++)
	{
		if (m_authors[i].m_id == id)
		{
			result = &m_authors[i];
			return true;
		}
	}
	return false;
}

bool DataBase::addFavoriteSong(int user_id, int song_id)
{
	if (m_favorite_songs.size() < user_id)
	{
		return false;
	}

	if (m_favorite_songs[user_id].size() != 0)
	{
		for (int i = 0; i < m_favorite_songs[user_id].size(); i++)
		{
			if (m_favorite_songs[user_id][i] == song_id)
			{
				std::cout << "Такая песня уже добавлена.\n";
				return false;
			}
		}
	}

	m_favorite_songs[user_id].push_back(song_id);
	return true;
}

bool DataBase::addFavoriteAuthor(int user_id, int author_id)
{
	if (m_authors.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Нет внесенных песен." << std::endl;
		return false;
	}

	else if (m_favorite_authors.size() < user_id)
	{
		return false;
	}

	if (m_favorite_authors[user_id].size() != 0)
	{
		for (int i = 0; i < m_favorite_authors[user_id].size(); i++)
		{
			if (m_favorite_authors[user_id][i] == author_id)
			{
				std::cout << "Такой автор уже добавлен.\n";
				return false;
			}
		}
	}

	m_favorite_authors[user_id].push_back(author_id);
	return true;
}

bool DataBase::addFavoriteAlbum(int user_id, int album_id)
{
	if (m_albums.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Нет внесенных песен." << std::endl;
		return false;
	}

	else if (m_favorite_albums.size() < user_id)
	{
		return false;
	}

	if (m_favorite_albums[user_id].size() != 0)
	{
		for (int i = 0; i < m_favorite_albums[user_id].size(); i++)
		{
			if (m_favorite_albums[user_id][i] == album_id)
			{
				std::cout << "Такой альбом уже добавлен.\n";
				return false;
			}
		}
	}

	m_favorite_albums[user_id].push_back(album_id);

	return true;
}

bool DataBase::getFavoriteSongs(int user_id, const MyVector<int>*& result) const
{
	if (m_favorite_songs.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых песен пуст." << std::endl;
		return false;
	}

	if (m_favorite_songs.size() < user_id)
	{
		return false;
	}

	result = &m_favorite_songs[user_id];
	return true;
}

bool DataBase::getFavoriteAuthors(int user_id, const MyVector<int>*& result) const
{
	if (m_favorite_authors.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых авторов пуст." << std::endl;
		return false;
	}

	if (m_favorite_authors.size() < user_id)
	{
		return false;
	}

	result = &m_favorite_authors[user_id];
	return true;
}

bool DataBase::getFavoriteAlbums(int user_id, const MyVector<int>*& result) const
{
	if (m_favorite_albums.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых альбомов пуст." << std::endl;
		return false;
	}

	if (m_favorite_albums.size() < user_id)
	{
		return false;
	}

	result = &m_favorite_albums[user_id];
	return true;
}

bool DataBase::deleteFavoriteSong(int user_id, int song_id)
{
	if (m_favorite_authors.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых авторов пуст." << std::endl;
		return false;
	}

	int size = m_favorite_songs[user_id].size();

	for (int j = 0; j < size; j++)
	{
		if (m_favorite_songs[user_id][j] == song_id)
		{
			m_favorite_songs[user_id].deleteElement(j);
			std::cout << "Песня удалена из любимых.\n";
			getchar();
			return true;
		}
	}

	std::cout << "Песни с таким id нет." << std::endl;

	return false;
}

bool DataBase::deleteFavoriteAuthor(int user_id, int author_id)
{
	if (m_favorite_authors.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых авторов пуст." << std::endl;
		return false;
	}

	int size = m_favorite_authors[user_id].size();

	for (int j = 0; j < size; j++)
	{
		if (m_favorite_authors[user_id][j] == author_id)
		{
			m_favorite_authors[user_id].deleteElement(j);
			std::cout << "Автор удален из любимых.\n";
			getchar();
			return true;
		}
	}

	std::cout << "Нет автора с таким id.\n";
	return false;
}

bool DataBase::deleteFavoriteAlbum(int user_id, int album_id)
{
	if (m_favorite_albums.size() == 0)
	{
		std::cout << "Ошибка!!\n";
		std::cout << "Список любимых альбомов пуст." << std::endl;
		return false;
	}

	for (int j = 0; j < m_favorite_albums[user_id].size(); j++)
	{
		if (m_favorite_albums[user_id][j] == album_id)
		{
			m_favorite_albums[user_id].deleteElement(j);
			std::cout << "Альбом удален из любимых.\n";
			getchar();
			return true;
		}
	}

	std::cout << "Нет альбома с таким id.\n";
	return false;
}

bool DataBase::addUser(const std::string& name, const std::string& password)
{
	int size = m_name.size();

	for (int i = 0; i < size; ++i)
	{
		if (m_name[i] == name && m_password[i] == password)
		{
			std::cout << "Такой пользователь уже есть.";
			return false;
		}
	}

	m_name.push_back(name);
	m_password.push_back(password);

	m_favorite_songs.push_back({});
	m_favorite_authors.push_back({});
	m_favorite_albums.push_back({});

	return true;
}

const MyVector<Song>& DataBase::getSongs() const
{
	return m_songs;
}

const MyVector<Album>& DataBase::getAlbums() const
{
	return m_albums;
}

const MyVector<Author>& DataBase::getAuthors() const
{
	return m_authors;
}

MyVector<int> DataBase::sortSongsByName() const
{
	int size = m_songs.size();
	MyVector<bool> need_ignore(false, size);
	MyVector<int> songs_id(0, size);

	for (int i = 0; i < size; ++i)
	{
		std::string min = "}";
		int min_index = 0;

		for (int j = 0; j < size; ++j)
		{
			if ((m_songs[j].m_name < min) && (need_ignore[j] == false))
			{
				min = m_songs[j].m_name;
				min_index = j;
			}
		}

		need_ignore[min_index] = true;
		songs_id[i] = m_songs[min_index].m_id;
	}

	return songs_id;
}

MyVector<int> DataBase::sortAuthorsByName() const
{
	int size = m_authors.size();
	MyVector<bool> need_ignore(false, size);
	MyVector<int> authors_id(0, size);

	for (int i = 0; i < size; ++i)
	{
		std::string min = "}";
		int min_index = 0;

		for (int j = 0; j < size; ++j)
		{
			if ((m_authors[j].m_name < min) && (need_ignore[j] == false))
			{
				min = m_authors[j].m_name;
				min_index = j;
			}
		}

		need_ignore[min_index] = true;
		authors_id[i] = m_authors[min_index].m_id;
	}

	return authors_id;
}

MyVector<int> DataBase::sortAlbumsByName() const
{
	int size = m_albums.size();
	MyVector<bool> need_ignore(false, size);
	MyVector<int> albums_id(0, size);

	for (int i = 0; i < size; ++i)
	{
		std::string min = "}";
		int min_index = 0;

		for (int j = 0; j < size; ++j)
		{
			if ((m_albums[j].m_name < min) && (need_ignore[j] == false))
			{
				min = m_albums[j].m_name;
				min_index = j;
			}
		}

		need_ignore[min_index] = true;
		albums_id[i] = m_albums[min_index].m_id;
	}

	return albums_id;
}

//bool DataBase::getUsers(MyVector<std::string>*& names, MyVector<std::string>*& passwords)
//{
//	MyVector <std::string> names_1;
//	MyVector <std::string> passwords_1;
//
//	int size = m_name.size();
//
//	for (int i = 0; i < size; ++i)
//	{
//		names_1.push_back(m_name[i]);
//		passwords_1.push_back(m_password[i]);
//	}
//
//	names = &names_1;
//	passwords = &passwords_1;
//
//	return true;
//}

