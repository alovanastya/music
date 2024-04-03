#pragma once
#include "Menu.h"
#include "DataBase.h"
#include "IMenu.h"

//enum class Selection_2
//{
//	ADD_AUTHOR = (int)Selection::COUNT,
//	ADD_ALBUM,
//	ADD_SONG,
//	COUNT = (int)ADD_SONG - (int)Selection::COUNT + 1
//};

class AdminMenu : public IMenu
{
public:
	AdminMenu();

	AdminMenu(DataBase*, int);

	Selection showMenu() override final;

	bool addSong();

	bool addAlbum();

	bool addAuthor();

	bool show();

};