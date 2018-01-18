#pragma once
namespace Shapes2D {
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2() { }

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

		T Distance(const Vector2 &b) {
			return (*this - b).Magnitude();
		}

		void Scale(const Vector2 &origin, const T &factor) {
			x += (x - origin.x) * (factor - 1);
			y += (y - origin.y) * (factor - 1);
		}

		Vector2 Average(const Vector2 &b) {
			return Vector2((x + b.x) / 2, (y + b.y) / 2);
		}

	};
	
	template<typename T>
	static Vector2<T> MakeVector2(T x, T y) {
		return Vector2<T>(x, y);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector2<T> &v)
	{
		os << v.x << " " << v.y;
		return os;
	}

	template<typename T>
	std::istream& operator>>(std::istream& is, Vector2<T> &v)
	{
		is >> v.x >> v.y;
		return is;
	}
}

