
#include "Camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Window.hpp"

const glm::vec3 UP_VEC = glm::vec3(0.0, 1.0, 0.0);

Camera::Camera(glm::vec3 pos, float fov)
	: position( pos ),
	  direction( 0.0, 0.0, -1.0 ),
	  right( 1, 0, 0 ),
	  fov( glm::radians(fov) ),
	  proj( 1.0f )
{
	updateProjMatrix();
}

void Camera::updateProjMatrix()
{
	proj = glm::perspectiveRH_ZO(fov, Window::getAspect(), 0.1f, 1000.0f);
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

	if (glm::angle(newDirection, UP_VEC) > glm::radians(1.0) && glm::angle(newDirection, -UP_VEC) > glm::radians(1.0))
		direction = newDirection;
}

void Camera::moveForward(float distance)
{
	position += direction * distance;
}

void Camera::moveBackward(float distance)
{
	position -= direction * distance;
}

void Camera::moveRight(float distance)
{
	position += right * distance;
}

void Camera::moveLeft(float distance)
{
	position -= right * distance;
}

void Camera::moveUp(float distance)
{
	position += UP_VEC * distance;
}

void Camera::moveDown(float distance)
{
	position -= UP_VEC * distance;
}







