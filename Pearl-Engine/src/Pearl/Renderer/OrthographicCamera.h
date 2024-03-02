//
// Created by Andrew Graser on 2/25/2024.
//

#ifndef PEARL_ORTHOGRAPHICCAMERA_H
#define PEARL_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>

namespace Pearl {
    class OrthographicCamera {
    public:
        //  Near / Far default to -1 to 1
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const {return mPosition;}

        float GetRotation() const {return mRotation;}
        void SetPosition(const glm::vec3& position){mPosition = position; RecalculateViewMatrix();}

        void SetRotation(const float rotation){mRotation = rotation; RecalculateViewMatrix();}

        const glm::mat4& GetProjectionMatrix() const {return mProjectionMatrix;}
        const glm::mat4& GetViewMatrix() const {return mViewMatrix;}
        const glm::mat4& GetViewProjectionMatrix() const {return mViewProjectionMatrix;}


    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
        glm::mat4 mViewProjectionMatrix;

        glm::vec3 mPosition;
        float mRotation = 0;
    };
}

#endif //PEARL_ORTHOGRAPHICCAMERA_H
