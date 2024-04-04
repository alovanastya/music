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

	bool end = false;
	while (!end)
	{
		Menu menu;

		//system("cls");

		menu.printMenu();

		int selection = 0;
		std::cout << " \nВведите число: ";
		std::cin >> selection;

		Result result = menu.runSelected(selection);
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

				else if (choice == 2) {}

				else
				{
					std::cout << "Неизвестная команда";
				}
			}
				break;

			default:
				break;

			// сообщать о результате работы, а в случае EXIT делать end = True
		}
	}


	return 0;
}