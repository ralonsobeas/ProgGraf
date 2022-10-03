#pragma once
#include "object.h"

class Item : public Object {

public:
	glm::vec2 direction = glm::vec2(0.0f, 0.5f);
	Item() :Object() {};
	Item(std::string fileName) :Object(fileName) { typeObject = ITEM_OBJ; };
	virtual void step() override;
};
