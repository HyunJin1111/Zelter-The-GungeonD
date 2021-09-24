#pragma once
#include "playerStateIdle.h"
#include "player.h"

class player;

class playerDonwJump : public playerState
{
	float _jumpPower;
	float _gravity;
public:

	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);

	virtual int getCurrentFrame() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

