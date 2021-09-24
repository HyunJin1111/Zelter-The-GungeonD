#pragma once
#include "gameNode.h"

class player;

class playerState : public gameNode
{
protected:

	string _stateName;

	image* _img;
	int _count;
	int _currentFrameX, _currentFrameY;
	int _blink;

	float _jumpPower;
	float _gravity;

public:

	virtual playerState* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;

	virtual string getCurrentStateName() { return _stateName; }
	virtual image* getCurrentStateImg() { return _img; }
	virtual int getFramCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }

};

