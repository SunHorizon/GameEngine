#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>


class Camera
{
public:
	Camera();
	~Camera();
	void setPosition(glm::vec3 position_);
	glm::vec3 getPosition();
	void SetRotation(float yaw_, float pitch_);
	glm::mat4 GetView();
	const glm::mat4 GetPerspective();
	const glm::mat4 GetOrthographic();

	void addLightSource(LightSource* light_);
	std::vector<LightSource*> getLightSource();

	void ProcessMouseMovement(float xOffSet_, float yOffSet_);
	void ProcessMouseZoom(float y_);

	glm::vec2 GetClippingPlanes() const;

	std::vector<glm::vec4> FrustumCulling();
private:
	void UpdateCameraVector();
	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 fowardVector, upVector, rightVector, worldUp;

	std::vector<LightSource*> lights;
	void OnDestory();

	std::vector<glm::vec4> NormalizePlane();
};
#endif //!CAMERA_H
