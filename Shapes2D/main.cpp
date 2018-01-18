#include "ShapeStore.h"
#include "Signal\Signal.h"
#include "TextUI\MenuController.h"
#include "TextUI\Button.h"
#include "App\ShapeButton.h"

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
				shared_ptr<Widget>(new Button("Add",  [=]() {GoToMenu("Add Shape"); })),
				shared_ptr<Widget>(new Button("Delete",  [=]() {GoToDeleteMenu(); })),
				shared_ptr<Widget>(new Button("Display", [=]() {DisplayShapes(); })),
				shared_ptr<Widget>(new Button("Display Selected", [=]() {GoToMenu("Display Selected"); })),
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
		Menu(
			"Display Selected",
			Menu::WidgetList{
				shared_ptr<Widget>(new Button("Squares", [=]() {DisplayShapes(SQUARE); })),
				shared_ptr<Widget>(new Button("Rectangles", [=]() {DisplayShapes(RECTANGLE); })),
				shared_ptr<Widget>(new Button("Triangles", [=]() {DisplayShapes(TRIANGLE); })),
				shared_ptr<Widget>(new Button("Trapezoids", [=]() {DisplayShapes(TRAPEZOID); })),
				shared_ptr<Widget>(new Button("Parallelograms", [=]() {DisplayShapes(PARALLELOGRAM); })),
				shared_ptr<Widget>(new Button("Circles", [=]() {DisplayShapes(CIRCLE); })),
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

	void GoToDeleteMenu() {
		Menu::WidgetList widgetList;
		for (auto&& shape : shapeStore.GetShapeList()) {
			widgetList.Add(shared_ptr<Widget>(new ShapeButton(shape.shape->Name(), [=]() {shapeStore.DeleteShape(shape); }, *(shape.shape), true)));
		}
		widgetList.Add(shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })));
		Menu menu("Delete", widgetList);
		menuController.AddOrReplaceMenu(menu);
		menuController.SwitchMenu("Delete");
	}

	void AddShape(ShapeType type) {
		shapeStore.AddShape(type);
	}

	void DisplayShapes() {
		cout << endl;
		shapeStore.DisplayShapes();
		system("PAUSE");
	}

	void DisplayShapes(ShapeType type) {
		cout << endl;
		shapeStore.DisplayShapes(type);
		system("PAUSE");
	}
};

int main() {

	App app;
	app.Start();

	return 0;
}