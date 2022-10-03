#include "common.h"
#ifndef OBJLOADER_H
#define OBJLOADER_H

// Cargador de OBJ simple, recibe el path y devuelve los vértices, uv y normales.

bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
);

#endif