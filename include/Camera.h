#pragma once

#include <math/math_main.h>


class Camera {
public:
	Camera(vec3 Position, vec3 TargetTo);

	void setPosition(vec3 Position);
	void setPositionXaxis(float xx);
	void setPositionYaxis(float yy);
	void setPositionZaxis(float zz);

	void setTarget(vec3 TargetTo);
	void setTargetXaxis(float xx);
	void setTargetYaxis(float yy);
	void setTargetZaxis(float zz);

	vec3 getPosition() { return m_Position; }
	vec3 getTarget() { return m_TargetTo; }
private:
	vec3 m_Position;
	vec3 m_TargetTo;
};