//
// Created by Andrew Graser on 2/9/2024.
//

#ifndef PEARL_LAYER_H
#define PEARL_LAYER_H


#include "Pearl/Events/Event.h"
#include "Pearl/Core/Timestep.h"

namespace Pearl {
    class Layer {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}

        virtual void OnEvent(Event &event) {}

        inline const std::string& GetName() const {return mDebugName;}

    private:
        std::string mDebugName;
    };
}


#endif //PEARL_LAYER_H
