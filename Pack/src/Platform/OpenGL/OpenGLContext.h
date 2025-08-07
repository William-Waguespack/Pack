#pragma once
#include "Pack/Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace Pack
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* windowHandle;
	};
}