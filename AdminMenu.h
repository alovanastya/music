#pragma once
#include "Menu.h"


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
