
#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


Camera::Camera(glm::vec3 pos, float fov, float aspect) noexcept
	: position( pos )
{
	proj = glm::perspectiveRH_ZO(glm::radians(fov), aspect, 0.1f, 1000.0f);
}

glm::mat4 Camera::getProjViewMatrix() const noexcept
{
	return proj * glm::lookAtRH(position, position + direction, UP_VEC);
}

void Camera::rotate(float yangle, float zangle) noexcept
{
	yawAngle += yangle;
	pitchAngle += zangle;
	pitchAngle = glm::clamp(pitchAngle, -MAX_PITCH, MAX_PITCH);

	direction.x = glm::cos(pitchAngle) * glm::cos(yawAngle);
	direction.y = glm::sin(pitchAngle);
	direction.z = glm::cos(pitchAngle) * glm::sin(yawAngle);
	
	right = glm::normalize(glm::cross(direction, UP_VEC));
	forward = glm::normalize(glm::cross(-right, UP_VEC));
}