#pragma once
#include "Menu.h"

class AdminMenu : public Menu
{
public:
	AdminMenu(DataBase*, int);

	void printMenu() const override;

	Result runSelected(int) override;

	void enterAlbum(Song&, bool&);

	void chooseGenre(Song&, bool&);

	bool addSong();

	void enterAuthors(Album&, int, bool&, const MyVector<Author>&);

	bool addAlbum();

	bool addAuthor();

	void editSongsAlbum(Song&, int&, bool&, const MyVector<Album>&, int&);

	void editSongsName(Song&, int&, bool&, const MyVector<Song>&, int&);

	void enterId(Song&, int&, const MyVector<Song>&, int&);

	bool editSong();
		 
	void editAlbumsName(Album&, int&, const MyVector<Album>&, int&);

	void editAlbumsAuthors(Album&, int&, const MyVector<Author>&, int&);

	void enterAlbumsId(Album&, int&, const MyVector<Album>&, int&);

	bool editAlbum();
		 
	bool editAuthor();

	~AdminMenu() override;
};
