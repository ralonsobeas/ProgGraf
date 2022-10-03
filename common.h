#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <list>
#include <map>
#include <string>


#define ENEMY_OBJ 		0b1
#define BULLET_OBJ 		0b10
#define SPACESHIP_OBJ 	0b100
#define CUBE_OBJ 		0b1000
#define BACKGROUND_OBJ	0b10000
#define ITEM_OBJ		0b100000
