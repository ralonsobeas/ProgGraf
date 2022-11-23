#pragma once

#include "common.h"


typedef struct vertex_t{

	glm::vec4 posicion;
	glm::vec4 old_posicion;
	glm::vec4 aceleracion;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texCoord;
	int vecinosCercanos[8];

}vertex_t;
