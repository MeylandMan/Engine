#include <math/math_main.h>
#include <cmath>
#include <cfloat>


// ----------- VECTORS ----------- 

std::string to_string(vec2& vec) {
	//std::string str = "(x , y)"; //Template
	float x = vec.x;
	float y = vec.y;

	std::string str = "TBA";
	return str;
}

float Dot(const vec2& l, const vec2& r) {
	return l.x * r.x + l.y * r.y;
}
float Dot(const vec2i& l, const vec2i& r) {
	return l.x * r.x + l.y * r.y;
}
float Dot(const vec3& l, const vec3& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}
float Dot(const vec3i& l, const vec3i& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}
float Dot(const vec4& l, const vec4& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}
float Dot(const vec4i& l, const vec4i& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}

float Length(const vec2& v) {
	return sqrtf(Dot(v, v));
}
float Length(const vec2i& v) {
	return sqrtf(Dot(v, v));
}
float Length(const vec3& v) {
	return sqrtf(Dot(v, v));
}
float Length(const vec3i& v) {
	return sqrtf(Dot(v, v));
}
float Length(const vec4& v) {
	return sqrtf(Dot(v, v));
}
float Length(const vec4i& v) {
	return sqrtf(Dot(v, v));
}

float LengthSq(const vec2& v) {
	return Dot(v, v);
}
float LengthSq(const vec2i& v) {
	return Dot(v, v);
}
float LengthSq(const vec3& v) {
	return Dot(v, v);
}
float LengthSq(const vec3i& v) {
	return Dot(v, v);
}
float LengthSq(const vec4& v) {
	return Dot(v, v);
}
float LengthSq(const vec4i& v) {
	return Dot(v, v);
}

float DistanceTo(const vec2& p1, const vec2& p2) {
	vec2 t = p1 - p2;
	return Length(t);
}
float DistanceTo(const vec2i& p1, const vec2i& p2) {
	vec2i t = p1 - p2;
	return Length(t);
}
float DistanceTo(const vec3& p1, const vec3& p2) {
	vec3 t = p1 - p2;
	return Length(t);
}
float DistanceTo(const vec3i& p1, const vec3i& p2) {
	vec3i t = p1 - p2;
	return Length(t);
}
float DistanceTo(const vec4& p1, const vec4& p2) {
	vec4 t = p1 - p2;
	return Length(t);
}
float DistanceTo(const vec4i& p1, const vec4i& p2) {
	vec4i t = p1 - p2;
	return Length(t);
}

void Normalize(vec2& v) {
	v = v * (1.0f / Length(v));
}
void Normalize(vec2i& v) {
	v = v * (1.0f / Length(v));
}
void Normalize(vec3& v) {
	v = v * (1.0f / Length(v));
}
void Normalize(vec3i& v) {
	v = v * (1.0f / Length(v));
}
void Normalize(vec4& v) {
	v = v * (1.0f / Length(v));
}
void Normalize(vec4i& v) {
	v = v * (1.0f / Length(v));
}

vec2 Normalized(const vec2& v) {
	return v * (1.0f / Length(v));
}
vec2i Normalized(const vec2i& v) {
	return v * (1.0f / Length(v));
}
vec3 Normalized(const vec3& v) {
	return v * (1.0f / Length(v));
}
vec3i Normalized(const vec3i& v) {
	return v * (1.0f / Length(v));
}
vec4 Normalized(const vec4& v) {
	return v * (1.0f / Length(v));
}
vec4i Normalized(const vec4i& v) {
	return v * (1.0f / Length(v));
}

vec3 Cross(const vec3& l, const vec3& r) {
	vec3 result;
	result.x = l.y * r.z - l.z * r.y;
	result.y = l.z * r.x - l.x * r.z;
	result.z = l.x * r.y - l.y * r.x;
	return result;
}
vec3i Cross(const vec3i& l, const vec3i& r) {
	vec3i result;
	result.x = l.y * r.z - l.z * r.y;
	result.y = l.z * r.x - l.x * r.z;
	result.z = l.x * r.y - l.y * r.x;
	return result;
}

float Angle(const vec2& l, const vec2& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}
float Angle(const vec2i& l, const vec2i& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}
float Angle(const vec3& l, const vec3& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}
float Angle(const vec3i& l, const vec3i& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}
float Angle(const vec4& l, const vec4& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}
float Angle(const vec4i& l, const vec4i& r) {
	float m = sqrtf(LengthSq(l) * LengthSq(r));
	return acos(Dot(l, r) / m);
}

vec2 Project(const vec2& length, const vec2& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}
vec2i Project(const vec2i& length, const vec2i& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}
vec3 Project(const vec3& length, const vec3& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}
vec3i Project(const vec3i& length, const vec3i& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}
vec4 Project(const vec4& length, const vec4& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}
vec4i Project(const vec4i& length, const vec4i& direction) {
	float dot = Dot(length, direction);
	float magSq = LengthSq(direction);
	return direction * (dot / magSq);
}

vec2 Perpendicular(const vec2& len, const vec2& dir) {
	return len - Project(len, dir);
}
vec2i Perpendicular(const vec2i& len, const vec2i& dir) {
	return len - Project(len, dir);
}
vec3 Perpendicular(const vec3& len, const vec3& dir) {
	return len - Project(len, dir);
}
vec3i Perpendicular(const vec3i& len, const vec3i& dir) {
	return len - Project(len, dir);
}
vec4 Perpendicular(const vec4& len, const vec4& dir) {
	return len - Project(len, dir);
}
vec4i Perpendicular(const vec4i& len, const vec4i& dir) {
	return len - Project(len, dir);
}

vec2 Reflection(const vec2& vec, const vec2& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}
vec2i Reflection(const vec2i& vec, const vec2i& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}
vec3 Reflection(const vec3& vec, const vec3& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}
vec3i Reflection(const vec3i& vec, const vec3i& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}
vec4 Reflection(const vec4& vec, const vec4& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}
vec4i Reflection(const vec4i& vec, const vec4i& normal) {
	float d = Dot(vec, normal);
	return vec - normal * (d * 2.0f);
}