#pragma once
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

namespace TextUI {

	using std::map;
	using std::vector;
	using std::string;
	using std::cout;

	class MenuController {

		map<string, Menu> menus;
		string currentMenuName;

	public:
		MenuController(vector<Menu> menus, int startMenuId = 0):
			currentMenuName(menus[startMenuId].Name())
		{
			for (auto&& menu : menus) {
				this->menus[menu.Name()] = menu;
			}
		}

		void Start() {
			menus[currentMenuName].Display();
			while (true) {
				char c = getchar();
				ProcessInput(c);
			}
		}

		void ProcessInput(char c) {
			cout << c;
		}
	};
}