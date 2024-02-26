//
// Created by Andrew Graser on 2/24/2024.
//


#include "RenderCommand.h"
#include "Pearl/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Pearl {
    RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}