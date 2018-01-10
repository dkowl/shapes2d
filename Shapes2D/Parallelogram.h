#pragma once

#pragma once
#include "Shape.h"

namespace Shapes2D {
	template<typename TFloat>
	class Parallelogram : public Shape<TFloat> {

	public:
		using Shape::Move;

		Parallelogram(Vector2 A, Vector2 B, Vector2 C) :
			A(A),
			B(B),
			C(C)
		{
		}
		//Start here
		TFloat Area() override {
			return std::abs(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
		}
		TFloat Perimeter() override {
			return (A.Distance(B) + B.Distance(C)) * 2;
		}
		Vector2 CenterPosition() override {
			return A.Average(C);
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
			return "Parallelogram";
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
	};

	template<typename TFloat>
	static Parallelogram<TFloat> MakeParallelogram(TFloat Ax, TFloat Ay, TFloat Bx, TFloat By, TFloat Cx, TFloat Cy) {
		return Parallelogram<TFloat>(Vector2<TFloat>(Ax, Ay), Vector2<TFloat>(Bx, By), Vector2<TFloat>(Cx, Cy));
	}
}
