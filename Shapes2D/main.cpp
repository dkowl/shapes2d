#include "Shapes2D.h"

using namespace Shapes2D;

int main() {
	Square<float> square(Vector2<float>(0, 0), 5);
	square.Display();
	square.Move(5, 5);
	square.Scale(3);
	square.Display();

	system("PAUSE");
	return 0;
}