//
// Created by Jip Boesenkool on 12/08/2018.
//
#ifndef AGE_CAMERA_H
#define AGE_CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float PITCH      =  0.0f;
const float SPEED      =  3.0f;
const float SENSITIVITY =  0.25f;
const float ZOOM       =  45.0f;

class Camera
{
//---------------------------------------------------------------------------------------------------------------------
// Members
//---------------------------------------------------------------------------------------------------------------------
public:
	// Camera Attributes
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	// Eular Angles
	float m_yaw;
	float m_pitch;
	// Camera options
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;
//---------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//---------------------------------------------------------------------------------------------------------------------
public:
	glm::mat4 GetViewMatrix();
//---------------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------------
public:
	// Constructor with vectors
	Camera(
			glm::vec3 position 	= glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up 		= glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw 			= -90.0f,
			float pitch 		= 0.0f
	);
	// Constructor with scalar values
	Camera(
			float posX, float posY, float posZ,
			float upX, float upY, float upZ,
			float yaw, float pitch
	);
	void SetPosition( glm::vec3& position );
	void Move(glm::vec3 direction);
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseMovement( glm::vec3 rotation, bool constrainPitch = true );
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);
private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors();
	void ConstrainPitch(bool constrainPitch);
};

#endif //AGE_CAMERA_H
