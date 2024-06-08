#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Camera
{
	inline constexpr static const glm::vec3 UP_VEC = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 position;
	glm::vec3 direction = glm::vec3{0.0f, 0.0f, -1.0f};
	glm::vec3 right = glm::vec3{1.0f, 0.0f, 0.0f};

	glm::mat4 proj = glm::mat4{1.0f};

public:
	Camera(glm::vec3 pos, float fov, float aspect);

	void yaw(float angle);
	void pitch(float angle);

	void moveForward(float distance)  { position += direction * distance; }
	void moveBackward(float distance) { position -= direction * distance; }
	void moveRight(float distance)    { position += right * distance; }
	void moveLeft(float distance)     { position -= right * distance; }
	void moveUp(float distance)       { position += UP_VEC * distance; }
	void moveDown(float distance)     { position -= UP_VEC * distance; }

	glm::vec3 getPosition()  const { return position; }
	glm::vec3 getDirection() const { return direction; }

	void setPosition(const glm::vec3 newPosition)   { position = newPosition; }
	void setPosition(float x, float y, float z)     { position = {x, y, z}; }

	glm::mat4 getProjViewMatrix() const;
};

