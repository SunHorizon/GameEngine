#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()), perspective(glm::mat4()), orthographic(glm::mat4()), fieldOfView(0), yaw(0.0), pitch(0.0), fowardVector(glm::vec3()), rightVector(glm::vec3()), upVector(glm::vec3()), worldUp(glm::vec3()), lights(std::vector<LightSource*>())
{
	fieldOfView = 45.0f;
	fowardVector = glm::vec3(0.0f, 0.0f, -1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = upVector;
	nearPlane = 2.2f;
	farPlane = 50;
	yaw = -90.0f;
	perspective = glm::perspective(fieldOfView, CoreEngine::getInstance()->GetScreenSize().x / CoreEngine::getInstance()->GetScreenSize().y, nearPlane, farPlane);
	orthographic = glm::ortho(0.0f, CoreEngine::getInstance()->GetScreenSize().x, 0.0f, CoreEngine::getInstance()->GetScreenSize().y, -1.0f, 1.0f);
	UpdateCameraVector();
}
	
Camera::~Camera()
{
	OnDestory();
}

void Camera::setPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVector();
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(position, position + fowardVector, upVector);
}

const glm::mat4 Camera::GetPerspective()
{
	perspective = glm::perspective(fieldOfView, CoreEngine::getInstance()->GetScreenSize().x / CoreEngine::getInstance()->GetScreenSize().y, nearPlane, farPlane);
	return perspective;
}

const glm::mat4 Camera::GetOrthographic()
{
	orthographic = glm::ortho(0.0f, CoreEngine::getInstance()->GetScreenSize().x, 0.0f, CoreEngine::getInstance()->GetScreenSize().y, -1.0f, 1.0f);
	return orthographic;
}

void Camera::addLightSource(LightSource* light_)
{
	lights.push_back(light_);
}

std::vector<LightSource*> Camera::getLightSource()
{
	return lights;
}

void Camera::ProcessMouseMovement(float xOffSet_, float yOffSet_)
{
	xOffSet_ *= 0.05f;
	yOffSet_ *= 0.05f;

	yaw += xOffSet_;
	pitch += yOffSet_;

	if(pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if(pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	if(yaw < 0.0f)
	{
		yaw += 360;
	}
	if (yaw > 360)
	{
		yaw -= 360;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(float y_)
{
	if(y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (fowardVector * 2.0f);
	}

	UpdateCameraVector();
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

void Camera::UpdateCameraVector()
{
	fowardVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	fowardVector.y = sin(glm::radians(pitch));
	fowardVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	fowardVector = glm::normalize(fowardVector);

	rightVector = glm::normalize(glm::cross(fowardVector, worldUp));
	upVector = glm::normalize(glm::cross(rightVector, fowardVector));
}

void Camera::OnDestory()
{
	lights.clear();
}
