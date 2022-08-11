#pragma once
#include "Vector2.h"
#include "Vector3.h"


namespace neu
{
	struct Matrix3x3
	{
		Vector3 rows[3];

		Matrix3x3() = default;
		~Matrix3x3() = default;

		Matrix3x3(const Vector3& r1, const Vector3& r2, const Vector3& r3);

		Vector3 operator [] (size_t index) const { return rows[index]; }
		Vector3& operator [] (size_t index) { return rows[index]; }

		inline Vector2 operator * (const Vector2& v) const; //{ return { (v.x * rows[0][0]) + (v.y * rows[0][1]), (v.x * rows[1][0]) + (v.y * rows[1][1]) }; }

		Matrix3x3 operator * (const Matrix3x3& mx) const;

		static Matrix3x3 CreateScale(const Vector2& scale);
		static Matrix3x3 CreateScale(float scale);

		static Matrix3x3 CreateRotation(float radians);

		static Matrix3x3 CreateTranslation(const Vector2& translate);

		static const Matrix3x3 identity;
		static const Matrix3x3 zero;
	};

	inline Matrix3x3::Matrix3x3(const Vector3& r1, const Vector3& r2, const Vector3& r3)
	{
		rows[0] = r1;
		rows[1] = r2;
		rows[2] = r3;
	}

	inline Vector2 Matrix3x3::operator*(const Vector2& v) const
	{
		Vector2 result;

		result.x = v.x * rows[0][0] + v.y * rows[0][1] + 1.0f * rows[0][2];
		result.y = v.x * rows[1][0] + v.y * rows[1][1] + 1.0f * rows[1][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx) const
	{
		Matrix3x3 result;

		//row 1
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		//row 2
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[0][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		//row 3
		result[2][0] = rows[2][0] * mx[0][0] + rows[2][1] * mx[1][0] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[0][1] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[0][2] + rows[2][1] * mx[1][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const Vector2& scale)
	{
		Matrix3x3 mx = identity;

		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale)
	{
		Matrix3x3 mx = identity;

		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float radians)
	{
		Matrix3x3 mx;

		float c = std::cos(radians);
		float s = std::sin(radians);

		mx[0] = { c, -s, 0.0f };
		mx[1] = { s, c, 0.0f };
		mx[2] = { 0.0f, 0.0f, 1.0f };

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateTranslation(const Vector2& translate)
	{
		Matrix3x3 mx = identity;
		
		mx[0][2] = translate.x;
		mx[1][2] = translate.y;

		return mx;
	}
}
