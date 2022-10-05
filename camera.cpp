#include "camera.h"
#include "inputManager.h"

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt,cameraType_e type)
{

	this->position=pos;
	this->lookAt=lookAt;
	this->rotation=glm::vec3(0.0f,0.0f,0.0f);
	this->viewMatrix=glm::mat4(1.0f);
	this->type=type;
	
	switch (type){
	
		case perspective:
			{
				projMatrix=glm::perspective(glm::radians(90.0f), 4.0f/3.0f,0.01f, 100.0f);
			}break;
			
		case ortho:
				projMatrix=glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.01f, 100.0f);			
		break;
	};
	
}

void Camera::computeMatrix(){

	this->viewMatrix=glm::lookAt(position,lookAt,glm::vec3(0.0f,1.0f,0.0f));
}

glm::mat4 Camera::getMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(){

	return projMatrix;

}

glm::vec4 Camera::camPos()
{
	glm::vec4 pos = glm::vec4(position.x, position.y, position.z, 1.0f);
	return pos;
}

void Camera::step()
{
	if (InputManager::keys['F'])
	{
		position.x -= 1.f;
		lookAt.x -= 1.f;
	}

	if (InputManager::keys['H'])
	{
		position.x += 1.f;
		lookAt.x += 1.f;
	}
	if (InputManager::keys['T'])
	{
		position.y += 1.f;
		lookAt.y += 1.f;
	}

	if (InputManager::keys['G'])
	{
		position.y -= 1.f;
		lookAt.y -= 1.f;
	}
	if (InputManager::keys['E'])
	{
		position.z += 1.f;
		lookAt.z += 1.f;
	}
	if (InputManager::keys['Q'])
	{
		position.z -= 1.f;
		lookAt.z -= 1.f;
	}


}


