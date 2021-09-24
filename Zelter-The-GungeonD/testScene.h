#pragma once
#include "gameNode.h"
#include "mapmap.h"

struct tagUI
{
	image* img;
	RECT rc;
	float x, y;
	float width, height;
};

class testScene : public gameNode
{
private:
	tagUI _title;
	tagUI _mapmap;
	tagUI _inGameButton;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void uiSet();
	void uiRender();
};
