#type vertex
#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform;

out vec2 vTexCoord;


void main() {
    vTexCoord = aTexCoord;

    gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform sampler2D uTexture;

in vec2 vTexCoord;

void main() {
    color = texture(uTexture, vTexCoord * 10.0);
}