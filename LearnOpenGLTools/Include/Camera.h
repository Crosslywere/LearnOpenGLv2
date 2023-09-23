#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f), float pitch = 0.0f, float yaw = -90.0f);
	/**
	 * @brief Constructs the view matrix based on the camera's position and orientation
	 */
	const glm::mat4& GetViewMatrix() const;
	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline float GetPitch() const { return m_Pitch; }
	inline void SetPitch(float pitch) { m_Pitch = pitch; UpdateOrientation(); }
	inline float GetYaw() const { return m_Yaw; }
	inline void SetYaw(float yaw, bool clamp = true)
	{
		m_Yaw = yaw;
		if (clamp)
			glm::clamp(m_Yaw, -89.0f, 89.0f);

		UpdateOrientation();
	}
	inline const glm::vec3& GetFront() const { return m_Front; }
	inline const glm::vec3& GetRight() const { return m_Right; }
	inline const glm::vec3& GetUp() const { return m_Up; }
	const glm::vec3 WorldUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
	float FOV = 60.0f;
private:
	void UpdateOrientation();
	glm::vec3 m_Position;
	float m_Pitch;
	float m_Yaw;
	glm::vec3 m_Front;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
};

#endif