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


std::vector<glm::vec4> Camera::FrustumCulling()
{
	UpdateCameraVector();
	glm::mat4 view = GetView();
	glm::mat4 proj = GetPerspective();
	
	glm::mat4 clip;
	glm::vec4 right, left, bottom, top, front, back;

	std::vector<glm::vec4> Planes;
	Planes.clear();
	{
		clip[0][0] = view[0][0] * proj[0][0] + view[0][1] * proj[1][0] + view[0][2] * proj[2][0] + view[0][3] * proj[3][0];
		clip[0][1] = view[0][0] * proj[0][1] + view[0][1] * proj[1][1] + view[0][2] * proj[2][1] + view[0][3] * proj[3][1];
		clip[0][2] = view[0][0] * proj[0][2] + view[0][1] * proj[1][2] + view[0][2] * proj[2][2] + view[0][3] * proj[3][2];
		clip[0][3] = view[0][0] * proj[0][3] + view[0][1] * proj[1][3] + view[0][2] * proj[2][3] + view[0][3] * proj[3][3];

		clip[1][0] = view[1][0] * proj[0][0] + view[1][1] * proj[1][0] + view[1][2] * proj[2][0] + view[1][3] * proj[3][0];
		clip[1][1] = view[1][0] * proj[0][1] + view[1][1] * proj[1][1] + view[1][2] * proj[2][1] + view[1][3] * proj[3][1];
		clip[1][2] = view[1][0] * proj[0][2] + view[1][1] * proj[1][2] + view[1][2] * proj[2][2] + view[1][3] * proj[3][2];
		clip[1][3] = view[1][0] * proj[0][3] + view[1][1] * proj[1][3] + view[1][2] * proj[2][3] + view[1][3] * proj[3][3];

		clip[2][0] = view[2][0] * proj[0][0] + view[2][1] * proj[1][0] + view[2][2] * proj[2][0] + view[2][3] * proj[3][0];
		clip[2][1] = view[2][0] * proj[0][1] + view[2][1] * proj[1][1] + view[2][2] * proj[2][1] + view[2][3] * proj[3][1];
		clip[2][2] = view[2][0] * proj[0][2] + view[2][1] * proj[1][2] + view[2][2] * proj[2][2] + view[2][3] * proj[3][2];
		clip[2][3] = view[2][0] * proj[0][3] + view[2][1] * proj[1][3] + view[2][2] * proj[2][3] + view[2][3] * proj[3][3];

		clip[3][0] = view[3][0] * proj[0][0] + view[3][1] * proj[1][0] + view[3][2] * proj[2][0] + view[3][3] * proj[3][0];
		clip[3][1] = view[3][0] * proj[0][1] + view[3][1] * proj[1][1] + view[3][2] * proj[2][1] + view[3][3] * proj[3][1];
		clip[3][2] = view[3][0] * proj[0][2] + view[3][1] * proj[1][2] + view[3][2] * proj[2][2] + view[3][3] * proj[3][2];
		clip[3][3] = view[3][0] * proj[0][3] + view[3][1] * proj[1][3] + view[3][2] * proj[2][3] + view[3][3] * proj[3][3];
	}

	// right plane
	right.x = clip[0][3] - clip[0][0];
	right.y = clip[1][3] - clip[1][0];
	right.z = clip[2][3] - clip[2][0];
	right.w = clip[3][3] - clip[3][0];

	right = glm::normalize(right);
	Planes.push_back(right);

	// left plane
	left.x = clip[0][3] + clip[0][0];
	left.y = clip[1][3] + clip[1][0];
	left.z = clip[2][3] + clip[2][0];
	left.w = clip[3][3] + clip[3][0];

	left = glm::normalize(left);
	Planes.push_back(left);

	// bottom plane
	bottom.x = clip[0][3] + clip[0][1];
	bottom.y = clip[1][3] + clip[1][1];
	bottom.z = clip[2][3] + clip[2][1];
	bottom.w = clip[3][3] + clip[3][1];

	bottom = glm::normalize(bottom);
	Planes.push_back(bottom);

	//Top plane
	top.x = clip[0][3] - clip[0][1];
	top.y = clip[1][3] - clip[1][1];
	top.z = clip[2][3] - clip[2][1];
	top.w = clip[3][3] - clip[3][1];

	top = glm::normalize(top);
	Planes.push_back(top);

	//front plane
	front.x = clip[0][3] - clip[0][2];
	front.y = clip[1][3] - clip[1][2];
	front.z = clip[2][3] - clip[2][2];
	front.w = clip[3][3] - clip[3][2];

	front = glm::normalize(front);
	Planes.push_back(front);

	//back plane
	back.x = clip[0][3] + clip[0][2];
	back.y = clip[1][3] + clip[1][2];
	back.z = clip[2][3] + clip[2][2];
	back.w = clip[3][3] + clip[3][2];

	back = glm::normalize(back);
	Planes.push_back(back);

	return Planes;
}
