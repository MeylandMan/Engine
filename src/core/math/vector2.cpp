#include <math/vector2.h>
#include <cmath>
#include <cfloat>
#include <iostream>

#define CMP(x, y) \
 (fabsf((x)-(y)) <= FLT_EPSILON * \
 fmaxf(1.0f, \
 fmaxf(fabsf(x), fabsf(y))) \
 )
vec2 operator+(const vec2& l, const vec2& r) {
	return vec2(l.x + r.x, l.y + r.y);
}

vec2 operator+=(vec2& l, const vec2& r) {
	return l = vec2(l.x + r.x, l.y + r.y);
}

vec2 operator-(const vec2& l, const vec2& r) {
	return vec2(l.x - r.x, l.y - r.y);
}

vec2 operator-=(vec2& l, const vec2& r) {
	return l = vec2(l.x - r.x, l.y - r.y);
}

vec2 operator*(const vec2& l, const vec2& r) {
	return vec2(l.x * r.x, l.y * r.y);
}
vec2 operator*=(vec2& l, const vec2& r) {
	return l = vec2(l.x * r.x, l.y * r.y);
}

vec2 operator*(const vec2& l, float r) {
	return vec2(l.x * r, l.y * r);
}
vec2 operator*=(vec2& l, float r) {
	return l = vec2(l.x * r, l.y * r);
}

vec2 operator/(const vec2& l, const vec2& r) {
	return vec2(l.x / r.x, l.y / r.y);
}
vec2 operator/=(vec2& l, const vec2& r) {
	return l = vec2(l.x / r.x, l.y / r.y);
}

bool operator==(const vec2& l, const vec2& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator!=(const vec2& l, const vec2& r) {
	return !(l == r);
}

bool operator<(const vec2& l, const vec2& r) {
	if (l.x < r.x && r.y < r.y)
		return true;
	else
		return false;
}
bool operator<=(const vec2& l, const vec2& r) {
	if (l.x <= r.x && r.y <= r.y)
		return true;
	else
		return false;
}

bool operator>(const vec2& l, const vec2& r) {
	if (l.x > r.x && r.y > r.y)
		return true;
	else
		return false;
}
bool operator>=(const vec2& l, const vec2& r) {
	if (l.x >= r.x && r.y >= r.y)
		return true;
	else
		return false;
}