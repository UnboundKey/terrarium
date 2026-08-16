//
// Created by socks on 8/16/26.
//

#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizeInPixelsX, int cellSizeInPixelsY) {
    return Rectangle {.x = (float)x*cellSizeInPixelsX, .y = (float)y*cellSizeInPixelsY, .width = (float)cellSizeInPixelsX, .height = (float)cellSizeInPixelsY };
}
