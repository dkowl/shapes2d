#pragma once

namespace TextUI {

	class Widget {

	private:
		bool selectable;
		bool clickable;

	public:
		Widget(bool selectable, bool clickable) :
			selectable(selectable),
			clickable(clickable)
		{
		}

		virtual void Display() = 0;
		virtual void Select() = 0;
		virtual void Deselect() = 0;
		virtual void Click() = 0;

		bool IsSelectable() {
			return selectable;
		}

		bool IsClickable() {
			return clickable;
		}
	};
}