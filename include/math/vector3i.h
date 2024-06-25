#pragma once

typedef struct vec3i {
	union {
		struct {
			int x;
			int y;
			int z;
		};
		int asArray[3];
	};
	int& operator[](int i) {
		return asArray[i];
	}
	inline vec3i(int xx = 0, int yy = 0, int zz = 0) {
		x = xx;
		y = yy;
		z = zz;
	}
} vec3i;

vec3i operator+(const vec3i& l, const vec3i& r);
vec3i operator+=(vec3i& l, const vec3i& r);

vec3i operator-(const vec3i& l, const vec3i& r);
vec3i operator-=(vec3i& l, const vec3i& r);

vec3i operator*(const vec3i& l, const vec3i& r);
vec3i operator*=(vec3i& l, const vec3i& r);

vec3i operator*(const vec3i& l, float r);
vec3i operator*=(vec3i& l, float r);

vec3i operator/(const vec3i& l, const vec3i& r);
vec3i operator/=(vec3i& l, const vec3i& r);

bool operator==(const vec3i& l, const vec3i& r);
bool operator!=(const vec3i& l, const vec3i& r);

bool operator<(const vec3i& l, const vec3i& r);
bool operator<=(const vec3i& l, const vec3i& r);

bool operator>(const vec3i& l, const vec3i& r);
bool operator>=(const vec3i& l, const vec3i& r);