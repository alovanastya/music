#pragma once

#include <vector>
#include <string>
#include "Song.h"
#include "Album.h"
#include "Author.h"
#include <iostream>

class DataBase
{
public:
	std::vector<Song> m_songs;
	std::vector<Album> m_albums;
	std::vector<Author> m_authors;

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

	bool addSong(const Song& song);

	bool operator +(const Song&);

	bool addAlbum(const Album& new_album);

	bool addAuthor(const Author& new_author);

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

	const std::vector<Song> getSongs() const;

	const std::vector<Album> getAlbums() const;

	const std::vector<Author> getAuthors() const;
};