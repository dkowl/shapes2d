#include "Shapes2D.h"

using namespace Shapes2D;

void TestShape(Shape<float> &shape) {
	shape.Display();
	shape.Move(5, 5);
	shape.Display();
	shape.Scale(3);
	shape.Display();
}

int main() {
	Square<float> square = Square<float>(Vector2<float>(0, 0), 5);
	Rectangle<float> rectangle = Rectangle<float>(Vector2<float>(0, 0), 3, 5);
	Triangle<float> triangle = Triangle<float>(Vector2<float>(15, 15), Vector2<float>(47, 40), Vector2<float>(65, 20));
	Trapezoid<float> trapezoid = Trapezoid<float>(Vector2<float>(15, 15), Vector2<float>(47, 40), Vector2<float>(65, 20), 5);


	vector<Shape<float>*> shapes;
	shapes.push_back(&square);
	shapes.push_back(&rectangle);
	shapes.push_back(&triangle);
	shapes.push_back(&trapezoid);


	for (auto& shape : shapes) {
		TestShape(*shape);
	}

	system("PAUSE");
	return 0;
}