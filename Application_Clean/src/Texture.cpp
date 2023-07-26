#include "Texture.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;
Texture::Texture(char const* path,int unit)
{
	textureID = loadTexture(path);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID);
	

}
unsigned int Texture::loadTexture(char const* path)
{
	glGenTextures(1, &textureID);// Generates 1 texture
	unsigned char* m_data = stbi_load(path, &m_width, &m_height, &m_nrComponents, 0);
	if (m_data)
	{
		/**
		* if recieved data successful load
		* if 1 component GL_RED
		* if 3 component GL_RGB
		* if 4 component GL_RGBA
		*/
		//hello
		GLenum format;
		if (m_nrComponents == 1)
			format = GL_RED;
		else if (m_nrComponents == 3)
			format = GL_RGB;
		else if (m_nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID); //Bind texture GL_TEXTURE_2D type
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data); //
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// S = x axis axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// T == y axis, R if 3D
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //zoom in
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //zoom out
		stbi_image_free(m_data);
		cout << "Loaded texture at path: " << path << " width " << m_width << " id " << textureID << endl;

	}
	else
	{
		cout << "Texture failed to load at path: " << path << " width " << m_width << " id " << textureID << endl;
		stbi_image_free(m_data);
	}

	return textureID;
}
