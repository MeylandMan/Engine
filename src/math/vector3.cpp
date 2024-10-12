#include <math/vector3.h>
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )
vec3 operator+(const vec3& l, const vec3& r) {
	return vec3(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3 operator+=(vec3& l, const vec3& r) {
	return l = vec3(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3 operator-(const vec3& l, const vec3& r) {
	return vec3(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3 operator-=(vec3& l, const vec3& r) {
	return l = vec3(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3 operator*(const vec3& l, const vec3& r) {
	return vec3(l.x * r.x, l.y * r.y, l.z * r.z);
}
vec3 operator*=(vec3& l, const vec3& r) {
	return l = vec3(l.x * r.x, l.y * r.y, l.z * r.z);
}

vec3 operator*(const vec3& l, float r) {
	return vec3(l.x * r, l.y * r, l.z * r);
}
vec3 operator*=(vec3& l, float r) {
	return l = vec3(l.x * r, l.y * r, l.z * r);
}

vec3 operator/(const vec3& l, const vec3& r) {
	return vec3(l.x / r.x, l.y / r.y, l.z / r.z);
}
vec3 operator/=(vec3& l, const vec3& r) {
	return l = vec3(l.x / r.x, l.y / r.y, l.z / r.z);
}

bool operator==(const vec3& l, const vec3& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}

bool operator!=(const vec3& l, const vec3& r) {
	return !(l == r);
}

bool operator<(const vec3& l, const vec3& r) {
	if (l.x < r.x && r.y < r.y && r.z < r.z)
		return true;
	else
		return false;
}
bool operator<=(const vec3& l, const vec3& r) {
	if (l.x <= r.x && r.y <= r.y && r.z <= r.z)
		return true;
	else
		return false;
}

bool operator>(const vec3& l, const vec3& r) {
	if (l.x > r.x && r.y > r.y && r.z > r.z)
		return true;
	else
		return false;
}
bool operator>=(const vec3& l, const vec3& r) {
	if (l.x >= r.x && r.y >= r.y && r.z >= r.z)
		return true;
	else
		return false;
}