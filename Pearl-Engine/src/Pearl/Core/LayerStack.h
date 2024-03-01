//
// Created by Andrew Graser on 2/9/2024.
//

#ifndef PEARL_LAYERSTACK_H
#define PEARL_LAYERSTACK_H


#include "Layer.h"

namespace Pearl {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() {return mLayers.begin();}
        std::vector<Layer*>::iterator end() {return mLayers.end();}

    private:
        std::vector<Layer*> mLayers;
        unsigned int mLayerInsertIndex = 0;
    };
}


#endif //PEARL_LAYERSTACK_H
