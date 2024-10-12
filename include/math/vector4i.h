#pragma once

typedef struct vec4i {
	union {
		struct {
			int x;
			int y;
			int z;
			int w;
		};
		int asArray[4];
	};
	int& operator[](int i) {
		return asArray[i];
	}
	inline vec4i(int xx = 0, int yy = 0, int zz = 0, int ww = 0) {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}
} vec4i;

vec4i operator+(const vec4i& l, const vec4i& r);
vec4i operator+=(vec4i& l, const vec4i& r);

vec4i operator-(const vec4i& l, const vec4i& r);
vec4i operator-=(vec4i& l, const vec4i& r);

vec4i operator*(const vec4i& l, const vec4i& r);
vec4i operator*=(vec4i& l, const vec4i& r);

vec4i operator*(const vec4i& l, float r);
vec4i operator*=(vec4i& l, float r);

vec4i operator/(const vec4i& l, const vec4i& r);
vec4i operator/=(vec4i& l, const vec4i& r);

bool operator==(const vec4i& l, const vec4i& r);
bool operator!=(const vec4i& l, const vec4i& r);

bool operator<(const vec4i& l, const vec4i& r);
bool operator<=(const vec4i& l, const vec4i& r);

bool operator>(const vec4i& l, const vec4i& r);
bool operator>=(const vec4i& l, const vec4i& r);
