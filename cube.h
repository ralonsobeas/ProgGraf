#pragma once
#include "object.h"


class Cube: public Object{
public:
	//Cube(std::string fileName):Object(fileName){typeObject=CUBE_OBJ;};
	Cube() :Object() { typeObject = CUBE_OBJ; };
	void changePosition();

	virtual void step() override;
};
