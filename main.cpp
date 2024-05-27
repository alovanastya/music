#include <string>
#include <iostream>
#include <limits>
#include "AdminMenu.h"


int main()
{
	setlocale(0, "RUSSIAN");
	/*
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
		std::cout << std::endl << std::endl << "Введите число: ";

		bool error = true;
		std::string string_selection;

		while (error)
		{
			try
			{
				error = false;
				std::cin >> string_selection;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				selection = stoi(string_selection);
			}

			catch (std::exception& exception)
			{
				error = true;
				std::cerr << "Пойманное исключение: " << exception.what() << std::endl;
				std::cerr << "Введите корректное число: ";
			}
		}

		Result result = menu->runSelected(selection);

		switch (result)
		{
		case Result::DONE:

			break;

		case Result::WITH_ERROR:
			std::cout << "Произошла ошибка!";
			break;

		case Result::EXIT:
			std::cout << "До свидания! Хорошего дня";
			end = true;
			break;

		default:
			break;
		}

		std::cout << "Нажмите любую клавишу, чтобы продолжить";
		std::cin.get();
	}
	*/



	//MyVector<int> vector(3, 5);
	//vector.push_back(7);

	//for (auto&& i : vector)
	//{
	//	std::cout << i;
	//}



	//delete menu;

	return 0;
}