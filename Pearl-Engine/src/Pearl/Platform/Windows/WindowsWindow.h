//
// Created by Andrew Graser on 2/8/2024.
//

#ifndef PEARL_WINDOWSWINDOW_H
#define PEARL_WINDOWSWINDOW_H


#include "Pearl/Window.h"
#include "Pearl/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Pearl {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps &props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return mData.Width;}
        inline unsigned int GetHeight() const override { return mData.Height;}

        inline void SetEventCallback(const EventCallbackFn &callback) override {
            mData.EventCallback = callback;
        }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline void* GetNativeWindow() const override {return mWindow;}



    private:
        void Init(const WindowProps &props);
        void Shutdown();

    private:
        GLFWwindow* mWindow;

        GraphicsContext *mContext;

        struct WindowData{
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        } mData;
    };
}


#endif //PEARL_WINDOWSWINDOW_H
