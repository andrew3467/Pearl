//
// Created by Andrew Graser on 3/1/2024.
//

#ifndef PEARL_ORTHOGRAPHICCAMERACONTROLLER_H
#define PEARL_ORTHOGRAPHICCAMERACONTROLLER_H


#include "Pearl/Renderer/OrthographicCamera.h"
#include "Pearl/Core/Timestep.h"

#include "Pearl/Events/Event.h"
#include "Pearl/Events/ApplicationEvent.h"
#include "Pearl/Events/MouseEvent.h"

namespace Pearl {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        OrthographicCamera& GetCamera() {return mCamera;}
        const OrthographicCamera& GetCamera() const {return mCamera;}

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float mAspectRatio;
        float mZoomLevel = 1.0f;

        OrthographicCamera mCamera;

        bool mRotation;

        glm::vec3 mCameraPosition = {0.0f, 0.0f, 0.0f};
        float mCameraRotation = 0.0f;

        float mCameraTranslationSpeed = 2.5f;
        float mCameraRotationSpeed = 180.0f;
    };
}


#endif //PEARL_ORTHOGRAPHICCAMERACONTROLLER_H
