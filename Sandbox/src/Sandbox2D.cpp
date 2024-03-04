//
// Created by Andrew Graser on 3/2/2024.
//

#include "Sandbox2D.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
    : Pearl::Layer("Sandbox 2D"), mCameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach() {
    mTexture = Pearl::Texture2D::Create("../../assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Pearl::Timestep ts) {
    mCameraController.OnUpdate(ts);

    Pearl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pearl::RenderCommand::Clear();

    Pearl::Renderer2D::BeginScene(mCameraController.GetCamera());

    Pearl::Renderer2D::DrawQuad({0.0f, 0.0f}, {0.5f, 0.5f}, mSquareColor);
    Pearl::Renderer2D::DrawQuad({1.0f, 0.0f, -0.1f}, {4.0f, 4.0f}, mTexture);

    Pearl::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Pearl::Event &e) {
    mCameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Material Editor");

    ImGui::ColorEdit4("Color A", glm::value_ptr(mSquareColor));

    ImGui::End();
}
