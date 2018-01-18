#pragma once

#include "Widget.h"
#include <iostream>

namespace TextUI {
	class Spacer : public Widget {

		int rows;

	public:
		Spacer(int rows = 1) :
			Widget(false, false),
			rows(rows)
		{
		}

		virtual void Display() {
			for (int i = 0; i < rows; i++) {
				std::cout << std::endl;
			}
		}
	};
}