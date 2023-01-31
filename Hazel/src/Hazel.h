#pragma once

// For use by Hazel applications
#include "hazel\Application.h"
#include "hazel\Layer.h"
#include "hazel\Log.h"

#include "hazel\Input.h"
#include "hazel\KeyCodes.h"
#include "hazel\MouseButtonCodes.h"

// -------- Imgui --------------------
#include "hazel\imgui\ImGuiLayer.h"
// -------- Imgui --------------------

// -------- Core --------------------
#include "hazel\Core\Timestep.h"
// -------- Core --------------------

// -------- Event --------------------
#include "hazel\events\AppEvent.h"
#include "hazel\events\KeyEvent.h"
#include "hazel\events\MouseEvent.h"
// -------- Event --------------------

// -------- Renderer --------------------
#include "hazel\renderer\Buffer.h"
#include "hazel\renderer\Shader.h"
#include "hazel\\renderer\VertexArray.h"

#include "hazel\renderer\Camera.h"

#include "hazel\renderer\Renderer.h"
#include "hazel\renderer\RenderCommend.h"
// -------- Renderer --------------------


// -------Entry Point -------------------
#include "hazel\EntryPoint.h"
// -------Entry Point -------------------