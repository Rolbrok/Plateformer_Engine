#ifndef BLOCK_SLIDERIGHT_H
#define BLOCK_SLIDERIGHT_H

#include "Block.h"

class Block_SlideRight : public Block
{
public:
	Block_SlideRight();
    Block_SlideRight(float x, float y, float size = 0);

private:
    float m_angle = 45.f;
};

#endif
