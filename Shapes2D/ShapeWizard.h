#pragma once
#include "Shapes2D.h"
#include <iostream>

using std::cin;

namespace Shapes2D {

	enum ShapeType {
		SQUARE,
		RECTANGLE,
		TRIANGLE,
		TRAPEZOID,
		PARALLELOGRAM,
		CIRCLE
	};

	template<typename TFloat>
	class ShapeWizard {

		template<typename TFloat>
		friend class ShapeStore;

		static Shape<TFloat>* CreateShape(ShapeType shapeType) {

			cout << "Creating Shape" << endl;

			Shape<TFloat> *result;
			switch (shapeType) {
			case SQUARE:
				result = CreateSquare();
				break;
			case RECTANGLE:
				result = CreateRectangle();
				break;
			case TRIANGLE:
				result = CreateTriangle();
				break;
			case TRAPEZOID:
				result = CreateTrapezoid();
				break;
			case PARALLELOGRAM:
				result = CreateParallelogram();
				break;
			case CIRCLE:
				result = CreateCircle();
				break;
			default:
				result = CreateSquare();
				break;
			}

			result->Display();
			return result;
		}

		static Shape<TFloat>* CreateSquare() {
			TFloat
				Ax,
				Ay,
				a;
			cout << "Point A - x coordinate: ";
			cin >> Ax;
			cout << "Point A - y coordinate: ";
			cin >> Ay;
			cout << "Side length a: ";
			cin >> a;
			return new Square<TFloat>(MakeVector2(Ax, Ay), a);
		}

		static Shape<TFloat>* CreateRectangle() {
			TFloat
				Ax,	Ay,
				a,
				b;
			cout << "Point A - x coordinate: ";
			cin >> Ax;
			cout << "Point A - y coordinate: ";
			cin >> Ay;
			cout << "Side length a: ";
			cin >> a;
			cout << "Side length b: ";
			cin >> b;
			return new Rectangle<TFloat>(MakeVector2(Ax, Ay), a, b);
		}

		static Shape<TFloat>* CreateTriangle() {
			TFloat
				Ax, Ay,
				Bx, By,
				Cx, Cy;
			cout << "Point A - x coordinate: ";
			cin >> Ax;
			cout << "Point A - y coordinate: ";
			cin >> Ay;
			cout << "Point B - x coordinate: ";
			cin >> Bx;
			cout << "Point B - y coordinate: ";
			cin >> By;
			cout << "Point C - x coordinate: ";
			cin >> Cx;
			cout << "Point C - y coordinate: ";
			cin >> Cy;
			return new Triangle<TFloat>(MakeVector2(Ax, Ay), MakeVector2(Bx, By), MakeVector2(Cx, Cy));
		}

		static Shape<TFloat>* CreateTrapezoid() {
			TFloat
				Ax, Ay,
				Bx, By,
				Cx, Cy,
				a;
			cout << "Point A - x coordinate: ";
			cin >> Ax;
			cout << "Point A - y coordinate: ";
			cin >> Ay;
			cout << "Point B - x coordinate: ";
			cin >> Bx;
			cout << "Point B - y coordinate: ";
			cin >> By;
			cout << "Point C - x coordinate: ";
			cin >> Cx;
			cout << "Point C - y coordinate: ";
			cin >> Cy;
			cout << "Side length a: ";
			cin >> a;
			return new Trapezoid<TFloat>(MakeVector2(Ax, Ay), MakeVector2(Bx, By), MakeVector2(Cx, Cy), a);
		}

		static Shape<TFloat>* CreateParallelogram() {
			TFloat
				Ax, Ay,
				Bx, By,
				Cx, Cy;
			cout << "Point A - x coordinate: ";
			cin >> Ax;
			cout << "Point A - y coordinate: ";
			cin >> Ay;
			cout << "Point B - x coordinate: ";
			cin >> Bx;
			cout << "Point B - y coordinate: ";
			cin >> By;
			cout << "Point C - x coordinate: ";
			cin >> Cx;
			cout << "Point C - y coordinate: ";
			cin >> Cy;
			return new Parallelogram<TFloat>(MakeVector2(Ax, Ay), MakeVector2(Bx, By), MakeVector2(Cx, Cy));
		}

		static Shape<TFloat>* CreateCircle() {
			TFloat
				Ox,
				Oy,
				r;
			cout << "Point O - x coordinate: ";
			cin >> Ox;
			cout << "Point O - y coordinate: ";
			cin >> Oy;
			cout << "Radius r: ";
			cin >> r;
			return new Circle<TFloat>(MakeVector2(Ox, Oy), r);
		}
		
	};
}