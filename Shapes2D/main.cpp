#include "ShapeStore.h"
#include "Signal\Signal.h"
#include "TextUI\MenuController.h"
#include "TextUI\Button.h"

using namespace Shapes2D;
using namespace TextUI;

void TestShape(Shape<float> &shape) {
	shape.Display();
	shape.Move(5, 5);
	shape.Display();
	shape.Scale(3);
	shape.Display();
}

class App {

	MenuController menuController;
	ShapeStore<float> shapeStore;

public:

	App() :
		menuController{
		Menu(
			"Main",
			Menu::WidgetList{
				shared_ptr<Widget>(new Button("Add Shape",  [=]() {GoToMenu("Add Shape"); })),
				shared_ptr<Widget>(new Button("Display Shapes", [=]() {DisplayShapes(); })),
				shared_ptr<Widget>(new Button("Exit", [=]() {Stop(); }))
			}
		),
		Menu(
			"Add Shape",
			Menu::WidgetList{
				shared_ptr<Widget>(new Button("Square", [=]() {AddShape(SQUARE); })),
				shared_ptr<Widget>(new Button("Rectangle", [=]() {AddShape(RECTANGLE); })),
				shared_ptr<Widget>(new Button("Triangle", [=]() {AddShape(TRIANGLE); })),
				shared_ptr<Widget>(new Button("Trapezoid", [=]() {AddShape(TRAPEZOID); })),
				shared_ptr<Widget>(new Button("Parallelogram", [=]() {AddShape(PARALLELOGRAM); })),
				shared_ptr<Widget>(new Button("Circle", [=]() {AddShape(CIRCLE); })),
				shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })),
			}
		),
		}
	{
	}

	void Start() {
		menuController.Start();
	}

	void Stop() {
		menuController.Stop();
	}

	void GoToMenu(string menuName) {
		menuController.SwitchMenu(menuName);
	}

	void AddShape(ShapeType type) {
		shapeStore.AddShape(type);
	}

	void DisplayShapes() {
		shapeStore.DisplayShapes();
		system("PAUSE");
	}
};

int main() {

	App app;
	app.Start();

	return 0;
}