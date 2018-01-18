#pragma once

namespace TextUI {

	class Widget {

	protected:
		bool selectable;
		bool clickable;

	public:
		Widget(bool selectable, bool clickable) :
			selectable(selectable),
			clickable(clickable)
		{
		}

		virtual void Display() = 0;
		virtual void Select() {};
		virtual void Deselect() {};
		virtual void Click() {};

		bool IsSelectable() {
			return selectable;
		}

		bool IsClickable() {
			return clickable;
		}
	};
}