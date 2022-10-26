#include "mesh.h"
#include "loaderOBJ.hpp"
#include <iostream>
#include <fstream>


Mesh::Mesh(){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();

//añadir vértices
	int size = 50;


	for (int x = 0; x <= size; x++) {
		for (int y = 0; y <= size; y++) {
			vertex_t v1;
			v1.posicion = glm::vec4(0.0f + y, 0.0f + x, 0.0f, 1.0f);
			vertexList->push_back(v1);
		}
		for (int y = 0; y < size; y++) {
			if (x == 0)
				break;
			if (x == 1) {
				faceList->push_back(y);
				faceList->push_back(1 + y);
				faceList->push_back(x * size + 1 + y);
			}
			else {
				faceList->push_back(y + ((x - 1) * size) + x - 1);
				faceList->push_back(y + ((x - 1) * size) + x);
				faceList->push_back(x * size + 1 + y + x - 1);
			}
			
		}
		for (int y = 0; y < size; y++) {
			if (x == 0)
				break;
			faceList->push_back(y + ((x - 1) * size) + x);
			faceList->push_back(x * size + y + x);
			faceList->push_back(x * size + y + x + 1);
		}
		
	}
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
