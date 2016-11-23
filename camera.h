#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
public:
	glm::mat4 get_view_matrix() const;
	glm::vec3 getLook();
	glm::vec3 getUp();
	glm::vec3 getRight();
	glm::vec3 getEye();
	glm::vec3 getCenter();
	float getPanSpeed();
	float getZoomSpeed();
	float getRollSpeed();
	float getRotationSpeed();
	void setLook(glm::vec3 nLook);
	void setEye(glm::vec3 nEye);
	void setUp(glm::vec3 nUp);
	void setRight(glm::vec3 nRight);
	void setCenter(glm::vec3 nCenter);
	void rotateEye(glm::vec3 axis_of_rotation, float angle);
private:
	float camera_distance_ = 3.0;
	glm::vec3 look_ = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 center_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 right_ = glm::vec3(1.0, 0.0f, 0.0f);
	glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, camera_distance_);
	// Note: you may need additional member variables
};

#endif
