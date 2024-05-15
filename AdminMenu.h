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

	void printAlbums();

	bool addAuthor();

	bool editSong();

	bool editAlbum();

	bool editAuthor();

	~AdminMenu() override;

private:
	void enterAlbum(Song&, bool&);

	void chooseGenre(Song&, bool&);

	void enterAuthors(Album&, bool&, const MyVector<Author>&);

	void editSongsAlbum(Song&, int&, bool&, const MyVector<Album>&, int&);

	void editSongsName(Song&, int&, bool&, const MyVector<Song>&, int&);

	void enterId(Song&, int&, const MyVector<Song>&, int&);

	void editAlbumsName(Album&, int&, const MyVector<Album>&, int&);

	void editAlbumsAuthors(Album&, int&, const MyVector<Author>&, int&);

	void enterAlbumsId(Album&, int&, const MyVector<Album>&, int&);
};
