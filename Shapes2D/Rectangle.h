#pragma once
#include "Shape.h"

namespace Shapes2D {
	template<typename TFloat>
	class Rectangle : public Shape<TFloat> {

	public:
		using Shape::Move;

		Rectangle(Vector2 A, TFloat a, TFloat b) :
			A(A),
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
			return A;
		}

		void Move(Vector2 v) override {
			A += v;
		}
		void Scale(TFloat x) override {
			a *= x;
			b *= x;
		}

		void Save(ostream &os) const {
			os << A << " " << a << " " << b;
		}

		void Load(istream &is) {
			is >> A >> a >> b;
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
		Vector2 A;
		TFloat a;
		TFloat b;
	};

	template<typename TFloat>
	static Rectangle<TFloat> MakeRectangle(TFloat Ax, TFloat Ay, TFloat a, TFloat b) {
		return Rectangle<TFloat>(Vector2<TFloat>(Ax, Ay), a, b);
	}
}
