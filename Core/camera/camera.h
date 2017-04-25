#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "window.h"
#include "const.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
    Camera(Window * window);
	// get
	glm::vec3 getGlobalCamPos(){return this->_cameraPos;}
	glm::vec3 getGlobalCamTarget(){return this->_cameraPos + this->_cameraFront;}
	glm::vec3 getGlobalUpVector(){return this->_cameraUp;}
	glm::vec3 getLocalCamDirection(){return this->_cameraFront;}
	glm::mat4 getProjectionMatrix(){return this->_projectionMatrix;}
	glm::mat4 getViewMatrix(){return this->_viewMatrix;}
	// set
	void setGlobalCamPos(const GLfloat global_x,const GLfloat global_y,const GLfloat global_z)
	{
		this->_cameraPos = glm::vec3(global_x,global_y,global_z);
	}
	void setLocalLookAt(const GLfloat local_x,const GLfloat local_y,const GLfloat local_z)
	{
		this->_cameraFront = glm::vec3(local_x,local_y,local_z);
	}
	void setUpVector(const GLfloat x ,const GLfloat y ,const GLfloat z)
	{
		this->_cameraUp = glm::normalize(glm::vec3(x,y,z));
	}
	void cameraUpdate();
private:
	void keyCallback();
	void cursorCallback();
	void mouseButtonCallback();
	void frameSizeChangeCallback();
	void moveForward(GLfloat const distance)
	{
		this->_cameraPos += glm::normalize(this->_cameraFront) * distance;
	}
	void moveBackward(GLfloat const distance)
	{
		this->_cameraPos -= glm::normalize(this->_cameraFront) * distance;
	}
	void moveLeft(GLfloat const distance)
	{
		this->_cameraPos -= glm::normalize(
			glm::cross(this->_cameraFront,this->_cameraUp)) * distance;
	}
	void moveRight(GLfloat const distance)
	{
		this->_cameraPos += glm::normalize(
			glm::cross(this->_cameraFront,this->_cameraUp)) * distance;
	}

	void rotate()
	{
		if (this->_pitch > 89.0f)
			this->_pitch = 89.0f;
		if (this->_pitch < -89.0f)
			this->_pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
		front.y = sin(glm::radians(this->_pitch));
		front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
		this->_cameraFront = glm::normalize(front);
	}
private:
    Window * _window;
	GLfloat _pfov,_pratio,_pnear,_pfar;
	GLfloat _cameraSpeed;
	GLfloat _deltaTime;
	// 灵敏度
	GLfloat _sensitivity;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	GLfloat _yaw;
	GLfloat _pitch;
	// 投影矩阵和视图矩阵
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
};

#endif