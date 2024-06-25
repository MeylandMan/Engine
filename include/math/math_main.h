#include <math/vector2.h>
#include <math/vector2i.h>
#include <math/vector3.h>
#include <math/vector3i.h>
#include <math/vector4.h>
#include <math/vector4i.h>
#include <math/matrices.h>
#include <algorithm>
#include <iostream>

#define rad_to_deg(x) ((x) * 57.295754f)
#define deg_to_rad(x) ((x) * 0.0174533f)


// ----------- VECTORS ----------- 
#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_

std::string to_string(vec2& vec);

float Dot(const vec2& l, const vec2& r);
float Dot(const vec2i& l, const vec2i& r);
float Dot(const vec3& l, const vec3& r);
float Dot(const vec3i& l, const vec3i& r);
float Dot(const vec4& l, const vec4& r);
float Dot(const vec4i& l, const vec4i& r);

float Length(const vec2& v);
float Length(const vec2i& v);
float Length(const vec3& v);
float Length(const vec3i& v);
float Length(const vec4& v);
float Length(const vec4i& v);

float LengthSq(const vec2& v);
float LengthSq(const vec2i& v);
float LengthSq(const vec3& v);
float LengthSq(const vec3i& v);
float LengthSq(const vec4& v);
float LengthSq(const vec4i& v);

float DistanceTo(const vec2& p1, const vec2& p2);
float DistanceTo(const vec2i& p1, const vec2i& p2);
float DistanceTo(const vec3& p1, const vec3& p2);
float DistanceTo(const vec3i& p1, const vec3i& p2);
float DistanceTo(const vec4& p1, const vec4& p2);
float DistanceTo(const vec4i& p1, const vec4i& p2);

void Normalize(vec2& v);
void Normalize(vec2i& v);
void Normalize(vec3& v);
void Normalize(vec3i& v);
void Normalize(vec4& v);
void Normalize(vec4i& v);

vec2 Normalized(const vec2& v);
vec2i Normalized(const vec2i& v);
vec3 Normalized(const vec3& v);
vec3i Normalized(const vec3i& v);
vec4 Normalized(const vec4& v);
vec4i Normalized(const vec4i& v);

vec3 Cross(const vec3& l, const vec3& r);
vec3i Cross(const vec3i& l, const vec3i& r);

float Angle(const vec2& l, const vec2& r);
float Angle(const vec2i& l, const vec2i& r);
float Angle(const vec3& l, const vec3& r);
float Angle(const vec3i& l, const vec3i& r);
float Angle(const vec4& l, const vec4& r);
float Angle(const vec4i& l, const vec4i& r);

vec2 Project(const vec2& length, const vec2& direction);
vec2i Project(const vec2i& length, const vec2i& direction);
vec3 Project(const vec3& length, const vec3& direction);
vec3i Project(const vec3i& length, const vec3i& direction);
vec4 Project(const vec4& length, const vec4& direction);
vec4i Project(const vec4i& length, const vec4i& direction);

vec2 Perpendicular(const vec2& len, const vec2& dir);
vec2i Perpendicular(const vec2i& len, const vec2i& dir);
vec3 Perpendicular(const vec3& len, const vec3& dir);
vec3i Perpendicular(const vec3i& len, const vec3i& dir);
vec4 Perpendicular(const vec4& len, const vec4& dir);
vec4i Perpendicular(const vec4i& len, const vec4i& dir);

vec2 Reflection(const vec2& vec, const vec2& normal);
vec2i Reflection(const vec2i& vec, const vec2i& normal);
vec3 Reflection(const vec3& vec, const vec3& normal);
vec3i Reflection(const vec3i& vec, const vec3i& normal);
vec4 Reflection(const vec4& vec, const vec4& normal);
vec4i Reflection(const vec4i& vec, const vec4i& normal);

#endif