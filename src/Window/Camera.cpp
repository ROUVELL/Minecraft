
#include "Camera.hpp"

#include <glm/ext/quaternion_geometric.hpp>
#include <glm/trigonometric.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>


Camera::Camera(glm::vec3 pos, float fov, float aspect)
	: position( pos )
{
	proj = glm::perspectiveRH_ZO(glm::radians(fov), aspect, 0.1f, 1000.0f);
}

glm::mat4 Camera::getProjViewMatrix() const
{
	return proj * glm::lookAtRH(position, position + direction, UP_VEC);
}

void Camera::yaw(float value)
{
	direction = glm::rotate(direction, value, UP_VEC);
	right = glm::normalize(glm::cross(direction, UP_VEC));
}

void Camera::pitch(float value)
{
	glm::vec3 newDirection = glm::rotate(direction, value, right);

	if (glm::angle(newDirection, UP_VEC) > glm::radians(1.0f) && glm::angle(newDirection, -UP_VEC) > glm::radians(1.0f))
		direction = newDirection;
}