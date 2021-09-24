#include "stdafx.h"
#include "startTitle.h"

startTitle::startTitle()
{
}

startTitle::~startTitle()
{
}

HRESULT startTitle::init()
{
	IMAGEMANAGER->addFrameImage("startTitle", L"UI/엔터더_타이틀_100.png", 10, 10);
	IMAGEMANAGER->addImage("logo", L"UI/로고.png");
	_backGroundImg = IMAGEMANAGER->findImage("startTitle");
	_titleImg = IMAGEMANAGER->findImage("logo");
	_count = _currentFrameX = 0;

	return S_OK;
}

void startTitle::release()
{
}

void startTitle::update()
{
	_count++;

	if (_count % 7 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX >= 10)
		{
			_currentFrameY++;
			_currentFrameX = 0;
		}
		if (_currentFrameY >= 10)
		{
			_currentFrameY = 0;
			_currentFrameX = 0;
		}
		_count = 0;
	}
	_gameStartRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 200, 40);
	_gameQuitRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 150, 200, 40);

	if (PtInRect(&_gameStartRc, _ptMouse)) 
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
		{
			SCENEMANAGER->changeScene("loading");
		}		
	}
	if (PtInRect(&_gameQuitRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
		{
			PostQuitMessage(0);
		}		
	}
}

void startTitle::render()
{
	_backGroundImg->frameRender2(0, 0, _currentFrameX, _currentFrameY);
	_titleImg->render(WINSIZEX / 2 - 370, WINSIZEY / 2 - 200);
	D2DRENDER->DrawRectangle(_gameStartRc, D2DDEFAULTBRUSH::Gray, 4);
	D2DRENDER->RenderTextField(_gameStartRc.left + 40, _gameStartRc.top + 5, L"GAME START", 20, 300, 30, D2DDEFAULTBRUSH::White);
	D2DRENDER->DrawRectangle(_gameQuitRc, D2DDEFAULTBRUSH::Gray, 4);
	D2DRENDER->RenderTextField(_gameQuitRc.left + 45, _gameQuitRc.top + 5, L"GAME QUIT", 20, 300, 30, D2DDEFAULTBRUSH::White);
}
