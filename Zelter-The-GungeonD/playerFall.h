#pragma once
#include "playerStateIdle.h"

class player;


class playerFall : public playerStateIdle
{
	
public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);

	virtual int getCurrentFrame() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

