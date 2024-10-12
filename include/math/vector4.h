#pragma once

typedef struct vec4 {
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float asArray[4];
	};
	float& operator[](int i) {
		return asArray[i];
	}
	inline vec4(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 0.0f) {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}
} vec4;

vec4 operator+(const vec4& l, const vec4& r);
vec4 operator+=(vec4& l, const vec4& r);

vec4 operator-(const vec4& l, const vec4& r);
vec4 operator-=(vec4& l, const vec4& r);

vec4 operator*(const vec4& l, const vec4& r);
vec4 operator*=(vec4& l, const vec4& r);

vec4 operator*(const vec4& l, float r);
vec4 operator*=(vec4& l, float r);

vec4 operator/(const vec4& l, const vec4& r);
vec4 operator/=(vec4& l, const vec4& r);

bool operator==(const vec4& l, const vec4& r);
bool operator!=(const vec4& l, const vec4& r);

bool operator<(const vec4& l, const vec4& r);
bool operator<=(const vec4& l, const vec4& r);

bool operator>(const vec4& l, const vec4& r);
bool operator>=(const vec4& l, const vec4& r);