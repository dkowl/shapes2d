#pragma once
#include "Vector2.h"

namespace Shapes2D {
	template<typename T>
	T DistanceFromPointToLine(Vector2<T> P, Vector2<T> A, Vector2<T> B) {
		return
			std::abs((B.y - A.y) * P.x - (B.x - A.x) * P.y + B.x * A.y - B.y * A.x)
			/
			std::sqrt((B.y - A.y) * (B.y - A.y) + (B.x - A.x) * (B.x - A.x))
			;
	}
}