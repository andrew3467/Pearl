//
// Created by Andrew Graser on 2/12/2024.
//

#ifndef PEARL_WINDOWSINPUT_H
#define PEARL_WINDOWSINPUT_H

#include "Pearl/Input.h"


namespace Pearl {
    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual std::pair<float, float> GetMousePosImpl() override;
    };
}


#endif //PEARL_WINDOWSINPUT_H
