#include "mesh.h"
#include "loaderOBJ.hpp"
#include <iostream>
#include <fstream>


Mesh::Mesh(){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();

//añadir vértices
	int size = 50;
	int i = 0;

	for (int x = 0; x < size; x++) {
		
		//Creamos todos los vértices
		for (int y = 0; y < size; y++) {
			
			vertex_t v1;
			v1.posicion = glm::vec4(0.0f + y, 0.0f + x, 0.0f, 1.0f);
			for (int j = 0; j < 8; j++) {
				v1.verticesAdyacentes[0] = y + (x - 1) * size - 1;
				v1.verticesAdyacentes[1] = y + (x - 1) * size;
				v1.verticesAdyacentes[2] = y + (x - 1) * size + 1;
				v1.verticesAdyacentes[3] = y + x * size - 1;
				v1.verticesAdyacentes[4] = y + x * size + 1;
				v1.verticesAdyacentes[5] = y + (x + 1) * size - 1;
				v1.verticesAdyacentes[6] = y + (x + 1) * size;
				v1.verticesAdyacentes[7] = y + (x + 1) * size + 1;
				if (y == 0) {
					v1.verticesAdyacentes[0] = -1;
					v1.verticesAdyacentes[1] = -1;
					v1.verticesAdyacentes[2] = -1;
				}
				else if (y == size - 1) {
					v1.verticesAdyacentes[5] = -1;
					v1.verticesAdyacentes[6] = -1;
					v1.verticesAdyacentes[7] = -1;
				}
				if (x == 0) {
					v1.verticesAdyacentes[0] = -1;
					v1.verticesAdyacentes[3] = -1;
					v1.verticesAdyacentes[5] = -1;
				}
				else if (x == size - 1) {
					v1.verticesAdyacentes[2] = -1;
					v1.verticesAdyacentes[4] = -1;
					v1.verticesAdyacentes[7] = -1;
				}
				
			}
			i++;
			v1.verticesAdyacentes[0] = 0;
			vertexList->push_back(v1);
		}
		//Cuadrado a cuadrado creando triangulos
		for (int y = 0; y < size - 1; y++) {
			if (x == 0)
				break;
			//Primer triangulo
			faceList->push_back(y + ((x - 1) * size));
			faceList->push_back(y + ((x - 1) * size) + 1);
			faceList->push_back(x * size + y);
			//Segundo triangulo
			faceList->push_back(y + ((x - 1) * size) + 1);
			faceList->push_back(x * size + y);
			faceList->push_back(x * size + y + 1);
		}		
	}
	printf("%d\n", i);
	/*
	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";
	std::string textureFile = "data/front.png";

	shader = new GLShader(vshader, fshader);
	tex = new Texture(textureFile);
	*/

	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";
	std::string textureFile = "data/front.png";

	shader = new GLShader(vshader, fshader);
	tex = new Texture(textureFile);
}


Mesh::Mesh(std::string fileName){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();
//añadir vértices
	loadFromFile(fileName);
}





void Mesh::setColor(int idxVertex, glm::vec4 color){
	(*vertexList)[idxVertex].color=color;
}


void Mesh::loadFromFile(std::string fileName){
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	loadOBJ(fileName.c_str(), temp_vertices, temp_uvs, temp_normals);
	for (int i = 0; i < temp_vertices.size(); i++) {
		vertex_t v1;
		v1.posicion.x = temp_vertices[i].x;
		v1.posicion.y = temp_vertices[i].y;
		v1.posicion.z = temp_vertices[i].z;
		v1.posicion.w = 1;
		v1.color.r = 1;
		v1.color.g = 1;
		v1.color.b = 1;
		v1.color.a = 1;
		v1.normal.x = temp_normals[i].x;
		v1.normal.y = temp_normals[i].y;
		v1.normal.z = temp_normals[i].z;
		v1.normal.w = 0;
		v1.texCoord.x = temp_normals[i].x;
		v1.texCoord.y = temp_normals[i].y;
		//v1.texCoord.x = rand() % 2;
		//v1.texCoord.y = rand() % 2;
		vertexList->push_back(v1);
		int b1;
		b1 = i;
		faceList->push_back(b1);
		
	}
	printf("%f", vertexList->at(0).posicion.x);
	/*
	std::ifstream fin;
	fin.open(fileName);
	
	int numVertex=0;
	fin>>numVertex;
	for(int i=0;i<numVertex;i++)
	{
		vertex_t v1;
		fin>>v1.posicion.x;
		fin>>v1.posicion.y;
		fin>>v1.posicion.z;
		fin>>v1.posicion.w;
		fin>>v1.color.r;
		fin>>v1.color.g;
		fin>>v1.color.b;
		fin>>v1.color.a;
		
		fin>>v1.normal.x;
		fin>>v1.normal.y;
		fin>>v1.normal.z;
		fin>>v1.normal.w;

		fin >> v1.texCoord.x;
		fin >> v1.texCoord.y;

		vertexList->push_back(v1);	
	}
	int numFaces=0;
	fin>>numFaces;
	for(int i=0;i<numFaces;i++)
	{
		int v1,v2,v3;
		fin>>v1;
		fin>>v2;
		fin>>v3;
		faceList->push_back(v1);			
		faceList->push_back(v2);
		faceList->push_back(v3);	
	}
	
	std::string vshader;
	fin>>vshader;
	std::string fshader;
	fin>>fshader;

	std::string textureFile;
	fin >> textureFile;

	fin.close();
	*/
	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";
	std::string textureFile = "data/front.png";

	shader=new GLShader(vshader,fshader);
	tex = new Texture(textureFile);
	printf("Completado!");
	
}



Mesh::~Mesh(){
	
	delete vertexList;
	delete faceList;
}
