#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	uiSet();

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	if (PtInRect(&_mapmap.rc, _ptMouse))
	{
		//cout << "?" << endl;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("mapTool");
		}
	}
}

void testScene::render()
{
	uiRender();
}


void testScene::uiSet()
{
	_title.x = WINSIZEX / 2;
	_title.y = 200;
	_title.rc = RectMakeCenter(_title.x, _title.y, 300, 100);
	_title.width = _title.rc.right - _title.rc.left;
	_title.height = _title.rc.bottom - _title.rc.top;

	_mapmap.x = WINSIZEX / 2 - 200;
	//cout << _mapmap.x;

	_mapmap.y = WINSIZEY / 2 + 200;
	_mapmap.rc = RectMakeCenter(_mapmap.x, _mapmap.y, 100, 30);
	_mapmap.width = _mapmap.rc.right - _mapmap.rc.left;
	_mapmap.height = _mapmap.rc.bottom - _mapmap.rc.top;

	_inGameButton.x = WINSIZEX / 2 + 200;
	_inGameButton.y = WINSIZEY / 2 + 200;
	_inGameButton.rc = RectMakeCenter(_inGameButton.x, _inGameButton.y, 100, 30);
	_inGameButton.width = _inGameButton.rc.right - _inGameButton.rc.left;
	_inGameButton.height = _inGameButton.rc.bottom - _inGameButton.rc.top;

}

void testScene::uiRender()
{
	RECT _rc;
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	D2DRENDER->DrawRectangle
	(
		_rc,
		D2DDEFAULTBRUSH::Red
	);
	//제목
	D2DRENDER->DrawRectangle
	(
		_title.rc,
		D2DDEFAULTBRUSH::Red
	);
	D2DRENDER->RenderTextField
	(
		_title.rc.left, _title.rc.top,
		L"제목",
		20,
		_title.width, _title.height,
		D2DDEFAULTBRUSH::Red,
		DWRITE_TEXT_ALIGNMENT_CENTER
	);

	//맵툴
	D2DRENDER->DrawRectangle
	(
		_mapmap.rc,
		D2DDEFAULTBRUSH::Red
	);
	D2DRENDER->RenderTextField
	(
		_mapmap.rc.left, _mapmap.rc.top,
		L"맵툴",
		20,
		_mapmap.width, _mapmap.height,
		D2DDEFAULTBRUSH::Red,
		DWRITE_TEXT_ALIGNMENT_CENTER
	);

	//인게임 게임시작
	D2DRENDER->DrawRectangle
	(
		_inGameButton.rc,
		D2DDEFAULTBRUSH::Red
	);
	D2DRENDER->RenderTextField
	(
		_inGameButton.rc.left, _inGameButton.rc.top,
		L"게임시작",
		20,
		_inGameButton.width, _inGameButton.height,
		D2DDEFAULTBRUSH::Red,
		DWRITE_TEXT_ALIGNMENT_CENTER
	);
}
