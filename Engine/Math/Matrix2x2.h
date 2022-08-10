#pragma once
#include "Vector2.h"


namespace neu
{
	struct Matrix2x2
	{
		Vector2 rows[2];

		Matrix2x2() = default;
		~Matrix2x2() = default;

		Matrix2x2(const Vector2& r1, const Vector2& r2);

		Vector2 operator [] (size_t index) const { return rows[index]; }
		Vector2& operator [] (size_t index) { return rows[index]; }

		inline Vector2 operator * (const Vector2& v); //{ return { (v.x * rows[0][0]) + (v.y * rows[0][1]), (v.x * rows[1][0]) + (v.y * rows[1][1]) }; }

		Matrix2x2 operator * (const Matrix2x2& mx);

		static Matrix2x2 CreateScale(const Vector2& scale);
		static Matrix2x2 CreateScale(float scale);

		static Matrix2x2 CreateRotation(float radians);

		static const Matrix2x2 identity;
		static const Matrix2x2 zero;
	};

	inline Matrix2x2::Matrix2x2(const Vector2& r1, const Vector2& r2)
	{
		rows[0] = r1;
		rows[1] = r2;
	}

	inline Vector2 Matrix2x2::operator*(const Vector2& v)
	{
		Vector2 result;

		result.x = v.x * rows[0][0] + v.y * rows[0][1];
		result.y = v.x * rows[1][0] + v.y * rows[1][1];

		return result;
	}

	inline Matrix2x2 Matrix2x2::operator*(const Matrix2x2& mx)
	{
		Matrix2x2 result;

		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix2x2 Matrix2x2::CreateScale(const Vector2& scale)
	{
		Matrix2x2 mx;

		mx[0] = { scale.x, 0.0f };
		mx[1] = { 0.0f, scale.y };

		return mx;
	}

	inline Matrix2x2 Matrix2x2::CreateScale(float scale)
	{
		Matrix2x2 mx;

		mx[0] = { scale, 0.0f };
		mx[1] = { 0.0f, scale };

		return mx;
	}

	inline Matrix2x2 Matrix2x2::CreateRotation(float radians)
	{
		Matrix2x2 mx;

		float c = std::cos(radians);
		float s = std::sin(radians);

		mx[0] = { c, -s };
		mx[1] = { s, c };

		return mx;
	}
}
