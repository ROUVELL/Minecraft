#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>


class Camera
{
	inline constexpr static const glm::vec3 UP_VEC = glm::vec3(0.0f, 1.0f, 0.0f);
	inline constexpr static const float MAX_PITCH = 1.56905f;  // 89.9 deg

	glm::vec3 position;
	glm::vec3 direction = glm::vec3{1.0f, 0.0f, 0.0f};

	glm::vec3 forward = glm::vec3{1.0f, 0.0f, 0.0f};
	glm::vec3 right = glm::vec3{0.0f, 0.0f, 1.0f};

	float yawAngle = 0.0f;
	float pitchAngle = 0.0f;

	glm::mat4 proj = glm::mat4{1.0f};

public:
	Camera(glm::vec3 pos, float fovDeg, float aspect) noexcept;

	glm::vec3 getPosition() const noexcept { return position; }
	glm::vec3 getDirection() const noexcept { return direction; }

	float getYawAngle() const noexcept { return yawAngle; }
	float getPitchAgnle() const noexcept { return pitchAngle; }

	glm::mat4 getProjViewMatrix() const noexcept;

	void setPosition(const glm::vec3 newPosition) noexcept { position = newPosition; }
	void setPosition(float x, float y, float z) noexcept   { position = {x, y, z}; }
	void setYawAngle(float yangle) noexcept                { yawAngle = yangle; }
	void setPitchAngle(float zangle) noexcept              { pitchAngle = zangle; }

	void rotate(float yangle, float zangle) noexcept;

	void moveForward(float distance) noexcept  { position += forward * distance; }
	void moveBackward(float distance) noexcept { position -= forward * distance; }
	void moveRight(float distance) noexcept    { position += right * distance; }
	void moveLeft(float distance) noexcept     { position -= right * distance; }
	void moveUp(float distance) noexcept       { position += UP_VEC * distance; }
	void moveDown(float distance) noexcept     { position -= UP_VEC * distance; }
};

