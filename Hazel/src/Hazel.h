#pragma once

// For use by Hazel applications
#include "hazel\Application.h"
#include "hazel\Layer.h"
#include "hazel\Log.h"

#include "hazel\Input.h"
#include "hazel\KeyCodes.h"
#include "hazel\MouseButtonCodes.h"
#include "hazel\CameraController.h"

// -------- Imgui --------------------
#include "hazel\imgui\ImGuiLayer.h"


// -------- Core --------------------
#include "hazel\Core\Timestep.h"


// -------- Event --------------------
#include "hazel\events\AppEvent.h"
#include "hazel\events\KeyEvent.h"
#include "hazel\events\MouseEvent.h"


// -------- Renderer --------------------
#include "hazel\renderer\Buffer.h"
#include "hazel\renderer\Shader.h"
#include "hazel\renderer\Texture.h"
#include "hazel\\renderer\VertexArray.h"

#include "hazel\renderer\Camera.h"

#include "hazel\renderer\Renderer.h"
#include "hazel\renderer\RenderCommend.h"



// -------Entry Point -------------------
#include "hazel\EntryPoint.h"
