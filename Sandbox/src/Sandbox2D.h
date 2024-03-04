//
// Created by Andrew Graser on 3/2/2024.
//

#ifndef SANDBOX_SANDBOX2D_H
#define SANDBOX_SANDBOX2D_H

#include <Pearl.h>


class Sandbox2D : public Pearl::Layer {
public:
    Sandbox2D();
    ~Sandbox2D() = default;


    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Pearl::Timestep ts) override;
    void OnEvent(Pearl::Event &e) override;
    void OnImGuiRender() override;

private:
    Pearl::OrthographicCameraController mCameraController;

    Pearl::Ref<Pearl::Texture2D> mTexture;

    glm::vec4 mSquareColor = {0.2f, 0.3f, 0.8f, 1.0f};


};


#endif //SANDBOX_SANDBOX2D_H
