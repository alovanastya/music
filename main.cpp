#include <string>
#include <iostream>
#include <windows.h>
#include "AdminMenu.h"


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


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
		std::getline(std::cin, login);

		std::cout << "Password: ";
		std::getline(std::cin, password);

		user_id = database.check_user(login, password);

		if (user_id == -1)
		{
			std::cout << "Неверный логин или пароль." << std::endl;
			std::cout << "Попробуйте еще раз: " << std::endl;
		}
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

		bool success = false;
		bool error = false;

		std::string string_selection;

		while (!success)
		{
			try
			{
				std::cin >> string_selection;
				selection = stoi(string_selection);
			}

			catch (std::exception& exception)
			{
				std::cerr << "Пойманное исключение: " << exception.what() << std::endl;
				error = true;
				std::cerr << "Введите корректное число: ";
			}

			if (!error)
			{
				std::cin.ignore();
				success = true;
			}

			error = false;
		}

		//std::cin.ignore();

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

			bool f = false;

			while (f == false)
			{
				std::cin >> choice;

				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(INT64_MAX, '\n');
					std::cout << "Пожалуйста, введите корректное число: ";
				}

				else
				{
					f = true;
				}
			}

			if (choice == 1) {
				std::cout << "До свидания! Хорошего дня";
				//exit(0);
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