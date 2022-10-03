#pragma once
#include "object.h"

class Background: public Object{

	
public:
	glm::vec2 scroll = glm::vec2(0,0);

	Background():Object(){};
        Background(std::string fileName):Object(fileName){typeObject=BACKGROUND_OBJ;};
	virtual void step() override;
};

