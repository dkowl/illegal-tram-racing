#pragma once
#include <glm/detail/type_vec3.hpp>
#include <memory>

class Camera;
class Tram;

class Screenshake
{
	Camera* camera;
	Tram* tram;

	float impactTime;
	float baseImpactForce;
	float springMass;
	float impactChancePerSecond;
	float springCoeff;
	float dragCoeff;

	glm::vec3 impactDirection;
	float timeSinceLastImpact;

	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 offset;

public:
	Screenshake();
	void SetCamera(Camera* camera);

	void Initialize();
	void Update();

private:
	glm::vec3 ImpactForce() const;
	glm::vec3 SpringForce() const;
	glm::vec3 DragForce() const;

	void Shake();
};
