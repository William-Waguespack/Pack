#include "Packpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Pack/Log.h"

namespace Pack
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : windowHandle(windowHandle)
	{
		PACK_CORE_ASSERT(windowHandle, "Window Handle is Null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PACK_CORE_ASSERT(status, "Failed to initialize GLAD");
		
		PACK_CORE_INFO("OpenGL Info");
		PACK_CORE_INFO("  ->Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PACK_CORE_INFO("  ->Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PACK_CORE_INFO("  ->Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}