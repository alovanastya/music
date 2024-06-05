#pragma once
#include "DataBase.h"
#include <exception>

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

public:
	virtual void printMenu() const = 0;

	virtual Result runSelected(int) = 0;

	virtual ~IMenu();
};