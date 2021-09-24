#pragma once
#include "gameNode.h"


struct tagCharacterPick
{
	RECT rc;
	image* img;
	float x, y;
	int currentFrameX;
	int currentFrameY;

	bool on;
	bool pick;

	
};
class characterPick :public gameNode 
{
private:
	tagCharacterPick _characterPick;
	tagCharacterPick _characterPick2;
	tagCharacterPick _character;
	tagCharacterPick _character2;

	image* _mouse;
	//=============================== 다이얼로그
	RECT _rc;
	RECT _yes;
	RECT _no;
	RECT _noMoneyrc;
	image* _img;
	image* _noMoneyimg;
	const char* _pickText;
	char _pickTextCut[128];
	int _pickTextCount;

	float _noMoney;


public:

	int _count;

	HRESULT init();
	void virtual update();
	void virtual release();
	void virtual render();

	void setImages();
};

