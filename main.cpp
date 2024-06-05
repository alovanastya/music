#include <string>
#include <iostream>
#include <limits>
#include "AdminMenu.h"


int main()
{
	setlocale(0, "RUSSIAN");

	DataBase database;

	std::string login(100, '\0');
	std::string password(100, '\0');

	try
	{
		database.readFromTxt();
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
	}
	catch (...)
	{
	}

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
			std::cout << "�������� ����� ��� ������." << std::endl;
			std::cout << "���������� ��� ���: " << std::endl;
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
		std::cout << std::endl << std::endl << "������� �����: ";

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
				std::cerr << "��������� ����������: " << exception.what() << std::endl;
				std::cerr << "������� ���������� �����: ";
			}
		}

		Result result = menu->runSelected(selection);

		switch (result)
		{
		case Result::DONE:

			break;

		case Result::WITH_ERROR:
			std::cout << "��������� ������!";
			break;

		case Result::EXIT:
			std::cout << "�� ��������! �������� ���" << std::endl;
			end = true;
			break;

		default:
			break;
		}

		std::cout << "������� ����� �������, ����� ����������";
		std::cin.get();
	}

	database.saveToTxt();

	delete menu;

	return 0;
}