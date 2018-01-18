#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Vector2.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;
using std::ostream;
using std::istream;

namespace Shapes2D {
	template<typename TFloat>
	class Shape
	{
	public:
		typedef Vector2<TFloat> Vector2;
		typedef vector<pair<string, TFloat>> ParamList;

		virtual TFloat Area() = 0;
		virtual TFloat Perimeter() = 0;
		virtual Vector2 CenterPosition() = 0;

		virtual void Move(Vector2 v) = 0;
		void Move(TFloat x, TFloat y) {
			Move(Vector2(x, y));
		}

		virtual void Scale(TFloat x) = 0;

		virtual void Save(ostream &os) const = 0;
		virtual void Load(istream &is) = 0;

		virtual string Name() {
			return "Shape";
		}
		virtual ParamList Params() {
			Vector2 centerPos = CenterPosition();
			ParamList pl = { 
				{ "Area", Area() },
				{ "Perimeter", Perimeter() }, 
				{ "Center x", centerPos.x },
				{ "Center y", centerPos.y }
			};
			return pl;
		}
		void Display() {
			cout << Name() << endl;
			for (auto&& param : Params()) {
				cout << param.first << ": " << param.second << endl;
			}
			cout << endl;
		}
	};

	static const double PI = 3.14159265;

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Shape<T> &shape)
	{
		shape.Save(os);
		return os;
	}

	template<typename T>
	std::istream& operator>>(std::istream& is, Shape<T> &shape)
	{
		shape.Load(is);
		return is;
	}
}

