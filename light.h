#pragma once
#include "common.h"

class Light
{
public:
	glm::vec4 lightPos;
	glm::vec4 lightColor;
	Light(glm::vec4 lightPos, glm::vec4 lightColor);
	~Light();
	virtual void step();
};