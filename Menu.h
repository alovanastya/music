#pragma once
#include "DataBase.h"
#include "IMenu.h"
#include <string>
#include <iostream>

//enum class Selection
//{
//	ADD_FAVORITE_SONG = 1,
//	DELETE_FAVORITE_SONG,
//	PRINT_FAVORITE_SONG,
//	EXIT,
//	COUNT
//};

// TODO: сделать абстрактный класс Imenu - родитель Menu

class Menu : public IMenu {
protected:

	Selection showMenu() override final;

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

	Menu();

	Menu(DataBase* database, int user_id);

	virtual bool show();
};