#include "hzpch.h"
#include "Input.h"

#include "Platform\Windows\WindowsInput.h"

namespace Hazel {
	Input* Input::s_Instance = new WindowsInput();
}