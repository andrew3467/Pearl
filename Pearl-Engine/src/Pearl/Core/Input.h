//
// Created by Andrew Graser on 2/12/2024.
//

#ifndef PEARL_INPUT_H
#define PEARL_INPUT_H

#include <utility>
#include "Pearl/Core/Core.h"

namespace Pearl {
    class Input {
    public:
        inline static bool IsKeyPressed(int keycode) {return sInstance->IsKeyPressedImpl(keycode);}

        inline static bool IsMouseButtonPressed(int button) {return sInstance->IsMouseButtonPressedImpl(button);}
        inline static float GetMouseX() {return sInstance->GetMouseXImpl();}
        inline static float GetMouseY() {return sInstance->GetMouseYImpl();}
        inline static std::pair<float, float> GetMousePos() {return sInstance->GetMousePosImpl();}

    protected:
        //Per platform implementations
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;

    public:
        static Input* sInstance;
    };
}

#endif //PEARL_INPUT_H
