//
// Created by Andrew Graser on 2/8/2024.
//

#ifndef PEARL_WINDOW_H
#define PEARL_WINDOW_H

#include "Events/Event.h"

namespace Pearl {

    struct WindowProps {
        unsigned int Width;
        unsigned int Height;
        const char* Title;

        WindowProps(unsigned int w, unsigned int h, const char* t)
            : Width(w), Height(h), Title(t){

        }

        WindowProps()
            : Width(1280), Height(720), Title("Pearl Engine") {

        }
    };


//TODO: Add support for multiplatform / WIN32 API
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        //Window Attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps &props = WindowProps());

    private:
        WindowProps mProps;
    };

}


#endif //PEARL_WINDOW_H
