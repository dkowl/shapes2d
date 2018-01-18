#pragma once

#include <string>
#include <iostream>
#include "Widget.h"
#include "../Signal/Signal.h"

namespace TextUI {

	using std::string;
	using std::cout;
	using std::endl;

	class Button : public Widget {

		bool isSelected;

	public:
		Signal<> onClickSignal;
		string text;

		Button(string text, Signal<>::Slot onClickSlot) :
			Widget(true, true),
			text(text),
			isSelected(false)
		{
			onClickSignal.Connect(onClickSlot);
		}

		template<class T>
		Button(string text, T* instance, void(T::*func)(void)) :
			Widget(true, true),
			text(text),
			isSelected(false)
		{
			onClickSignal.Connect(instance, func);
		}

		virtual void Display() {
			if (isSelected) {
				cout << " --> ";
			}
			cout << text << endl;
		}

		virtual void Select() {
			isSelected = true;
		}

		virtual void Deselect() {
			isSelected = false;
		}

		virtual void Click() {
			onClickSignal.Emit();
		}

	};
}
