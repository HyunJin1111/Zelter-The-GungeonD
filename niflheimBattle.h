#pragma once
#include "gameNode.h"
#include "niflheim.h"
#include "player.h"
#include "niflheimMap.h"

class niflheimBattle : public gameNode
{
	niflheim*	_niflheim;
	player*		_player;

	niflheimMap* _niflheimMap;

	image*	_backGround;

public :
	niflheimBattle() {};
	~niflheimBattle() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

