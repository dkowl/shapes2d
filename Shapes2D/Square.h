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

		void Save(ostream &os) const {
			os << A << " " << a;
		}

		void Load(istream &is) {
			is >> A >> a;
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

	template<typename TFloat>
	static Square<TFloat> MakeSquare(TFloat Ax, TFloat Ay, TFloat a) {
		return Square<TFloat>(Vector2<TFloat>(Ax, Ay), a);
	}
}
