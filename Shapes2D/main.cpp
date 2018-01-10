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
	auto square = MakeSquare(0.f, 0.f, 5.f);
	auto rectangle = MakeRectangle(0.f, 0.f, 3.f, 5.f);
	auto triangle = MakeTriangle(15.f, 15.f, 47.f, 40.f, 65.f, 20.f);
	auto trapezoid = MakeTrapezoid(15.f, 15.f, 47.f, 40.f, 65.f, 20.f, 5.f);


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