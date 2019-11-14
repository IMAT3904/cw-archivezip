/** \file OpenGLShader.h
*	\brief
*/

#pragma once
#include "windows/window.h"
#include <gl/GL.h>
#include "rendering/shader.h"

namespace Engine {

	/**	\class OpenGLShader
	*	\brief 
	*/
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~OpenGLShader();


	private:
	};
}
