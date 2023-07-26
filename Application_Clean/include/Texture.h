#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Texture
{
public:
	Texture(char const* path, int unit);
	unsigned int getID() { return textureID; }
	unsigned int getTexUnit() { return texUnit; }
	unsigned int getcreateTex() { return createTex; }

private:
	unsigned int loadTexture(char const* path);
	unsigned int textureID; //Texture handle
	unsigned int createTex;
	char const* path;
	int m_width, m_height, m_nrComponents;
	int map;
	int texUnit;


	
};