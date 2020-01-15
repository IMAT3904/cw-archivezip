/** \file .h
*	\brief
*/

#pragma once

namespace Engine {

	/**	\class
	*	\brief
	*/

	class RenderCommand
	{
	public:
		virtual void action() = 0; //!< action a render command
		static RenderCommand * ClearDepthColorBufferCommand();
		static RenderCommand * setClearColourCommand(float r, float g, float b, float a);
		static RenderCommand * setDepthTestLessCommand(bool enabled);
		static RenderCommand * setBackfaceCullingCommand(bool enabled);
		static RenderCommand * setOneMinusAlphaBlending(bool enabled);
	};

}