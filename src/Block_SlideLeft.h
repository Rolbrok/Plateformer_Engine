#ifndef BLOCK_SLIDELEFT_H
#define BLOCK_SLIDELEFT_H

#include "Block.h"

class Block_SlideLeft : public Block
{
public:
	Block_SlideLeft();
    Block_SlideLeft(float x, float y, float size = 0);

private:
    float m_angle = -45.f;
};

#endif
