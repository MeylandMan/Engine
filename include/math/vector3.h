#pragma once

typedef struct vec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};
	float& operator[](int i) {
		return asArray[i];
	}
	inline vec3(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f) {
		x = xx;
		y = yy;
		z = zz;
	}
} vec3;

vec3 operator+(const vec3& l, const vec3& r);
vec3 operator+=(vec3& l, const vec3& r);

vec3 operator-(const vec3& l, const vec3& r);
vec3 operator-=(vec3& l, const vec3& r);

vec3 operator*(const vec3& l, const vec3& r);
vec3 operator*=(vec3& l, const vec3& r);

vec3 operator*(const vec3& l, float r);
vec3 operator*=(vec3& l, float r);

vec3 operator/(const vec3& l, const vec3& r);
vec3 operator/=(vec3& l, const vec3& r);

bool operator==(const vec3& l, const vec3& r);
bool operator!=(const vec3& l, const vec3& r);

bool operator<(const vec3& l, const vec3& r);
bool operator<=(const vec3& l, const vec3& r);

bool operator>(const vec3& l, const vec3& r);
bool operator>=(const vec3& l, const vec3& r);
