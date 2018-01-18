#pragma once
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <initializer_list>
#include "Menu.h"

namespace TextUI {

	using std::map;
	using std::vector;
	using std::string;
	using std::cout;
	using std::initializer_list;

	class MenuController {

		map<string, Menu> menus;
		string currentMenuName;
		bool inputArrowFlag = false;
		bool stopFlag = false;

	public:
		MenuController(vector<Menu> menus, int startMenuId = 0):
			currentMenuName(menus[startMenuId].Name())
		{
			for (auto&& menu : menus) {
				this->menus[menu.Name()] = Menu(menu);
			}
		}

		MenuController(initializer_list<Menu> initList) :
			currentMenuName(initList.begin()->Name())
		{
			for (auto&& menu : initList) {
				menus[menu.Name()] = menu;
			}
		}

		void Start() {
			menus[currentMenuName].Display();
			while (!stopFlag) {
				char c = _getch();
				ProcessInput(c);
				CurrentMenu().Display();
			}
		}

		void Stop() {
			stopFlag = true;
		}

		void SwitchMenu(string menuName) {
			currentMenuName = menuName;
		}

	private:
		void ProcessInput(char c) {
			//cout << (int)c << endl;
			if (!inputArrowFlag) {
				switch (c) {
				case -32:
					inputArrowFlag = true;
					break;
				case 13:
					CurrentMenu().Click();
					break;
				}
			}
			else {
				switch (c) {
				case 72:
					CurrentMenu().SelectPrevious();
					break;
				case 80:
					CurrentMenu().SelectNext();
					break;
				}
				inputArrowFlag = false;
			}
		}

		Menu& CurrentMenu() {
			return menus[currentMenuName];
		}
	};
}