#pragma once

#include<math.h>
class vec3
{
private:
	float e[3];

public:
	vec3() {};
	vec3(float e0, float e1, float e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}
	inline float x() const { return e[0]; };
	inline float y() const { return e[1]; };
	inline float z() const { return e[2]; };
	inline float r() const { return e[0]; };
	inline float g() const { return e[1]; };
	inline float b() const { return e[2]; };

	inline	const vec3& operator+() const { return *this; };
	inline const vec3 operator- () const { return vec3(-e[0], -e[1], -e[2]); };

	inline  vec3 operator+ (const vec3& v2) const
	{
		return vec3(this->e[0] + v2.x(), this->e[1] + v2.y(), this->e[2] + v2.e[2]);
	}
	inline vec3 operator- (const vec3& v2) const
	{

		return vec3(this->e[0] - v2.x(), this->e[1] - v2.y(), this->e[2] - v2.z());
	}
	inline vec3 operator* (const vec3& v2) const
	{
		return vec3(this->e[0] * v2.x(), this->e[1] * v2.y(), this->e[2] * v2.z());
	}
	inline vec3 operator/ (const vec3& v2) const
	{
		return vec3(this->e[0] / v2.x(), this->e[1] / v2.y(), this->e[2] / v2.z());
	}
	inline vec3 operator* (const float t) const
	{
		return vec3(this->e[0] * t, this->e[1] * t, this->e[2] * t);
	}
	inline vec3 operator/ (const float t) const
	{
		return vec3(this->e[0] / t, this->e[1] / t, this->e[2] / t);
	}


	inline float operator[](int i) const { return e[i]; };
	inline float& operator[](int i) { return e[i]; };
	

	inline vec3& operator+=(const vec3 &v2)
	{
		e[0] += v2.x();
		e[1] += v2.y();
		e[2] += v2.z();
		return *this;
	}

	inline vec3&  operator -= (const vec3& v2)
	{
		e[0] -= v2.x();
		e[1] -= v2.y();
		e[2] -= v2.z();
		return *this;
	}

	inline vec3& operator*= (const vec3& v2)
	{
		e[0] *= v2.x();
		e[1] *= v2.y();
		e[2] *= v2.z();
		return *this;
	}

	inline vec3& operator /= (const vec3& v2)
	{
		e[0] /= v2.x();
		e[1] /= v2.y();
		e[2] /= v2.z();
		return *this;
	}

	inline vec3& operator *=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline vec3& operator/= (const float t)
	{
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	}

	inline float length() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float squaredLength() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void makeUnitVector()
	{
		float factor = this->length();
		this->operator/=(factor);
	}

};


inline vec3 makeUnitVector(const vec3&  vec)
{
	vec3  retVec = vec;
	retVec.makeUnitVector();
	return retVec;
}


inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z()* v2.z();
}


inline vec3 cross(const vec3 &v1, const vec3 &v2) 
{
	return vec3( v1.y() * v2.z() - v1.z() * v2.y(),
		v1.z()* v2.x() - v1.x() * v2.z(),
		v1.x()*v2.y() - v1.y() * v2.x() );		
}

inline vec3 operator*(float t, const vec3 &v) 
{
	return vec3(t*v.x(), t*v.y(), t*v.z());
}
