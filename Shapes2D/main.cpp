#include "ShapeStore.h"
#include "Signal\Signal.h"
#include "TextUI\MenuController.h"
#include "TextUI\Button.h"
#include "App\ShapeButton.h"
#include <fstream>
#include <experimental/filesystem>

using namespace Shapes2D;
using namespace TextUI;
namespace fs = std::experimental::filesystem::v1;

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
	static const string saveDirectory;
	static const string saveExtension;
	string currentSaveFilename;

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
				shared_ptr<Widget>(new Button("Move", [=]() {GoToMoveMenu(); })),
				shared_ptr<Widget>(new Button("Scale", [=]() {GoToScaleMenu(); })),
				shared_ptr<Widget>(new Button("Save", [=]() {Save(); })),
				shared_ptr<Widget>(new Button("Save As", [=]() {SaveAs(); })),
				shared_ptr<Widget>(new Button("Load", [=]() {Load(); })),
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

	void GoToMoveMenu() {
		Menu::WidgetList widgetList;
		for (auto&& shape : shapeStore.GetShapeList()) {
			widgetList.Add(shared_ptr<Widget>(new ShapeButton(shape.shape->Name(), [=]() {
				float x, y;
				cout << "Move vector - x coordinate: ";
				cin >> x;
				cout << "Move vector - y coordinate: ";
				cin >> y;
				shapeStore.MoveShape(shape, MakeVector2<float>(x, y)); 
			}, *(shape.shape), false)));
		}
		widgetList.Add(shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })));
		Menu menu("Move", widgetList);
		menuController.AddOrReplaceMenu(menu);
		menuController.SwitchMenu("Move");
	}

	void GoToScaleMenu() {
		Menu::WidgetList widgetList;
		for (auto&& shape : shapeStore.GetShapeList()) {
			widgetList.Add(shared_ptr<Widget>(new ShapeButton(shape.shape->Name(), [=]() {
				float x;
				cout << "Scale factor: ";
				cin >> x;
				shapeStore.ScaleShape(shape, x);
			}, *(shape.shape), false)));
		}
		widgetList.Add(shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })));
		Menu menu("Move", widgetList);
		menuController.AddOrReplaceMenu(menu);
		menuController.SwitchMenu("Move");
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

	void Save() {
		if (!currentSaveFilename.empty()) {
			Save(currentSaveFilename);
		}
		else {
			SaveAs();
		}
	}

	void SaveAs() {
		Menu::WidgetList widgetList;
		for (auto&& entry : fs::directory_iterator(saveDirectory)) {
			if (fs::is_regular_file(entry) && entry.path().extension().string() == saveExtension) {
				widgetList.Add(shared_ptr<Widget>(new Button(entry.path().filename().string(), [=]() { Save(entry.path().filename().string()); })));
			}
		}
		widgetList.Add(shared_ptr<Widget>(new Button("New save", [=]() { SaveAsNew();})));
		widgetList.Add(shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })));
		Menu menu("Save As", widgetList);
		menuController.AddOrReplaceMenu(menu);
		menuController.SwitchMenu("Save As");
	}

	void SaveAsNew() {
		cout << "Save name: ";
		cin >> currentSaveFilename;
		cout << endl;
		Save();
	}

	void Save(string filename) {
		//cout << CurrentSavePath();
		fs::create_directory(saveDirectory);
		std::ofstream file(CurrentSavePath(), std::ofstream::trunc);
		if (file.good()) {
			shapeStore.Save(file);
			cout << "Save successfull\n";
			system("PAUSE");
			GoToMenu("Main");
		}
		else {
			cout << "Bad file\n";
			system("PAUSE");
		}
		file.close();
	}

	void Load() {
		Menu::WidgetList widgetList;
		for (auto&& entry : fs::directory_iterator(saveDirectory)) {
			if (fs::is_regular_file(entry) && entry.path().extension().string() == saveExtension) {
				widgetList.Add(shared_ptr<Widget>(new Button(entry.path().filename().string(), [=]() { Load(entry.path().filename().string()); })));
			}
		}
		widgetList.Add(shared_ptr<Widget>(new Button("Back to Main Menu", [=]() {GoToMenu("Main"); })));
		Menu menu("Load", widgetList);
		menuController.AddOrReplaceMenu(menu);
		menuController.SwitchMenu("Load");
	}

	void Load(string filename) {
		std::ifstream file(saveDirectory + filename);
		if (file.good()) {
			shapeStore.Load(file);
			cout << "Load successfull\n";
			system("PAUSE");
			GoToMenu("Main");
		}
		else {
			cout << "Bad file\n";
			system("PAUSE");
		}
		file.close();
	}

private:
	string CurrentSavePath() {
		return SavePath(currentSaveFilename);
	}

	string SavePath(string filename) {
		return saveDirectory + filename + saveExtension;
	}
};

const string App::saveDirectory = "Saves/";
const string App::saveExtension = ".shapes2d";

int main() {

	App app;
	app.Start();

	return 0;
}