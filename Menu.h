#pragma once
#include "IMenu.h"

class Menu : public IMenu {
public:

	void printMenu() const override;

	Result runSelected(int selected) override;

	int inputInt() const;

	void addUser();

	void addFavoriteSong();

	void addFavoriteAuthor();

	void addFavoriteAlbum();

	void printFavoriteSongs() const;

	void printFavoriteAuthors() const;

	void printFavoriteAlbums() const;

	void deleteFavoriteSong();

	void deleteFavoriteAuthor();

	void deleteFavoriteAlbum();

	void printSongs() const;

	void printAlbums() const;

	void printAuthors() const;

	void sortSongsByName() const;

	void sortAlbumsByName() const;

	void sortAuthorsByName() const;

public:

	Menu(DataBase* database, int user_id);

	~Menu() override;
};