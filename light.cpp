#include "light.h"

Light::Light(glm::vec4 lightPos, glm::vec4 lightColor)
{
	this->lightPos = lightPos;
	this->lightColor = lightColor;
}

Light::~Light()
{
}

void Light::step()
{
}
