#pragma once
#include "Song.h"
#include "Album.h"
#include "Author.h"

class DataBase
{
public:
	// TODO: перенести в private
	MyVector<Song> m_songs;
	MyVector<Album> m_albums;
	MyVector<Author> m_authors;

private:
	MyVector<MyVector<int>> m_favorite_songs;
	MyVector<MyVector<int>> m_favorite_authors;
	MyVector<MyVector<int>> m_favorite_albums;

	std::vector<std::string> m_name = { "admin" };
	std::vector<std::string> m_password = { "admin" };

	int m_new_song_id = 0;
	int m_new_album_id = 0;
	int m_new_author_id = 0;
	int m_new_user_id = 0;

public:
	DataBase()
	{}

	int check_user(const std::string&, const std::string&) const;

	bool addSong(const Song&);

	bool operator +(const Song&);

	bool addAlbum(const Album&);

	bool operator +(const Album&);

	bool addAuthor(const Author&);

	bool operator +(const Author&);

	bool editSong(int id, Song*);

	bool editAlbum(int id, Album*);

	bool editAuthor(int id, Author*);

	bool getSong(int id, const Song*&) const;

	bool getAlbum(int id, const Album*&) const;

	bool getAuthor(int id, const Author*&) const;

	bool addFavoriteSong(int, int);

	bool addFavoriteAuthor(int, int);

	bool addFavoriteAlbum(int, int);

	bool getFavoriteSongs(int, const MyVector<int>*&) const;

	bool getFavoriteAuthors(int, const MyVector<int>*&) const;

	bool getFavoriteAlbums(int, const MyVector<int>*&) const;

	bool deleteFavoriteSong(int, int);

	bool deleteFavoriteAuthor(int, int);

	bool deleteFavoriteAlbum(int, int);

	bool addUser(const std::string&, const std::string&);

	const MyVector<Song> &getSongs() const;

	const MyVector<Album> &getAlbums() const;

	const MyVector<Author> &getAuthors() const;

	MyVector<int> sortSongsByName() const
	{
		// TODO:
		// 1) не редактировать содержимое вектора m_songs,
		// 2) возвращать вектор с id песен, отсортированных по навазнию
		// 3) нельзя создавать копию m_songs
		// 4) нужно создать массив с id

		// Найти минимальное имя среди всех, записать первым элементом результата
		// найти минимальное имся среди оставшихся, записать вторым элементом результата
		// и т.д.


		// оставшиеся это те песни, для которых в этом векторе записан false
		MyVector<bool> need_ignore(false, m_songs.size());

		//MyVector<Song> tmp_vector = m_database->getSongs();
		//
		//Song song;
		//for (int i = 0; i < tmp_vectors.size(); ++i)
		//{
		//	for (int j = 0; tmp_vector.size() - i - 1; ++j)
		//	{
		//		if (tmp_vector[j] > tmp_vector[j + 1])
		//		{
		//			song = tmp_vectors[j + 1];
		//			tmp_vector[j + 1] = tmp_vector[j];
		//			tmp_vector[j] = song;
		//		}
		//	}
		//}
	}
};