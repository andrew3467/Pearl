//
// Created by Andrew Graser on 3/1/2024.
//

#ifndef PEARL_RENDERER2D_H
#define PEARL_RENDERER2D_H


#include "OrthographicCamera.h"
#include "Texture.h"

namespace Pearl {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation = 0.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation = 0.0f);
    };
}


#endif //PEARL_RENDERER2D_H
