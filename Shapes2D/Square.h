#pragma once
#include "Shape.h"

namespace Shapes2D {
	template<typename TFloat>
	class Square : public Shape<TFloat> {

	public:
		using Shape::Move;

		Square(Vector2 A, TFloat a) :
			A(A),
			a(a)
		{
		}

		TFloat Area() override {
			return a*a;
		}
		TFloat Perimeter() override {
			return a * 4;
		}
		Vector2 CenterPosition() override {
			return A;
		}

		void Move(Vector2 v) override {
			A += v;
		}
		void Scale(TFloat x) override {
			a *= x;
		}

		string Name() override {
			return "Square";
		}
		ParamList Params() override {
			ParamList result = Shape::Params();
			result.emplace_back(pair<string, TFloat>{"Side Length", a});
			return result;
		}

	private:
		Vector2 A;
		TFloat a;
	};
}
