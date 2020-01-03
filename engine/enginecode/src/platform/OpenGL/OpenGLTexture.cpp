/** \file OpenGLTexture.cpp
*	\brief
*/

#include "engine_pch.h"
#include <stb_image.h>
#include "include/platform/OpenGL/OpenGLTexture.h"

namespace Engine {
	

	OpenGLTexture::OpenGLTexture(const std::string& filepath)
	{
		static int m_texSlot;

		unsigned char *texData = stbi_load(filepath.c_str(), &m_data.m_width, &m_data.m_height, &m_data.m_channels, 0);

		glGenTextures(1, &m_objID);
		
		glActiveTexture(GL_TEXTURE0 + m_texSlot);
		m_data.m_slot = m_texSlot;
		m_texSlot++;
		glBindTexture(GL_TEXTURE_2D, m_objID);

		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		 if (m_data.m_channels == 3) {
			 glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_data.m_width, m_data.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			 glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		 }
		 else if (m_data.m_channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_data.m_width, m_data.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		 else if (m_data.m_channels == 1)
		 {
			 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			 glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_data.m_width, m_data.m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
			 glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		 }
		 else return;

		 glGenerateMipmap(GL_TEXTURE_2D);
		 stbi_image_free(texData);
	}

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		m_data.m_width = width;
		m_data.m_height = height;
		m_data.m_channels = channels;

		glGenTextures(1, &m_objID);

		glActiveTexture(GL_TEXTURE0 + m_data.m_slot);
		m_data.m_slot++;
		glBindTexture(GL_TEXTURE_2D, m_objID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_data.m_channels == 3) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_data.m_width, m_data.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else if (m_data.m_channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_data.m_width, m_data.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		else if (m_data.m_channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_data.m_width, m_data.m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else return;

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_objID);
	}

	
}