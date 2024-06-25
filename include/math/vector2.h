#pragma once

typedef struct vec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};
	float& operator[](int i) {
		return asArray[i];
	}
	inline vec2(float xx = 0.0f, float yy = 0.0f) {
		x = xx;
		y = yy;
	}
} vec2;

vec2 operator+(const vec2& l, const vec2& r);
vec2 operator+=(vec2& l, const vec2& r);

vec2 operator-(const vec2& l, const vec2& r);
vec2 operator-=(vec2& l, const vec2& r);

vec2 operator*(const vec2& l, const vec2& r);
vec2 operator*=(vec2& l, const vec2& r);

vec2 operator*(const vec2& l, float r);
vec2 operator*=(vec2& l, float r);

vec2 operator/(const vec2& l, const vec2& r);
vec2 operator/=(vec2& l, const vec2& r);

bool operator==(const vec2& l, const vec2& r);
bool operator!=(const vec2& l, const vec2& r);

bool operator<(const vec2& l, const vec2& r);
bool operator<=(const vec2& l, const vec2& r);

bool operator>(const vec2& l, const vec2& r);
bool operator>=(const vec2& l, const vec2& r);