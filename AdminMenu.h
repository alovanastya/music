#pragma once
#include "Menu.h"
#include "DataBase.h"
#include "Menu.h"


class AdminMenu : public Menu
{
public:
	AdminMenu();

	AdminMenu(DataBase*, int);

	void printMenu();

	Result runSelected(int) override;

	bool addSong();

	bool addAlbum();

	bool addAuthor();



};