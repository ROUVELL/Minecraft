#pragma once

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 right;

	float fov;
	glm::mat4 proj;

	void updateProjMatrix();

public:
	Camera(const glm::vec3& pos, float fov);

	void yaw(float angle);
	void pitch(float angle);

	void moveForward(float distance);
	void moveBackward(float distance);
	void moveRight(float distance);
	void moveLeft(float distance);
	void moveUp(float distance);
	void moveDown(float distance);

	glm::vec3 getPosition() const { return position; }
	glm::vec3 getDirection() const { return direction; }
	float getFOV() const { return fov; }

	void setPosition(const glm::vec3 newPosition) { position = newPosition; }
	void setPosition(float x, float y, float z) { position = {x, y, z}; }
	void setDirection(const glm::vec3 newDirection) { direction = glm::normalize(newDirection); }
	void setDirection(float x, float y, float z) { direction = glm::normalize(glm::vec3(x, y, z)); }
	void setFOV(float newFov) { fov = glm::radians(newFov); updateProjMatrix(); }

	glm::mat4 getProjViewMatrix() const;
};

