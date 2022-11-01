#pragma once

struct Vector2 {
	float x, y;

	friend constexpr Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); };
	friend constexpr Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); };
	friend constexpr Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); };
	friend constexpr Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x / rhs.x, lhs.y / rhs.y); };
	friend constexpr bool operator==(const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };
	friend constexpr bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); };
};