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


        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();


    private:
        float mTime = 0.0f;
    };
}


#endif //PEARL_IMGUILAYER_H
