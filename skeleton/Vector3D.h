#pragma once
#include <algorithm>
template<typename T>
class Vector3D
{
	
public:
	T x, y, z;

	Vector3D();
	Vector3D(T x, T y, T z) : x(x), y(y), z(z) {

	};
	Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z)
	{
	}
	Vector3D& operator=(const Vector3D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}
	 Vector3D operator+(const Vector3D& v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	Vector3D operator-(const Vector3D& v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
	 Vector3D operator*(float f) const
	{
		return Vector3D(x * f, y * f, z * f);
	}
	T dot(const Vector3D& v) const
	 {
		 return x * v.x + y * v.y + z * v.z;
	 }
	Vector3D operator*(const Vector3D& v) const
	{
		return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	 T magnitudeSquared() const
	{
		return x * x + y * y + z * z;
	}
	 T normalize()
	{
		const T m = magnitude();
		if (m > 0.0f)
			*this /= m;
		return m;
	}
	 Vector3D getNormalized() const
	 {
		 const T m = magnitudeSquared();
		 return m > 0.0f ? *this * sqrt(m) : Vector3D(0, 0, 0);
	 }
};

