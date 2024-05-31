#include "DataBase.h"


DataBase::DataBase()
{
	m_favorite_songs.push_back({});
	m_favorite_authors.push_back({});
	m_favorite_albums.push_back({});

	m_name.push_back("admin");
	m_password.push_back("admin");
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

void DataBase::addSong(const Song& song)
{
	if (!albumExists(song.m_album))
	{
		throw std::exception("Ошибка при добавлении песни. Такого альбома не существует");
	}

	m_songs.push_back(song);
	m_songs.back().m_id = m_new_song_id;
	++m_new_song_id;
}

void DataBase::operator +(const Song& song)
{
	if (!albumExists(song.m_album))
	{
		throw std::exception("Ошибка при добавлении песни. Такого альбома не существует");
	}

	m_songs.push_back(song);
	m_songs.back().m_id = m_new_song_id;
	++m_new_song_id;
}

void DataBase::addAlbum(const Album& new_album)
{
	if (new_album.m_authors.size() == 0)
	{
		throw std::exception("Ошибка при добавлении альбома.Не указано ни одного автора");
	}

	for (int i = 0; i < new_album.m_authors.size(); ++i)
	{
		if (!authorExists(new_album.m_authors[i]))
		{
			throw std::exception("Ошибка при добавлении альбома. Одного из авторов не существует");
		}
	}

	m_albums.push_back(new_album);
	m_albums.back().m_id = m_new_album_id;
	++m_new_album_id;
}

void DataBase::operator +(const Album& new_album)
{
	if (new_album.m_authors.size() == 0)
	{
		throw std::exception("Ошибка при добавлении альбома.Не указано ни одного автора");
	}

	for (int i = 0; i < new_album.m_authors.size(); ++i)
	{
		if (!authorExists(new_album.m_authors[i]))
		{
			throw std::exception("Ошибка при добавлении альбома. Одного из авторов не существует");
		}
	}

	m_albums.push_back(new_album);
	m_albums.back().m_id = m_new_album_id;
	++m_new_album_id;
}

void DataBase::addAuthor(const Author& new_author)
{
	m_authors.push_back(new_author);
	m_authors.back().m_id = m_new_author_id;
	saveAuthorToTxt(new_author.m_name, new_author.m_id);
	++m_new_author_id;
}

void DataBase::operator +(const Author& new_author)
{
	m_authors.push_back(new_author);
	m_authors.back().m_id = m_new_author_id;
	++m_new_author_id;
}

void DataBase::editSong(int id, const Song& new_song)
{
	const int index = getSongIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при редактировании песни. Такой песни не существует");
	}

	if (!albumExists(new_song.m_album))
	{
		throw std::exception("Ошибка при редактировании песни. Такого альбома не существует");
	}

	m_songs[index] = new_song;
}

void  DataBase::editAlbum(int id, const Album& new_album)
{
	const int index = getAlbumIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при редактировании альбома. Такого альбома не существует");
	}

	if (new_album.m_authors.size() == 0)
	{
		throw std::exception("Ошибка при редактировании альбома.Не указано ни одного автора");
	}

	for (int i = 0; i < new_album.m_authors.size(); ++i)
	{
		if (!authorExists(new_album.m_authors[i]))
		{
			throw std::exception("Ошибка при редактировании альбома. Одного из авторов не существует");
		}
	}

	m_albums[index] = new_album;
}

void DataBase::editAuthor(int id, const Author& new_author)
{
	const int index = getAuthorIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при редактировании автора. Такого автора не существует");
	}

	m_authors[index] = new_author;
}

const Song& DataBase::getSong(int id) const
{
	const int index = getSongIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при получении песни. Такой песни не существует");
	}

	return m_songs[index];
}

const Album& DataBase::getAlbum(int id) const
{
	const int index = getAlbumIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при получении альбома. Такого альбома не существует");
	}

	return m_albums[index];
}

const Author& DataBase::getAuthor(int id) const
{
	const int index = getAuthorIndex(id);
	if (index == -1)
	{
		throw std::exception("Ошибка при получении автора. Такого автора не существует");
	}

	return m_authors[index];
}

void DataBase::addFavoriteSong(int user_id, int song_id)
{
	if (m_favorite_songs.size() <= user_id)
	{
		throw std::exception("Ошибка при добавлении любимой песни. Такой песни не существует");
	}

	if (!songExists(song_id))
	{
		throw std::exception("Ошибка при добавлении любимой песни. Такой песни не существует");
	}

	if (getFavoriteSongIndex(user_id, song_id) != -1)
	{
		return;
	}

	m_favorite_songs[user_id].push_back(song_id);
}

void DataBase::addFavoriteAuthor(int user_id, int author_id)
{
	if (m_favorite_authors.size() <= user_id)
	{
		throw std::exception("Ошибка при добавлении любимого автора. Такого автора не существует");
	}

	if (!authorExists(author_id))
	{
		throw std::exception("Ошибка при добавлении любимого автора. Такого автора не существует");
	}

	if (getFavoriteAuthorIndex(user_id, author_id) != -1)
	{
		return;
	}

	m_favorite_authors[user_id].push_back(author_id);
}

void DataBase::addFavoriteAlbum(int user_id, int album_id)
{
	if (m_favorite_albums.size() <= user_id)
	{
		throw std::exception("Ошибка при добавлении любимого альбома. Такого альюома не существует");
	}

	if (!albumExists(album_id))
	{
		throw std::exception("Ошибка при добавлении любимого альбома. Такого альбома не существует");
	}

	if (getFavoriteAlbumIndex(user_id, album_id) != -1)
	{
		return;
	}

	m_favorite_albums[user_id].push_back(album_id);
}

const MyVector<int>& DataBase::getFavoriteSongs(int user_id) const
{
	if (m_favorite_songs.size() <= user_id)
	{
		throw std::exception("Ошибка при получении любимых песен. Такого пользователя не существует");
	}

	return m_favorite_songs[user_id];
}

const MyVector<int>& DataBase::getFavoriteAuthors(int user_id) const
{
	if (m_favorite_authors.size() <= user_id)
	{
		throw std::exception("Ошибка при получении любимых авторов. Такого пользователя не существует");
	}

	return m_favorite_authors[user_id];
}

const MyVector<int>& DataBase::getFavoriteAlbums(int user_id) const
{
	if (m_favorite_albums.size() <= user_id)
	{
		throw std::exception("Ошибка при получении любимых альбомов. Такого пользователя не существует");
	}

	return m_favorite_albums[user_id];
}

void DataBase::deleteFavoriteSong(int user_id, int song_id)
{
	if (m_favorite_songs.size() <= user_id)
	{
		throw std::exception("Ошибка при удалении любимой песни. Такого пользователя не существует");
	}

	const int index = getFavoriteSongIndex(user_id, song_id);
	if (index == -1)
	{
		throw std::exception("Ошибка при удалении любимой песни. Песня не была среди любимых");
	}

	m_favorite_songs[user_id].deleteElement(index);
}

void DataBase::deleteFavoriteAuthor(int user_id, int author_id)
{
	if (m_favorite_authors.size() <= user_id)
	{
		throw std::exception("Ошибка при удалении любимого автора. Такого пользователя не существует");
	}

	const int index = getFavoriteAuthorIndex(user_id, author_id);
	if (index == -1)
	{
		throw std::exception("Ошибка при удалении любимого альбома. Альбом не был среди любимых");
	}

	m_favorite_authors[user_id].deleteElement(index);
}

void DataBase::deleteFavoriteAlbum(int user_id, int album_id)
{
	if (m_favorite_albums.size() <= user_id)
	{
		throw std::exception("Ошибка при удалении любимого альбома. Такого пользователя не существует");
	}

	const int index = getFavoriteAlbumIndex(user_id, album_id);
	if (index == -1)
	{
		throw std::exception("Ошибка при удалении любимого альбома. Альбом не был среди любимых");
	}

	m_favorite_albums[user_id].deleteElement(index);
}

void DataBase::addUser(const std::string& name, const std::string& password)
{
	int size = m_name.size();

	for (int i = 0; i < size; ++i)
	{
		if (m_name[i] == name && m_password[i] == password)
		{
			throw std::exception("Ошибка при добавлении пользователя. Такой пользователь уже существует");
		}
	}

	m_name.push_back(name);
	m_password.push_back(password);

	m_favorite_songs.push_back({});
	m_favorite_authors.push_back({});
	m_favorite_albums.push_back({});
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

void DataBase::getUsers(const MyVector<std::string>*& names, const  MyVector<std::string>*& passwords) const
{
	names = &m_name;
	passwords = &m_password;
}

bool DataBase::userExists(const std::string& name) const
{
	for (int i = 0; i < m_name.size(); ++i)
	{
		if (m_name[i] == name)
		{
			return true;
		}
	}

	return false;
}

bool DataBase::songExists(int id) const
{
	return getSongIndex(id) != -1;
}

bool DataBase::authorExists(int id) const
{
	return getAuthorIndex(id) != -1;
}

bool DataBase::albumExists(int id) const
{
	return getAlbumIndex(id) != -1;
}

bool DataBase::albumExists(int author_id, const std::string& album_name) const
{
	for (int i = 0; i < m_albums.size(); ++i)
	{
		if (m_albums[i].m_name == album_name)
		{
			for (int j = 0; j < m_albums[i].m_authors.size(); ++j)
			{
				if (m_albums[i].m_authors[j] == author_id)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void DataBase::saveUserToTxt(const std::string& name, const std::string& password) const
{
	std::ofstream file("users.txt", std::ios::app);

	if (!file.is_open())
	{
		throw "Не удалось открыть файл.";

	}
	file << name << ' ' << password << ' ';
	file.close();
}


void DataBase::readUsersFromTxt()
{
	std::ifstream file("users.txt");

	if (!file.is_open()) { throw "Не удалось открыть файл."; }

	std::string name;
	std::string password;

	while (!file.eof())
	{
		std::getline(file, name, ' ');
		m_name.push_back(name);
		std::getline(file, password, ' ');
		m_password.push_back(password);
	}

	file.close();
}

void DataBase::saveAuthorToTxt(const std::string& name, const int& id) const
{
	std::ofstream file("authors.txt", std::ios::app);

	if (!file.is_open()) { throw "Не удалось открыть файл."; }

	file << id << ' ' << name << ' ';

	file.close();
}

void DataBase::readAuthorsFromTxt()
{
	std::ifstream file("authors.txt");

	if (!file.is_open()) { throw "Не удалось открыть файл."; }

	std::string name;
	std::string id;
	int author_id;

	Author new_author;

	while (!file.eof())
	{
		std::getline(file, id, ' ');
		try
		{
			//author_id = std::stoi(id);
		//new_author.m_id = author_id;
		} catch (...)
		{
			std::cout << "error";
		};
		std::getline(file, name, ' ');
		new_author.m_name = name;
		m_authors.push_back(new_author);
	}

	file.close();
}

int DataBase::getSongIndex(int id) const
{
	for (int i = 0; i < m_songs.size(); ++i)
	{
		if (m_songs[i].m_id == id)
		{
			return i;
		}
	}

	return -1;
}

int DataBase::getAuthorIndex(int id) const
{
	for (int i = 0; i < m_authors.size(); ++i)
	{
		if (m_authors[i].m_id == id)
		{
			return i;
		}
	}

	return -1;
}

int DataBase::getAlbumIndex(int id) const
{
	for (int i = 0; i < m_albums.size(); ++i)
	{
		if (m_albums[i].m_id == id)
		{
			return i;
		}
	}

	return -1;
}

int DataBase::getFavoriteSongIndex(int user_id, int song_id) const
{
	if (m_favorite_songs.size() <= user_id)
	{
		return -1;
	}

	const MyVector<int>& tmp_vec = m_favorite_songs[user_id];
	for (int i = 0; i < tmp_vec.size(); ++i)
	{
		if (tmp_vec[i] == song_id)
		{
			return i;
		}
	}

	return -1;
}

int DataBase::getFavoriteAuthorIndex(int user_id, int author_id) const
{
	if (m_favorite_authors.size() <= user_id)
	{
		return -1;
	}

	const MyVector<int>& tmp_vec = m_favorite_authors[user_id];
	for (int i = 0; i < tmp_vec.size(); ++i)
	{
		if (tmp_vec[i] == author_id)
		{
			return i;
		}
	}

	return -1;
}

int DataBase::getFavoriteAlbumIndex(int user_id, int album_id) const
{
	if (m_favorite_albums.size() <= user_id)
	{
		return -1;
	}

	const MyVector<int>& tmp_vec = m_favorite_albums[user_id];
	for (int i = 0; i < tmp_vec.size(); ++i)
	{
		if (tmp_vec[i] == album_id)
		{
			return i;
		}
	}

	return -1;
}



