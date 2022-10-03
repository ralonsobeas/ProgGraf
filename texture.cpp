#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string fileName) {

	//generacion texture ID
	unsigned char* data = NULL;
	glGenTextures(1, &glId);

	//carga de fichero
	data = stbi_load(fileName.c_str(), &w, &h, nullptr, 4);
	//carga de atos en GPU

	glBindTexture(GL_TEXTURE_2D, glId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//liberar datos?
	stbi_image_free(data);


}

void Texture::bind(int textureunitIdx)
{
	glActiveTexture(GL_TEXTURE0 + textureunitIdx);
	glBindTexture(GL_TEXTURE_2D, glId);
}
