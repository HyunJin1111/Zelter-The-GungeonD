#pragma once
#include "playerState.h"
#include "playerBullet.h"
#include "player.h"

class playerAttack : public playerState
{
	playerBullet* _playerBullet;

	float _pressPower;
	int _pressTime;
	//========================
	POINT _mapMouse;
public :
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);

	virtual int getFrameCount() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

