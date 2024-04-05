#include "IMenu.h"

IMenu::IMenu(DataBase* database, int user_id)
{
	m_database = database;
	m_user_id = user_id;
}
