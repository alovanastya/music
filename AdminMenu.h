#pragma once
#include "Menu.h"
#include "DataBase.h"


class AdminMenu : public Menu
{
public:
	AdminMenu(DataBase*, int);

	void printMenu() const override;

	Result runSelected(int) override;

	bool addSong();

	bool addAlbum();

	bool addAuthor();

};
