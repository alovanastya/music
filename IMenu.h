#pragma once
#include "DataBase.h"

//enum class Selection
//{
//	ADD_FAVORITE_SONG = 1,
//	DELETE_FAVORITE_SONG,
//	PRINT_FAVORITE_SONG,
//	ADD_FAVORITE_AUTHOR,
//	DELETE_FAVORITE_AUTHOR,
//	PRINT_FAVORITE_AUTHOR,
//	ADD_FAVORITE_ALBUM,
//	DELETE_FAVORITE_ALBUM,
//	PRINT_FAVORITE_ALBUM,
//	ADD_AUTHOR,
//	ADD_ALBUM,
//	ADD_SONG,
//	EXIT,
//	COUNT
//};

enum class Result
{
	DONE,
	WITH_ERROR,
	EXIT,
	NOT_SUPPORTED
};

class IMenu
{
protected:
	DataBase* m_database;

	int m_user_id = 0;

	IMenu(DataBase*, int);

	IMenu();

	virtual void printMenu() const = 0;

	virtual Result runSelected(int) = 0;


};