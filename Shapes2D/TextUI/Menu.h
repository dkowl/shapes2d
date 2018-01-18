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
		WidgetList::Iterator<> selectedIter;

	public:
		Menu() :
			Menu("New Menu", WidgetList())
		{
		}

		Menu(std::string name, const WidgetList &widgetList) :
			name(name),
			widgets(widgetList),
			isSelectable(false),
			selectedIter(widgets.begin())
		{ 
			for (auto i = widgets.begin(); i != widgets.end(); i++) {
				if ((*i)->IsSelectable()) {
					Select(i);
					isSelectable = true;
					break;
				}
			}
		}

		Menu(Menu const &other) :
			Menu(other.name, other.widgets)
		{
		}

		Menu& operator=(Menu const &other) {
			name = other.name;
			widgets = other.widgets;
			isSelectable = false;
			selectedIter = widgets.begin();
			for (auto i = widgets.begin(); i != widgets.end(); i++) {
				if ((*i)->IsSelectable()) {
					Select(i);
					isSelectable = true;
					break;
				}
			}
			return *this;
		}

		void SelectNext() {
			if (isSelectable) {
				auto i = selectedIter;
				i++;
				for (; i != widgets.end(); i++) {
					if ((*i)->IsSelectable()) {
						Select(i);
						break;
					}
				}
			}
		}

		void SelectPrevious() {
			if (isSelectable) {
				auto i = selectedIter;
				i--;
				for (; ; i--) {
					if ((*i)->IsSelectable()) {
						Select(i);
						break;
					}
					if (i == widgets.begin()) break;
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

		std::string Name() const {
			return name;
		}

	private:
		void Select(WidgetList::Iterator<> iter) {
			(*selectedIter)->Deselect();
			(*iter)->Select();
			selectedIter = iter;
		}
	};
}