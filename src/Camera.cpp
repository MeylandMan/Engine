#include<Camera.h>

Camera::Camera(vec3 Position, vec3 TargetTo) :
	m_Position(Position), m_TargetTo(TargetTo) {}

void Camera::setPosition(vec3 Position) { m_Position = Position; }

void Camera::setPositionXaxis(float xx) { m_Position.x = xx; }

void Camera::setPositionYaxis(float yy) { m_Position.y = yy; }

void Camera::setPositionZaxis(float zz) { m_Position.z = zz; }

void Camera::setTarget(vec3 TargetTo) { m_TargetTo = TargetTo; }

void Camera::setTargetXaxis(float xx) { m_TargetTo.x = xx; }

void Camera::setTargetYaxis(float yy) { m_TargetTo.y = yy; }

void Camera::setTargetZaxis(float zz) { m_TargetTo.z = zz; }