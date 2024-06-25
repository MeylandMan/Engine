#include <math/vector2i.h>
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )

vec2i operator+(const vec2i& l, const vec2i& r) {
	return vec2i(l.x + r.x, l.y + r.y);
}

vec2i operator+=(vec2i& l, const vec2i& r) {
	return l = vec2i(l.x + r.x, l.y + r.y);
}

vec2i operator-(const vec2i& l, const vec2i& r) {
	return vec2i(l.x - r.x, l.y - r.y);
}

vec2i operator-=(vec2i& l, const vec2i& r) {
	return l = vec2i(l.x - r.x, l.y - r.y);
}

vec2i operator*(const vec2i& l, const vec2i& r) {
	return vec2i(l.x * r.x, l.y * r.y);
}
vec2i operator*=(vec2i& l, const vec2i& r) {
	return l = vec2i(l.x * r.x, l.y * r.y);
}

vec2i operator*(const vec2i& l, float r) {
	return vec2i(l.x * r, l.y * r);
}
vec2i operator*=(vec2i& l, float r) {
	return l = vec2i(l.x * r, l.y * r);
}

vec2i operator/(const vec2i& l, const vec2i& r) {
	return vec2i(l.x / r.x, l.y / r.y);
}
vec2i operator/=(vec2i& l, const vec2i& r) {
	return l = vec2i(l.x / r.x, l.y / r.y);
}

bool operator==(const vec2i& l, const vec2i& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator!=(const vec2i& l, const vec2i& r) {
	return !(l == r);
}

bool operator<(const vec2i& l, const vec2i& r) {
	if (l.x < r.x && r.y < r.y)
		return true;
	else
		return false;
}
bool operator<=(const vec2i& l, const vec2i& r) {
	if (l.x <= r.x && r.y <= r.y)
		return true;
	else
		return false;
}

bool operator>(const vec2i& l, const vec2i& r) {
	if (l.x > r.x && r.y > r.y)
		return true;
	else
		return false;
}
bool operator>=(const vec2i& l, const vec2i& r) {
	if (l.x >= r.x && r.y >= r.y)
		return true;
	else
		return false;
}