#include "camera.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace {
	float pan_speed = 0.1f;
	float roll_speed = 0.1f;
	float rotation_speed = 0.05f;
	float zoom_speed = 0.1f;
};

// FIXME: Calculate the view matrix
glm::mat4 Camera::get_view_matrix() const
{
	glm::vec3 Z = eye_ - center_;
	Z = glm::normalize(Z);
	glm::vec3 Y = up_;
	glm::vec3 X = glm::cross(Y, Z);
	Y = glm::cross(Z, X);
	X = glm::normalize(X);
	Y = glm::normalize(Y);
	
	glm::mat4 V = {X.x, X.y, X.z, glm::dot(-X, eye_),
				   Y.x, Y.y, Y.z, glm::dot(-Y, eye_),
				   Z.x, Z.y, Z.z, glm::dot(-Z, eye_),
				   0.0f  , 0.0f  , 0.0f  , 1.0f                };
	
	V = glm::transpose(V);

	return V;
}

// Getters and setters beyond here
glm::vec3 Camera::getLook()					{ return look_;				}
glm::vec3 Camera::getEye()					{ return eye_;				}
glm::vec3 Camera::getUp()					{ return up_;				}
glm::vec3 Camera::getRight()				{ return right_;			}
glm::vec3 Camera::getCenter()				{ return center_;			}
void Camera::setLook(glm::vec3 nLook)		{ look_ = nLook;			}
void Camera::setEye(glm::vec3 nEye)			{
	camera_distance_ = glm::distance(nEye, center_);
	eye_ = nEye;
}
void Camera::setUp(glm::vec3 nUp)			{ up_ = nUp;				}
void Camera::setRight(glm::vec3 nRight)		{ right_ = nRight;			}
void Camera::setCenter(glm::vec3 nCenter) { 
	camera_distance_ = glm::distance(nCenter, eye_); 
	center_ = nCenter; 
}
float Camera::getPanSpeed()					{ return pan_speed;			}
float Camera::getZoomSpeed()				{ return zoom_speed;		}
float Camera::getRollSpeed()				{ return roll_speed;		}
float Camera::getRotationSpeed()			{ return rotation_speed;	}
void Camera::rotateEye(glm::vec3 axis_of_rotation, float angle) {

	/*
	glm::mat4x4 V = { right_.x, up_.x, look_.x, eye_.x,
					  right_.y, up_.y, look_.y, eye_.y,
					  right_.z, up_.z, look_.z, eye_.z,
					  0       , 0    , 0      , 1      };
					  */
	glm::mat4x4 V = { right_.x, up_.x, look_.x, eye_.x,
					  right_.y, up_.y, look_.y, eye_.y,
					  right_.z, up_.z, look_.z, eye_.z,
					 0.0f       , 0.0f    , 0.0f      , 1.0f };

	V = glm::rotate(V, angle, axis_of_rotation);
	right_ = glm::vec3(V[0][0], V[1][0], V[2][0]);
	up_    = glm::vec3(V[0][1], V[1][1], V[2][1]);
	look_  = glm::vec3(V[0][2], V[1][2], V[2][2]);
	eye_   = glm::vec3(V[0][3], V[1][3], V[2][3]);
	camera_distance_ = glm::distance(eye_, center_);
}