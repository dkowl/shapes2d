#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../List.h"
#include "Widget.h"

namespace TextUI {

	using std::shared_ptr;

	class Menu {

	public:
		typedef List<shared_ptr<Widget>> WidgetList;

	private:
		std::string name;
		WidgetList widgets;
		bool isSelectable;
		WidgetList::Iterator selectedIter;

	public:
		Menu() :
			Menu("New Menu", WidgetList())
		{
		}

		Menu(std::string name, WidgetList widgets) :
			name(name),
			widgets(widgets),
			isSelectable(false),
			selectedIter(this->widgets.begin())
		{ 
			cout << "lul";
			for (auto i = widgets.begin(); i != widgets.end(); i++) {
				if ((*i)->IsSelectable()) {
					selectedIter = i;
					isSelectable = true;
				}
			}
		}

		void SelectNext() {
			if (isSelectable) {
				auto i = selectedIter;
				i++;
				for (; i != selectedIter; i++) {
					if ((*i)->IsSelectable()) {
						Select(i);
					}
				}
			}
		}

		void SelectPrevious() {
			if (isSelectable) {
				auto i = selectedIter;
				i--;
				for (; i != selectedIter; i--) {
					if ((*i)->IsSelectable()) {
						Select(i);
					}
				}
			}
		}

		void Click() {
			if (isSelectable && (*selectedIter)->IsClickable()) {
				(*selectedIter)->Click();
			}
		}

		void Display() {
			system("cls");
			for (auto&& widget : widgets) {
				widget->Display();
			}
		}

		std::string Name() {
			return name;
		}

	private:
		void Select(WidgetList::Iterator iter) {
			(*selectedIter)->Deselect();
			(*iter)->Select();
			selectedIter = iter;
		}
	};
}