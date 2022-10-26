#include "cube.h"
#include "inputManager.h"
#include "scene.h"
#include "system.h"


void Cube::step()
{


	if(InputManager::keys['A'])
	{
                rotation.y-=0.01f;
	}	

	if(InputManager::keys['D'])
	{
                rotation.y+=0.01f;
	}
	
	
	if(InputManager::keys['W'])
	{
                rotation.x-=0.01f;
	}	

	if(InputManager::keys['S'])
	{
                rotation.x+=0.01f;
	}

	changePosition();

}

void Cube::changePosition() {
	std::vector<vertex_t>* vertexList = this->mesh->vertexList;

	//Cambiar vértices
	for (int x = 0; x < vertexList->size()/2; x++) {
		//printf("%d %f ", x, vertexList->at(x).posicion.y);
		vertexList->at(x).posicion.y -= 0.01;
	}
}

