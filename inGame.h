#pragma once
#include "gameNode.h"
#include "inGameMap.h"
#include "niflheimMap.h"
#include "player.h"
#include "dinosaur.h"
#include "fishMan.h"

class inGame : public gameNode
{
private:
	inGameMap* _inGameMap;
	niflheimMap* _niflheimMap;
	player* _player;
	dinosaur* _dinosaur;
	fishMan* _fishMan;
	POINT _mapMouse;
public:
	inGame() {};
	~inGame() {};

	HRESULT init();
	void release();	
	void update();
	void render();

	void collisionDoor();
	void collisionEnemy();


};

