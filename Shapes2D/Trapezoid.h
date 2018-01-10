#pragma once
#pragma once
#include "Shape.h"
#include "Utils.h"

namespace Shapes2D {
	template<typename TFloat>
	class Trapezoid : public Shape<TFloat> {

	public:
		using Shape::Move;

		Trapezoid(Vector2 A, Vector2 B, Vector2 C, TFloat a) :
			A(A),
			B(B),
			C(C),
			a(a)
		{
		}

		TFloat Area() override {
			return ((a + A.Distance(B)) / 2) * Height();
		}
		TFloat Perimeter() override {
			return A.Distance(B) + B.Distance(C) * 2 + a;
		}
		Vector2 CenterPosition() override {
			return Vector2((A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3);
		}
		TFloat Height() {
			return DistanceFromPointToLine(C, A, B);
		}

		void Move(Vector2 v) override {
			A += v;
			B += v;
			C += v;
		}
		void Scale(TFloat x) override {
			Vector2 center = CenterPosition();
			A.Scale(center, x);
			B.Scale(center, x);
			C.Scale(center, x);
		}

		string Name() override {
			return "Triangle";
		}
		ParamList Params() override {
			ParamList result = Shape::Params();
			result.emplace_back(pair<string, TFloat>{"Point A x", A.x});
			result.emplace_back(pair<string, TFloat>{"Point A y", A.y});
			result.emplace_back(pair<string, TFloat>{"Point B x", B.x});
			result.emplace_back(pair<string, TFloat>{"Point B y", B.y});
			result.emplace_back(pair<string, TFloat>{"Point C x", C.x});
			result.emplace_back(pair<string, TFloat>{"Point C y", C.y});
			return result;
		}

	private:
		Vector2 A;
		Vector2 B;
		Vector2 C;
		TFloat a;
	};
}