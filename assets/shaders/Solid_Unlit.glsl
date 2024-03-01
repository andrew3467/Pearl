#type vertex
#version 460 core

layout(location = 0) in vec3 aPosition;

uniform mat4 uViewProjection;
uniform mat4 uTransform;

out vec3 vPosition;

void main() {
    vPosition = aPosition;

    gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec3 vPosition;

uniform vec4 uColor;

void main() {
    color = uColor;
}