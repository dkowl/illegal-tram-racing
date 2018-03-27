#pragma once

#include "../Engine/GameObject.h"

class Track;

class Tram : public GameObject
{
public:
	static const float AXIS_DISTANCE;
private:
	static const float ACCELERATION; //		m/s^2
	static const float MAX_SPEED; //		m/s
	static const float STATIC_FRICTION_DECELERATION;
	static const float FRICTION_DECELERATION;
	static const float BRAKING_DECELERATION;
	static const float SPEED_MULTIPLIER;

	Track* track;

	float speed;
	float distanceTraveled;
	float yRotation;
	float yRotationPrev;
	float centrifugalForce;

public:
	explicit Tram(const GameObject::BuildParams &params);

	void Initialize();
	void Update() override;

	float Speed() const;
	float DistanceTraveled() const;
	
private:
	float Acceleration() const;
	float CentrifugalForce() const;

	void UpdateSpeed(const float &deltaTime);

};
