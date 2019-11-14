/** \file OpenGLTexture.h
*	\brief
*/

#pragma once
#include <rendering/texture.h>
#include <glad/glad.h>

namespace Engine {

	class texData {
	public:
		int m_width;
		int m_height;
		int m_channels;
		int m_slot;
	};

	class OpenGLTexture : public Texture
	{
	private:
		unsigned int m_objID;
		texData m_data;
	public:

		OpenGLTexture(const std::string& filepath);
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);
		~OpenGLTexture();

		unsigned int getWidth() const override { return m_data.m_width; }
		unsigned int getHeight() const override { return m_data.m_height; }
		unsigned int getChannels() const override { return m_data.m_channels; }
		unsigned int getSlot() const override { return m_data.m_slot; }

		

	};	
}		 