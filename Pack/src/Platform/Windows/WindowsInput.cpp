#include "Packpch.h"
#include "WindowsWindow.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Pack/Application.h"

namespace Pack
{
	Input* Input::s_Instance = new WindowsInput();

	bool Pack::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* const window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* const window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return y;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* const window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}
}