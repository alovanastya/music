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

	IMenu* menu = nullptr;
	if (user_id == 0)
	{
		menu = new AdminMenu(&database, 0);
	}
	else
	{
		menu = new Menu(&database, user_id);
	}

	bool end = false;
	while (!end)
	{
		system("cls");

		menu->printMenu();

		int selection = 0;
		std::cout << " \nВведите число: ";
		std::cin >> selection;

		Result result = menu->runSelected(selection);
		switch (result)
		{
		case (Result::DONE):
			break;

		case (Result::WITH_ERROR):
			std::cout << "Произошла ошибка!";
			break;

		case (Result::EXIT):
		{
			std::cout << "Вы уверены, что хотите выйти?\n";
			int choice = 0;
			std::cout << "1 - Да\n";
			std::cout << "2 - Нет, хочу остаться\n";
			std::cin >> choice;

			if (choice == 1) {
				std::cout << "До свидания! Хорошего дня";
				end = true;
			}

			else if (choice != 2)
			{
				std::cout << "Неизвестная команда";
			}
		}
		break;

		default:
			break;
		}
	}

	delete menu;

	return 0;
}