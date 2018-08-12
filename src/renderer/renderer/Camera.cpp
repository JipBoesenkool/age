//
// Created by Jip Boesenkool on 12/08/2018.
//
#include <renderer/renderer/Camera.h>
//---------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//---------------------------------------------------------------------------------------------------------------------
// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(
			m_position,
			m_position + m_front,
			m_up
	);
}
//---------------------------------------------------------------------------------------------------------------------
// Public Functions
//---------------------------------------------------------------------------------------------------------------------
Camera::Camera( glm::vec3 position, glm::vec3 up, float yaw, float pitch )
{
	//Default values
	m_front 			= glm::vec3(0.0f, 0.0f, -1.0f);
	m_movementSpeed		= SPEED;
	m_mouseSensitivity	= SENSITIVITY;
	m_zoom 				= ZOOM;

	//Set values
	m_position 	= position;
	m_worldUp 	= up;
	m_yaw 		= yaw;
	m_pitch 	= pitch;
	UpdateCameraVectors();
}

Camera::Camera( float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch )
{
	//Default values
	m_front 			= glm::vec3(0.0f, 0.0f, -1.0f);
	m_movementSpeed		= SPEED;
	m_mouseSensitivity	= SENSITIVITY;
	m_zoom 				= ZOOM;

	//Set values
	m_position	= glm::vec3(posX, posY, posZ);
	m_worldUp 	= glm::vec3(upX, upY, upZ);
	m_yaw 		= yaw;
	m_pitch 	= pitch;
	UpdateCameraVectors();
}

void Camera::SetPosition( glm::vec3& position )
{
	m_position = position;
}

void Camera::Move(glm::vec3 direction)
{
	m_position += direction;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		m_position += m_front * velocity;
	}
	else if (direction == RIGHT)
	{
		m_position += m_right * velocity;
	}
	else if (direction == LEFT)
	{
		m_position -= m_right * velocity;
	}
	else if (direction == BACKWARD)
	{
		m_position -= m_front * velocity;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw   += xoffset;
	m_pitch += yoffset;

	ConstrainPitch( constrainPitch );

	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
}

void Camera::ProcessMouseMovement( glm::vec3 rotation, bool constrainPitch )
{
	m_yaw   -= rotation.y;
	m_pitch += rotation.x;

	ConstrainPitch( constrainPitch );

	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
	{
		m_zoom -= yoffset;
	}
	//TODO: quick hack, 44 should be 1.0f
	if (m_zoom <= 44.0f)
	{
		m_zoom = 44.0f;
	}
	else if (m_zoom >= 45.0f)
	{
		m_zoom = 45.0f;
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Private Functions
//---------------------------------------------------------------------------------------------------------------------
void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up    = glm::normalize(glm::cross(m_right, m_front));
}
// Makes sure that when pitch is out of bounds, screen doesn't get flipped
void Camera::ConstrainPitch(bool constrainPitch)
{
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
		{
			m_pitch = 89.0f;
		}
		if (m_pitch < -89.0f)
		{
			m_pitch = -89.0f;
		}
	}
}



