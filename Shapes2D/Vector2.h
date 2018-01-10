#pragma once
namespace Shapes2D {
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2(T x, T y) :
			x(x),
			y(y)
		{
		}

		Vector2 operator +(const Vector2 &b){
			return Vector2(x + b.x, y + b.y);
		}

		Vector2& operator +=(const Vector2 &b) {
			x += b.x;
			y += b.y;
			return *this;
		}

		Vector2 operator -(const Vector2 &b){
			return Vector2(x - b.x, y - b.y);
		}

		Vector2& operator -=(const Vector2 &b) {
			x -= b.x;
			y -= b.y;
			return *this;
		}

		T Magnitude() {
			return std::sqrt(x*x + y*y);
		}

		T Distance(Vector2 b) {
			return (*this - b).Magnitude();
		}

		void Scale(Vector2 origin, T factor) {
			x += (x - origin.x) * (factor - 1);
			y += (y - origin.y) * (factor - 1);
		}
	};
}

