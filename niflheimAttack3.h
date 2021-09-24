#pragma once
#include "state.h"
#include "player.h"

class niflheim;

class niflheimAttack3 : public state
{
	int _bulletCount;
	int _fireBullet;
	float _targetX, _targetY;
	int _icePillar1, _icePillar2;

public:
	virtual state* inputHandle(niflheim* niflheim);
	virtual void update(niflheim* niflheim);
	virtual void enter(niflheim* niflheim);
	virtual void exit(niflheim* niflheim);
	virtual void render(niflheim* niflheim);

	void iceBulletFire(niflheim* niflheim, float targetX, float targetY);
};

