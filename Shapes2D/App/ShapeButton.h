#pragma once

#include "../ShapeStore.h"
#include "../TextUI/Button.h"

using namespace TextUI;
using namespace Shapes2D;

class ShapeButton : public Button {

	Shape<float>& shape;
	bool oneTimeUse;
	bool used;

public:

	ShapeButton(string text, Signal<>::Slot onClickSlot, Shape<float> &shape, bool oneTimeUse = false) :
		Button(text, onClickSlot),
		shape(shape),
		oneTimeUse(oneTimeUse),
		used(false)
	{
	}

	virtual void Display() {
		if (!used) {
			Button::Display();
			if (isSelected) {
				shape.Display();
			}
		}
	}

	virtual void Click() {
		Button::Click();
		if (oneTimeUse) {
			selectable = false;
			clickable = false;
			used = true;
		}
	}


};