#pragma once

#include "Camera.h"
#include "Texture.h"

namespace Hazel {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float dim = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float dim = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float TilingFactor = 1.0f, float dim = 0.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float TilingFactor = 1.0f, float dim = 0.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, float dim = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, float dim = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
			float TilingFactor = 1.0f, float dim = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
			float TilingFactor = 1.0f, float dim = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
	};
}