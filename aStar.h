#pragma once
#include "gameNode.h"
class aStar : public gameNode
{
private:


public:
	aStar();
	~aStar();

	HRESULT init();
	void release();
	void update();
	void render();
};

