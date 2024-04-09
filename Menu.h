#pragma once
#include "IMenu.h"

class Menu : public IMenu {
public:

	void printMenu() const override;

	Result runSelected(int selected) override;

	bool addFavoriteSong();

	bool addFavoriteAuthor();

	bool addFavoriteAlbum();

	bool printFavoriteSongs();

	bool printFavoriteAuthors();

	bool printFavoriteAlbums();

	bool deleteFavoriteSong();

	bool deleteFavoriteAuthor();

	bool deleteFavoriteAlbum();

public:

	Menu(DataBase* database, int user_id);

	~Menu() override;
};