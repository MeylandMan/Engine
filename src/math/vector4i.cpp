#include <math/vector4i.h>
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )
vec4i operator+(const vec4i& l, const vec4i& r) {
	return vec4i(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4i operator+=(vec4i& l, const vec4i& r) {
	return l = vec4i(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4i operator-(const vec4i& l, const vec4i& r) {
	return vec4i(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4i operator-=(vec4i& l, const vec4i& r) {
	return l = vec4i(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4i operator*(const vec4i& l, const vec4i& r) {
	return vec4i(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}
vec4i operator*=(vec4i& l, const vec4i& r) {
	return l = vec4i(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}

vec4i operator*(const vec4i& l, float r) {
	return vec4i(l.x * r, l.y * r, l.z * r, l.w * r);
}
vec4i operator*=(vec4i& l, float r) {
	return l = vec4i(l.x * r, l.y * r, l.z * r, l.w * r);
}

vec4i operator/(const vec4i& l, const vec4i& r) {
	return vec4i(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}
vec4i operator/=(vec4i& l, const vec4i& r) {
	return l = vec4i(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

bool operator==(const vec4i& l, const vec4i& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z) && CMP(l.w, r.w);
}

bool operator!=(const vec4i& l, const vec4i& r) {
	return !(l == r);
}

bool operator<(const vec4i& l, const vec4i& r) {
	if (l.x < r.x && r.y < r.y && r.z < r.z && r.w < r.w)
		return true;
	else
		return false;
}
bool operator<=(const vec4i& l, const vec4i& r) {
	if (l.x <= r.x && r.y <= r.y && r.z <= r.z && r.w <= r.w)
		return true;
	else
		return false;
}

bool operator>(const vec4i& l, const vec4i& r) {
	if (l.x > r.x && r.y > r.y && r.z > r.z && r.w > r.w)
		return true;
	else
		return false;
}
bool operator>=(const vec4i& l, const vec4i& r) {
	if (l.x >= r.x && r.y >= r.y && r.z >= r.z && r.w >= r.w)
		return true;
	else
		return false;
}