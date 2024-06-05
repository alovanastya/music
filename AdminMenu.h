#pragma once
#include "Menu.h"

class AdminMenu : public Menu
{
public:
	AdminMenu(DataBase*, int);

	void printMenu() const override;

	Result runSelected(int) override;

	void addSong();

	void addAlbum();

	void addAuthor();

	void editSong();

	void editAlbum();

	void editAuthor();

	~AdminMenu() override;

private:
	void editSongsAlbum(Song&) const;

	void editSongsName(Song&) const;

	void editSongsGenre(Song&) const;

	void editAlbumsName(Album&) const;

	void editAlbumsAuthors(Album&) const;
};
