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

		Signal<> onClickSignal;
		string text;
		bool isSelected;

	public:
		Button(string text, Signal<>::Slot onClickSlot) :
			Widget(true, true),
			text(text),
			isSelected(false)
		{
			onClickSignal.Connect(onClickSlot);
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
