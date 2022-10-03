#include "item.h"
#include "system.h"

void Item::step() {
	this->position.x += direction.x * 0.01f;
	this->position.y += direction.y * 0.01f;

	std::vector<Object*>* player = System::scene->getCollisions(SPACESHIP_OBJ, this);

	if (player->size() > 0) {
		System::scene->deleteObject(this);
		for (auto it = player->begin(); it != player->end(); it++) {
			int fire = (int)rand() % 3;
			(*it)->setFireType(fire);
		}
	}
}