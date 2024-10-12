#include <math/vector3i.h>
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )

vec3i operator+(const vec3i& l, const vec3i& r) {
	return vec3i(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3i operator+=(vec3i& l, const vec3i& r) {
	return l = vec3i(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3i operator-(const vec3i& l, const vec3i& r) {
	return vec3i(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3i operator-=(vec3i& l, const vec3i& r) {
	return l = vec3i(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3i operator*(const vec3i& l, const vec3i& r) {
	return vec3i(l.x * r.x, l.y * r.y, l.z * r.z);
}
vec3i operator*=(vec3i& l, const vec3i& r) {
	return l = vec3i(l.x * r.x, l.y * r.y, l.z * r.z);
}

vec3i operator*(const vec3i& l, float r) {
	return vec3i(l.x * r, l.y * r, l.z * r);
}
vec3i operator*=(vec3i& l, float r) {
	return l = vec3i(l.x * r, l.y * r, l.z * r);
}

vec3i operator/(const vec3i& l, const vec3i& r) {
	return vec3i(l.x / r.x, l.y / r.y, l.z / r.z);
}
vec3i operator/=(vec3i& l, const vec3i& r) {
	return l = vec3i(l.x / r.x, l.y / r.y, l.z / r.z);
}

bool operator==(const vec3i& l, const vec3i& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}

bool operator!=(const vec3i& l, const vec3i& r) {
	return !(l == r);
}

bool operator<(const vec3i& l, const vec3i& r) {
	if (l.x < r.x && r.y < r.y && r.z < r.z)
		return true;
	else
		return false;
}
bool operator<=(const vec3i& l, const vec3i& r) {
	if (l.x <= r.x && r.y <= r.y && r.z <= r.z)
		return true;
	else
		return false;
}

bool operator>(const vec3i& l, const vec3i& r) {
	if (l.x > r.x && r.y > r.y && r.z > r.z)
		return true;
	else
		return false;
}
bool operator>=(const vec3i& l, const vec3i& r) {
	if (l.x >= r.x && r.y >= r.y && r.z >= r.z)
		return true;
	else
		return false;
}