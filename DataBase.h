#pragma once

#include <vector>
#include "MyVector.h"
#include <string>
#include "Song.h"
#include "Album.h"
#include "Author.h"
#include <iostream>

class DataBase
{
public:
	MyVector<Song> m_songs;
	MyVector<Album> m_albums;
	MyVector<Author> m_authors;

private:
	std::vector<std::vector<int>> m_favorite_songs = { {} };
	std::vector<std::vector<int>> m_favorite_authors = { {} };
	std::vector<std::vector<int>> m_favorite_albums = { {} };

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

	//std::istream& operator >> (std::istream&);

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

	bool getFavoriteSongs(int, const std::vector<int>*&) const;

	bool getFavoriteAuthors(int, const std::vector<int>*&) const;

	bool getFavoriteAlbums(int, const std::vector<int>*&) const;

	bool deleteFavoriteSong(int, int);

	bool deleteFavoriteAuthor(int, int);

	bool deleteFavoriteAlbum(int, int);

	bool addUser(const std::string&, const std::string&);

	const MyVector<Song> getSongs() const;
			
	const MyVector<Album> getAlbums() const;
			
	const MyVector<Author> getAuthors() const;
};