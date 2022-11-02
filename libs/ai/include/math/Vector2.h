#pragma once
#include <math.h>
#include <iostream>

struct Vector2 {
	float x, y;

	Vector2 Normalize() {
		float ls = x * x + y * y;
		float invNorm = 1.0f / (float)sqrt((double)ls);
		return Vector2(x* invNorm, y * invNorm);
	}

	friend constexpr Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
	friend constexpr Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }
	friend constexpr Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
	friend constexpr Vector2 operator*(const Vector2& lhs, const float value) { return Vector2(lhs.x * value, lhs.y * value); }
	friend constexpr Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x / rhs.x, lhs.y / rhs.y); }
	friend constexpr bool operator==(const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	friend constexpr bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); }
	friend std::ostream& operator<<(std::ostream& out, const Vector2& value) { return out << "(" << value.x << ", " << value.y << ")\n"; }
};