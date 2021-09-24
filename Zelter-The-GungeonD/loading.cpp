#include "stdafx.h"
#include "loading.h"

loading::loading()
{
}

loading::~loading()
{
}

HRESULT loading::init()
{
	IMAGEMANAGER->addFrameImage("고양이로딩", L"UI/고양이_11.png", 11, 1);
	_loadingImage = IMAGEMANAGER->findImage("고양이로딩");
	_currentFrameX = _count = 0;
	_loadingTextCount = 0;
	_loadingText = "L O A D I N G . . . . . .";
	_loadingRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);


	CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadFunction,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		NULL,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);

	return S_OK;
}

void loading::release()
{
}

void loading::update()
{
	_count++;
	if (_count % 10 == 0) 
	{
		_currentFrameX++;
		_loadingTextCount++;
		if (_currentFrameX >= 10) _currentFrameX = 0;
	}
	strncpy_s(_loadingTextCut, sizeof(_loadingTextCut), _loadingText, _loadingTextCount * 2);
	
	if (_loadingTextCount >= strlen(_loadingText)) _loadingTextCount = 0;

	//로딩 후 씬 변경
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("openWorld");
	}
}

void loading::render()
{
	D2DRENDER->FillRectangle(_loadingRect, D2DDEFAULTBRUSH::Black);
	_loadingImage->frameRender2(WINSIZEX / 2 - _loadingImage->getFrameWidth() / 2, WINSIZEY / 2 - _loadingImage->getFrameHeight() / 2, _currentFrameX, 0);
	D2DRENDER->RenderTextField(WINSIZEX / 2 - 100, WINSIZEY / 2 + 100, ConvertCtoWC(_loadingTextCut), D2D1::ColorF::White, 25, 500, 200, 1);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	loading* loadingHelper = (loading*)lpParameter;


	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		Sleep(1);

		loadingHelper->_currentCount++;

	}

	return 0;
}
