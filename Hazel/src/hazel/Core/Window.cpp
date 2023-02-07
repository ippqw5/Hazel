#include "hzpch.h"
#include "Window.h"

#include "Platform\Windows\WindowsWindow.h"

namespace Hazel {
	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}
}