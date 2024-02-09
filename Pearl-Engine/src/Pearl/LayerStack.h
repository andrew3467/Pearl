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
        std::vector<Layer*>::iterator mLayerInsert;
    };
}


#endif //PEARL_LAYERSTACK_H
