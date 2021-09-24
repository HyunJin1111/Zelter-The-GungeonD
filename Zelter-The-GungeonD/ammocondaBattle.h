#pragma once
#include "gameNode.h"
#include "ammoconda.h"
#include "ammocondaMap.h"

class ammocondaBattle : public gameNode
{
private:
	ammoconda* _ammoconda;
	player* _player;

	//¸Ê°ü·Ã
	ammocondaMap* _ammocondaMap;
	POINT _mapMouse;

public:
	ammocondaBattle();
	~ammocondaBattle();

	HRESULT init();
	void release();
	void update();
	void render();
};

