#pragma once

#include "common.h"
#include "vertex.h"
#include <vector>
#include "shader.h"
#include "texture.h"

typedef struct vertexFisico_t {

	int control;
	float posicion[4];
	float aceleracion[4];
	int vecinosCercanos[8];

}vertexFisico_t;

class Mesh{

public:
//atributos
	int tamTela = 25;
	std::vector<vertex_t>* vertexList;
	vertexFisico_t* vertexFisica = new vertexFisico_t[tamTela*tamTela];
	std::vector<int>* faceList;
	GLShader* shader;
	Texture* tex = nullptr;
//métodos	
	Mesh();
	Mesh(std::string fileName);
	~Mesh();
	void loadFromFile(std::string fileName);
	void setColor(int idxVertex, glm::vec4 color);
	//void drawSquare(double x1, double y1, double sidelength);
};
