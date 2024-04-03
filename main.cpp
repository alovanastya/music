#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "Menu.h"
#include "AdminMenu.h"



int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	DataBase database;

	std::string login(100, '\0');
	std::string password(100, '\0');

	int user_id = -1;

	while (user_id == -1)
	{
		std::cout << "Login: ";
		std::cin >> login;

		std::cout << "Password: ";
		std::cin >> password;

		user_id = database.check_user(login, password);
	}

	Menu menu(&database, user_id);

	bool end = false;
	while (!end)
	{
		system("cls");
		end = menu.show();
	}

	if (user_id == 0) 
	{
		AdminMenu admin_menu(&database, user_id);

		admin_menu.show();
	}

	return 0;
}