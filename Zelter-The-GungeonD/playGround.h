#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "player.h"
#include "playerBullet.h"
#include "niflheim.h"
#include "bulletKing.h"



class playGround : public gameNode
{
private:
	stageManager* _stageManager;
	niflheim* _niflheim;
	bulletKing* _bulletKing;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};


































































