//
// Created by adun on 2017. 11. 20..
//

#ifndef ADUNGL_TILELAYER_H
#define ADUNGL_TILELAYER_H

#include "layer.h"
#include "../batchrenderer2d.h"

namespace AdunGL
{
    namespace graphics
    {
        class TileLayer : public Layer
        {
        public:
            TileLayer(Shader* shader);

            ~TileLayer();
        };
    }
}
#endif //ADUNGL_TILELAYER_H
