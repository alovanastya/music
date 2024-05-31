#pragma once
#include "Song.h"
#include "Album.h"
#include "Author.h"

#include <fstream>
#include <string>

class DataBase
{
private:
	MyVector<Song> m_songs;
	MyVector<Album> m_albums;
	MyVector<Author> m_authors;

	MyVector<MyVector<int>> m_favorite_songs;
	MyVector<MyVector<int>> m_favorite_authors;
	MyVector<MyVector<int>> m_favorite_albums;

	MyVector<std::string> m_name;
	MyVector<std::string> m_password;

	int m_new_song_id = 0;
	int m_new_album_id = 0;
	int m_new_author_id = 0;
	int m_new_user_id = 0;

public:
	DataBase();

	int check_user(const std::string&, const std::string&) const;

	void addSong(const Song&);

	void operator +(const Song&);

	void addAlbum(const Album&);

	void operator +(const Album&);

	void addAuthor(const Author&);

	void operator +(const Author&);

	void editSong(int id, const Song&);

	void editAlbum(int id, const Album&);

	void editAuthor(int id, const Author&);

	const Song& getSong(int id) const;

	const Album& getAlbum(int id) const;

	const Author& getAuthor(int id) const;

	void addFavoriteSong(int, int);

	void addFavoriteAuthor(int, int);

	void addFavoriteAlbum(int, int);

	const MyVector<int>& getFavoriteSongs(int) const;

	const MyVector<int>& getFavoriteAuthors(int) const;

	const MyVector<int>& getFavoriteAlbums(int) const;

	void deleteFavoriteSong(int, int);

	void deleteFavoriteAuthor(int, int);

	void deleteFavoriteAlbum(int, int);

	void addUser(const std::string&, const std::string&);

	const MyVector<Song>& getSongs() const;

	const MyVector<Album>& getAlbums() const;

	const MyVector<Author>& getAuthors() const;

	MyVector<int> sortSongsByName() const;

	MyVector<int> sortAuthorsByName() const;

	MyVector<int> sortAlbumsByName() const;

	void getUsers(const MyVector<std::string>*&, const MyVector<std::string>*&) const;

	bool userExists(const std::string& name) const;

	bool songExists(int) const;

	bool authorExists(int) const;

	bool albumExists(int) const;

	bool albumExists(int, const std::string&) const;

	void saveUserToTxt(const std::string&, const std::string&) const;

	void readUsersFromTxt();

	void saveAuthorToTxt(const std::string&, const int&) const;

	void readAuthorsFromTxt();

private:
	int getSongIndex(int) const;

	int getAuthorIndex(int) const;

	int getAlbumIndex(int) const;

	int getFavoriteSongIndex(int, int) const;

	int getFavoriteAuthorIndex(int, int) const;

	int getFavoriteAlbumIndex(int, int) const;



};