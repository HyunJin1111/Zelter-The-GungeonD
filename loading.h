#pragma once
#include "gameNode.h"

#define LOADINGMAX 200

class loading : public gameNode
{
private:
	RECT _loadingRect;
	image* _loadingImage;
	int _currentFrameX;
	int _count;
	const char* _loadingText;
	char _loadingTextCut[128];
	int _loadingTextCount;
public:
	loading();
	~loading();

	int _currentCount;

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);

