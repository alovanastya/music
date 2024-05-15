#pragma once
#include "Song.h"
#include "Album.h"
#include "Author.h"

class DataBase
{
private:
	MyVector<Song> m_songs;
	MyVector<Album> m_albums;
	MyVector<Author> m_authors;

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
	DataBase();

	int check_user(const std::string&, const std::string&) const;

	bool addSong(const Song&);

	bool operator +(const Song&);

	bool addAlbum(const Album&);

	bool operator +(const Album&);

	bool addAuthor(const Author&);

	bool operator +(const Author&);

	bool editSong(int id, const Song &);

	bool editAlbum(int id, const Album &);

	bool editAuthor(int id, const Author &);

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

	MyVector<int> sortSongsByName() const;

	MyVector<int> sortAuthorsByName() const;

	MyVector<int> sortAlbumsByName() const;

	//bool getUsers(MyVector<std::string>*&, MyVector<std::string>*&);
	
};