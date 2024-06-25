#include <math/vector4.h>
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )
vec4 operator+(const vec4& l, const vec4& r) {
	return vec4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4 operator+=(vec4& l, const vec4& r) {
	return l = vec4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4 operator-(const vec4& l, const vec4& r) {
	return vec4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4 operator-=(vec4& l, const vec4& r) {
	return l = vec4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4 operator*(const vec4& l, const vec4& r) {
	return vec4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}
vec4 operator*=(vec4& l, const vec4& r) {
	return l = vec4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}

vec4 operator*(const vec4& l, float r) {
	return vec4(l.x * r, l.y * r, l.z * r, l.w * r);
}
vec4 operator*=(vec4& l, float r) {
	return l = vec4(l.x * r, l.y * r, l.z * r, l.w * r);
}

vec4 operator/(const vec4& l, const vec4& r) {
	return vec4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}
vec4 operator/=(vec4& l, const vec4& r) {
	return l = vec4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

bool operator==(const vec4& l, const vec4& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z) && CMP(l.w, r.w);
}

bool operator!=(const vec4& l, const vec4& r) {
	return !(l == r);
}

bool operator<(const vec4& l, const vec4& r) {
	if (l.x < r.x && r.y < r.y && r.z < r.z && r.w < r.w)
		return true;
	else
		return false;
}
bool operator<=(const vec4& l, const vec4& r) {
	if (l.x <= r.x && r.y <= r.y && r.z <= r.z && r.w <= r.w)
		return true;
	else
		return false;
}

bool operator>(const vec4& l, const vec4& r) {
	if (l.x > r.x && r.y > r.y && r.z > r.z && r.w > r.w)
		return true;
	else
		return false;
}
bool operator>=(const vec4& l, const vec4& r) {
	if (l.x >= r.x && r.y >= r.y && r.z >= r.z && r.w >= r.w)
		return true;
	else
		return false;
}