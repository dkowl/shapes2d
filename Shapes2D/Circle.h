#pragma once
#include "Shape.h"
#include <math.h>

namespace Shapes2D {
	template<typename TFloat>
	class Circle : public Shape<TFloat> {

	public:
		using Shape::Move;

		Circle() {}

		Circle(Vector2 O, TFloat r) :
			O(O),
			r(r)
		{
		}

		TFloat Area() override {
			return  r * r * (TFloat)PI;
		}
		TFloat Perimeter() override {
			return 2 * (TFloat)PI * r;
		}
		Vector2 CenterPosition() override {
			return O;
		}

		void Move(Vector2 v) override {
			O += v;
		}
		void Scale(TFloat x) override {
			r *= x;
		}

		void Save(ostream &os) const {
			os << O << " " << r << " ";
		}

		void Load(istream &is) {
			is >> O >> r;
		}

		string Name() override {
			return "Circle";
		}
		ParamList Params() override {
			ParamList result = Shape::Params();
			result.emplace_back(pair<string, TFloat>{"Radius", r});
			return result;
		}

	private:
		Vector2 O;
		TFloat r;
	};

	template<typename TFloat>
	static Circle<TFloat> MakeCircle(TFloat Ox, TFloat Oy, TFloat r) {
		return Circle<TFloat>(Vector2<TFloat>(Ox, Oy), r);
	}
}