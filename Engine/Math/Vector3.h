#pragma once

namespace neu
{
	struct Vector3
	{
		float x, y, z;

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}

		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

		Vector3(float v) : x{ v }, y{ v }, z{ v } {}

		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }


		//Arithmetic Operators
		Vector3 operator + (const Vector3 v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3 v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3 v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3 v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3& operator += (const Vector3 v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3 v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3 v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3 v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (float s) { this->x += s; this->y += s; this->z += s; return *this; }
		Vector3& operator -= (float s) { this->x -= s; this->y -= s; this->z -= s; return *this; }
		Vector3& operator *= (float s) { this->x *= s; this->y *= s; this->z *= s; return *this; }
		Vector3& operator /= (float s) { this->x /= s; this->y /= s; this->z /= s; return *this; }

		Vector3 operator - () const { return Vector3{ -x, -y, -z }; }

		bool operator == (const Vector3& v) const { return (v.x == this->x && v.y == this->y && v.z == this->z); }
		bool operator != (const Vector3& v) const { return !(*this == v); }

		float LengthSqr();
		float Length();

		float DistanceSqr(const Vector3& v);
		float Distance(const Vector3& v);

		Vector3 Normalized();
		void Normalize();
	};

	inline float Vector3::LengthSqr()
	{

	}

	inline float Vector3::Length()
	{
		return 0.0f;
	}

	inline float Vector3::DistanceSqr(const Vector3& v)
	{
		return 0.0f;
	}

	inline float Vector3::Distance(const Vector3& v)
	{
		return 0.0f;
	}

	inline Vector3 Vector3::Normalized()
	{
		return Vector3();
	}

	inline void Vector3::Normalize()
	{

	}
}