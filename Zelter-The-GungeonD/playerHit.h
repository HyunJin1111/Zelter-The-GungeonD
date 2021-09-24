#pragma once
#include "playerState.h"
#include "player.h"

class playerHit : public playerState
{
	
	int _blink;
	
	int _blinkTime;
	int _blinkTimeEnd;
	int _blinkCount;

public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);


	virtual int getFrameCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

