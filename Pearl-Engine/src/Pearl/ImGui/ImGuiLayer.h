//
// Created by Andrew Graser on 2/10/2024.
//

#ifndef PEARL_IMGUILAYER_H
#define PEARL_IMGUILAYER_H

#include "Pearl/Layer.h"
#include "Pearl/Events/MouseEvent.h"
#include "Pearl/Events/KeyEvent.h"
#include "Pearl/Events/ApplicationEvent.h"

namespace Pearl {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();


        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;


    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleassedEvent &e);
        bool OnMouseMovedEvent(MouseMovedEvent &e);
        bool OnMouseScrolledEvent(MouseScrolledEvent &e);
        bool OnKeyPressedEvent(KeyPressedEvent &e);
        bool OnKeyReleasedEvent(KeyReleasedEvent &e);
        bool OnKeyTypedEvent(KeyTypedEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);


    private:
        float mTime = 0.0f;
    };
}


#endif //PEARL_IMGUILAYER_H
