#pragma once
#include "playerState.h"

class player;

class playerStateIdle : public playerState
{

public:

	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);

	virtual int getFrameCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }

};

