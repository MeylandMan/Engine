#pragma once

typedef struct vec2i {
	union {
		struct {
			int x;
			int y;
		};
		int asArray[2];
	};
	int& operator[](int i) {
		return asArray[i];
	}
	inline vec2i(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
} vec2i;

vec2i operator+(const vec2i& l, const vec2i& r);
vec2i operator+=(vec2i& l, const vec2i& r);

vec2i operator-(const vec2i& l, const vec2i& r);
vec2i operator-=(vec2i& l, const vec2i& r);

vec2i operator*(const vec2i& l, const vec2i& r);
vec2i operator*=(vec2i& l, const vec2i& r);

vec2i operator*(const vec2i& l, float r);
vec2i operator*=(vec2i& l, float r);

vec2i operator/(const vec2i& l, const vec2i& r);
vec2i operator/=(vec2i& l, const vec2i& r);

bool operator==(const vec2i& l, const vec2i& r);
bool operator!=(const vec2i& l, const vec2i& r);

bool operator<(const vec2i& l, const vec2i& r);
bool operator<=(const vec2i& l, const vec2i& r);

bool operator>(const vec2i& l, const vec2i& r);
bool operator>=(const vec2i& l, const vec2i& r);