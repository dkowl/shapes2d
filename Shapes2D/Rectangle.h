#pragma once
#include "Shape.h"

namespace Shapes2D {
	template<typename TFloat>
	class Rectangle : public Shape<TFloat> {

	public:
		using Shape::Move;

		Rectangle(Vector2 p, TFloat a, TFloat b) :
			p(p),
			a(a),
			b(b)
		{
		}

		TFloat Area() override {
			return a*b;
		}
		TFloat Perimeter() override {
			return a * 2 + b * 2;
		}
		Vector2 CenterPosition() override {
			return p;
		}

		void Move(Vector2 v) override {
			p += v;
		}
		void Scale(TFloat x) override {
			a *= x;
			b *= x;
		}

		string Name() override {
			return "Rectangle";
		}
		ParamList Params() override {
			ParamList result = Shape::Params();
			result.emplace_back(pair<string, TFloat>{"Width", a});
			result.emplace_back(pair<string, TFloat>{"Height", b});
			return result;
		}

	private:
		Vector2 p;
		TFloat a;
		TFloat b;
	};
}
