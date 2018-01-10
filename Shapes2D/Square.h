#pragma once
#include "Shape.h"

namespace Shapes2D {
	template<typename TFloat>
	class Square : public Shape<TFloat> {

	public:
		using Shape::Move;

		Square(Vector2 p, TFloat a) :
			p(p),
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
			return p;
		}

		void Move(Vector2 v) override {
			p += v;
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
		Vector2 p;
		TFloat a;
	};
}
