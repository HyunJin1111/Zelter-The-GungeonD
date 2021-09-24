#pragma once
#include "gameNode.h"
class startTitle : public gameNode
{
private:
	image* _backGroundImg;
	image* _titleImg;
	int _count;
	int _currentFrameX;
	int _currentFrameY;


	RECT _gameStartRc;
	RECT _gameQuitRc;
public:
	startTitle();
	~startTitle();

	HRESULT init();
	void release();
	void update();
	void render();

};

