#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, float pitch, float yaw)
	:m_Position{ position }, m_Pitch{ pitch }, m_Yaw{ yaw }
{
	UpdateOrientation();
}

const glm::mat4& Camera::GetViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::UpdateOrientation()
{
	m_Front.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_Front.y = glm::sin(glm::radians(m_Pitch));
	m_Front.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);
	m_Right = glm::normalize(glm::cross(m_Front, WorldUp));
	m_Up = glm::cross(m_Right, m_Front);
}
