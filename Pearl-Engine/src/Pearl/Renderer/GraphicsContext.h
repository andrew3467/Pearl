//
// Created by Andrew Graser on 2/17/2024.
//

#ifndef PEARL_GRAPHICSCONTEXT_H
#define PEARL_GRAPHICSCONTEXT_H

namespace Pearl {
    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif //PEARL_GRAPHICSCONTEXT_H
