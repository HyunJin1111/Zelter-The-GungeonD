#include "stdafx.h"
#include "mapmap.h"

//HRESULT mapmap::init()
//{
//	setup();
//
//	return S_OK;
//}
//
//void mapmap::release()
//{
//}
//
//void mapmap::update()
//{
//	if (KEYMANAGER->isStayKeyDown(VK_LEFT))CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 25.f);
//	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 25.f);
//	if (KEYMANAGER->isStayKeyDown(VK_UP))CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 25.f);
//	if (KEYMANAGER->isStayKeyDown(VK_DOWN))CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 25.f);
//
//	cout << _mapMouse.x << "X" << endl;
//	cout << _mapMouse.y << "Y" << endl;
//	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse, 10); // <--- 이 함수 플레이어 기준으로 움직이게 바꿔야 함
//	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
//	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
//
//	tapTool();
//	if (_tool.isOn)	dragField();
//
//	setMap();
//}
//
//void mapmap::render()
//{
//	맵 타일 그리기
//	mapClipping();
//
//	샘플 타일 그리기
//	sampleRender();
//
//
//}
//
//void mapmap::save()
//{
//	HANDLE file;
//	DWORD write;
//
//	LPCSTR str;
//	str = _tileInfo.name.c_str();
//
//	file = CreateFile(str, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	WriteFile(file, _tile, sizeof(tagTile)* TILEX * TILEY, &write, NULL);
//	CloseHandle(file);
//}
//
//void mapmap::load()
//{
//	HANDLE file;
//	DWORD read;
//
//	LPCSTR str;
//	str = _tileInfo.name.c_str();
//
//
//	file = CreateFile(str, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
//	CloseHandle(file);
//}
//
//void mapmap::clear()
//{
//	for (int i = 0; i < TILEX*TILEY; i++)
//	{
//		_tile[i].checkRect = { 0 };
//
//		switch (_tileInfo.type)
//		{
//		case OPENWORLD:
//			_tile[i].terrainX = 0;
//			_tile[i].terrainY = 2;
//			break;
//		case BULLETKING:
//			_tile[i].terrainX = 2;
//			_tile[i].terrainY = 0;
//			break;
//		case AMOCONDA:
//			_tile[i].terrainX = 4;
//			_tile[i].terrainY = 0;
//			break;
//		case EGGNYANG:
//			_tile[i].terrainX = 19;
//			_tile[i].terrainY = 0;
//			break;
//		case NIFLHEIM:
//			_tile[i].terrainX = 19;
//			_tile[i].terrainY = 0;
//			break;
//		}
//		_tile[i].objX = 0;
//		_tile[i].objY = 0;
//		_tile[i].terrain = CEMENT;
//		_tile[i].object = OBJ_NONE;
//		_tile[i].sizeX = TILESIZEX;
//		_tile[i].sizeY = TILESIZEY;
//		_tile[i].isMove = true;
//	}
//}
//
//
//
//void mapmap::setup()
//{
//	setImage();
//	setCamera(BACKGROUNDX, BACKGROUNDY);
//
//	_changeCount = 0;
//	_tileInfo.type = AMOCONDA;
//
//	_dragStart = false;
//
//	_dragMouse.currentStartX = 0;
//	_dragMouse.currentStartY = 0;
//	_dragMouse.currentEndY = 0;
//	_dragMouse.currentEndY = 0;
//	_dragMouse.start.x = 0;
//	_dragMouse.start.y = 0;
//	_dragMouse.end.x = 0;
//	_dragMouse.end.y = 0;
//
//
//	_tool.rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 600);
//	_tool.width = _tool.rc.right - _tool.rc.left;
//	_tool.height = _tool.rc.bottom - _tool.rc.top;
//	_tool.isOn = false;
//
//	_sampleImg = IMAGEMANAGER->findImage("amoconda");
//	_tileInfo.name = "amoconda";
//	changeSample();
//
//	_message = RectMake(_tool.rc.right - 250, _tool.rc.top + 50, 200, 30);
//
//	_btnSave.rc = RectMake(_tool.rc.left + 50, 550, 100, 30);
//	_btnLoad.rc = RectMake(_tool.rc.left + 150, 550, 100, 30);
//	_btnTerrain.rc = RectMake(_tool.rc.left + 50, 500, 100, 30);
//	_btnObject.rc = RectMake(_tool.rc.left + 150, 500, 100, 30);
//	_btnEraser.rc = RectMake(_tool.rc.left + 250, 500, 100, 30);
//	_btnClear.rc = RectMake(_tool.rc.left + 350, 500, 100, 30);
//	_btnEnter.rc = RectMake(_tool.rc.right - 150, _tool.rc.bottom - 80, 100, 30);
//	_btnPrevios.rc = RectMake(_tileInfo.rc.left - 100, _tileInfo.rc.top, 50, _tileInfo.height);
//	_btnNext.rc = RectMake(_tileInfo.rc.right + 50, _tileInfo.rc.top, 50, _tileInfo.height);
//
//	처음 상태는 지형을 선택 한 것으로
//	_ctrlSelect = CTRL_TERRAINDRAW;
//
//	샘플 타일셋 먼저 셋팅
//	for (int i = 0; i < SAMPLETILEY; i++)
//	{
//		for (int j = 0; j < SAMPLETILEX; j++)
//		{
//			_sample[i*SAMPLETILEX + j].frameX = j;
//			_sample[i*SAMPLETILEX + j].frameY = i;
//
//			샘플 타일에 렉트를 씌움
//			/*==============================
//			@@렉트
//			@@left		(WINSIZEX - 이미지너비) + (j * 타일사이즈X)
//			@@top		i * TILEYSIZE
//			@@right		(WINSIZEX - 이미지너비) + (j * 타일사이즈X) + 타일사이즈X
//			@@bottom	(i * TILEYSIZE) + TILESIZE
//			==============================*/
//			SetRect(&_sample[i*SAMPLETILEX + j].rc,
//				(_tool.rc.left + 50) + j * TILESIZEX,
//				(_tool.rc.top + 100) + i * TILESIZEY,
//				(_tool.rc.left + 50) + j * TILESIZEX + TILESIZEX,
//				(_tool.rc.top + 100) + i * TILESIZEY + TILESIZEY);
//		}
//	}
//
//	맵 타일 영역
//	for (int i = 0; i < TILEY; i++)
//	{
//		for (int j = 0; j < TILEX; j++)
//		{
//			SetRect(&_tile[i*TILEX + j].rc,
//				j*TILESIZEX,
//				i*TILESIZEY,
//				j*TILESIZEX + TILESIZEX,
//				i*TILESIZEY + TILESIZEY);
//		}
//	}
//
//	맵 타일 셋팅
//	for (int i = 0; i < TILEX *TILEY; i++)
//	{
//		_tile[i].terrainX = 0;
//		_tile[i].terrainY = 2;
//		_tile[i].objX = 0;
//		_tile[i].objY = 0;
//		_tile[i].terrain = CEMENT;
//		_tile[i].object = OBJ_NONE;
//		_tile[i].sizeX = TILESIZEX;
//		_tile[i].sizeY = TILESIZEY;
//		_tile[i].isMove = true;
//	}
//
//}
//
//void mapmap::setImage()
//{
//	IMAGEMANAGER->addFrameImage("openWorld", L"tileImg/오픈월드.png", SAMPLETILEX, SAMPLETILEY);
//	IMAGEMANAGER->addFrameImage("bulletKing", L"tileImg/총탄킹.png", SAMPLETILEX, SAMPLETILEY);
//	IMAGEMANAGER->addFrameImage("amoconda", L"tileImg/아모콘다.png", SAMPLETILEX, SAMPLETILEY);
//	IMAGEMANAGER->addFrameImage("dunBoss", L"tileImg/던그리드보스.png", SAMPLETILEX, SAMPLETILEY);
//}
//
//void mapmap::setMap()
//{
//
//	맵 타일 그리기(마우스로)
//	if (_leftButtonDown && !_tool.isOn &&
//		!PtInRect(&_btnSave.rc, _ptMouse) &&
//		!PtInRect(&_btnLoad.rc, _ptMouse) &&
//		!PtInRect(&_btnEnter.rc, _ptMouse))
//	{
//		int current = (_mapMouse.y / 32)*TILEX + (_mapMouse.x / 32);
//
//		int sizeX = (_dragMouse.currentEndX + 1 - _dragMouse.currentStartX);
//		int sizeY = (_dragMouse.currentEndY + 1 - _dragMouse.currentStartY);
//
//
//
//
//		switch (_ctrlSelect)
//		{
//		case CTRL_TERRAINDRAW:
//			for (int i = 0; i < sizeY; ++i)
//			{
//				for (int j = 0; j < sizeX; ++j)
//				{
//					_tile[i*TILEX + current + j].terrainX = _dragMouse.currentStartX + j;
//					_tile[i*TILEX + current + j].terrainY = _dragMouse.currentStartY + i;
//					_tile[i*TILEX + current + j].isMove = true;
//					_tile[i*TILEX + current + j].terrain = terrainSelect(
//						_tile[i*TILEX + current + j].terrainX,
//						_tile[i*TILEX + current + j].terrainY);
//					setTerrainRect(_tile[i*TILEX + current + j].terrain, current);
//				}
//			}
//			break;
//		case CTRL_OBJDRAW:
//			for (int i = 0; i < sizeY; ++i)
//			{
//				for (int j = 0; j < sizeX; ++j)
//				{
//					_tile[i*TILEX + current + j].objX = _dragMouse.currentStartX + j;
//					_tile[i*TILEX + current + j].objY = _dragMouse.currentStartY + i;
//					_tile[i*TILEX + current + j].object = objSelect(
//						_tile[i*TILEX + current + j].objX,
//						_tile[i*TILEX + current + j].objY);
//					_tile[i*TILEX + current + j].isMove = true;
//					setObjectRect(_tile[i*TILEX + current + j].object, i*TILEX + current + j);
//				}
//			}
//			break;
//			vector 타입의 타일이라서(_vTile) 지우개가 안됨 
//			_vTile[current]의 current의 조건을 찾아 거기의 오브젝트를 NONE으로 바꿔줘야함
//		case CTRL_ERASER:
//			_tile[current].objX = NULL;
//			_tile[current].objY = NULL;
//			_tile[current].object = OBJ_NONE;
//			break;
//		}
//	}
//
//
//
//}
//
//void mapmap::setCamera(int mapSizeX, int mapSizeY)
//{
//	CAMERAMANAGER->setMapCamera(mapSizeX, mapSizeY);
//	CAMERAMANAGER->setCamera(WINSIZEX, WINSIZEY);
//}
//
//void mapmap::mapClipping()
//{
//
//
//	지형 그리기
//	for (int i = 0; i < TILEX * TILEY; ++i)
//	{
//		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
//			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
//			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
//			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
//		{
//
//			_sampleImg->cutRender(
//				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
//				_tile[i].terrainX, _tile[i].terrainY,
//				_tile[i].sizeX, _tile[i].sizeY
//			);
//		}
//
//	}
//
//	오브젝트 그리기
//	for (int i = 0; i < TILEX * TILEY; ++i)
//	{
//		obj_none 떄메 안나옴 이거 해결해야함 빼면 안됨
//		if (_tile[i].object == OBJ_NONE)continue;
//
//		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
//			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
//			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
//			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
//		{
//
//			_sampleImg->cutRender(
//				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
//				_tile[i].objX, _tile[i].objY,
//				_tile[i].sizeX, _tile[i].sizeY
//			);
//		}
//		D2DRENDER->DrawRectangle(_tile[i].checkRect, D2DDEFAULTBRUSH::Green, 5.f);
//
//	}
//
//}
//
//void mapmap::sampleRender()
//{
//	if (_tool.isOn)
//	{
//		D2DRENDER->FillRectangle(_tool.rc, D2D1COLOR::Black, 0.7f);
//		D2DRENDER->DrawRectangle(_tileInfo.rc, D2DDEFAULTBRUSH::Red);
//		D2DRENDER->RenderTextField(
//			_tileInfo.rc.left, _tileInfo.rc.top,
//			ConvertStoWS(_tileInfo.name),
//			20,
//			_tileInfo.width, _tileInfo.height,
//			D2DDEFAULTBRUSH::Red,
//			DWRITE_TEXT_ALIGNMENT_CENTER);
//
//		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
//		{
//			_sampleImg->cutRender(
//				_sample[i].rc.left,
//				_sample[i].rc.top,
//				_sample[i].frameX,
//				_sample[i].frameY,
//				TILESIZEX, TILESIZEY
//			);
//			D2DRENDER->DrawRectangle(_sample[i].rc, D2DDEFAULTBRUSH::White);
//		}
//		if (_dragMouse.isDrag)D2DRENDER->DrawRectangle(_dragMouse.rc, D2DDEFAULTBRUSH::Red, 1.f);
//
//		buttonRender();
//	}
//
//	int sizeX = (_dragMouse.currentEndX + 1 - _dragMouse.currentStartX);
//	int sizeY = (_dragMouse.currentEndY + 1 - _dragMouse.currentStartY);
//	if (_dragStart)
//	{
//		_sampleImg->cutRender(
//			_ptMouse.x, _ptMouse.y,													//이미지가 찍힐 left,top
//			_dragMouse.currentStartX, _dragMouse.currentStartY,						//이미지를 짜를 left,top
//			(_dragMouse.currentEndX + 1 - _dragMouse.currentStartX) * TILESIZEX,	//짜른 이미지의 width
//			(_dragMouse.currentEndY + 1 - _dragMouse.currentStartY) * TILESIZEY,	//짜른 이미지의 hegiht
//			0.5f
//		);
//	}
//}
//
//void mapmap::changeSample()
//{
//	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4) && _changeCount > 0)_changeCount--;
//	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6) && _changeCount < 4)_changeCount++;
//
//	switch (_changeCount)
//	{
//	case 0:
//		_sampleImg = IMAGEMANAGER->findImage("openWorld");
//		_tileInfo.name = "openWorld.map";
//		_tileInfo.type = OPENWORLD;
//		setCamera(BACKGROUNDX, BACKGROUNDY);
//		break;
//	case 1:
//		_sampleImg = IMAGEMANAGER->findImage("bulletKing");
//		_tileInfo.name = "bulletKing.map";
//		_tileInfo.type = BULLETKING;
//		setCamera(2000, 1000);
//		break;
//	case 2:
//		_sampleImg = IMAGEMANAGER->findImage("amoconda");
//		_tileInfo.name = "amoconda.map";
//		_tileInfo.type = AMOCONDA;
//		setCamera(2000, 1000);
//		break;
//	case 3:
//		_sampleImg = IMAGEMANAGER->findImage("dunBoss");
//		_tileInfo.name = "niflheim.map";
//		_tileInfo.type = NIFLHEIM;
//		setCamera(WINSIZEX, WINSIZEY);
//		break;
//	case 4:
//		_sampleImg = IMAGEMANAGER->findImage("dunBoss");
//		_tileInfo.name = "eggNyang.map";
//		_tileInfo.type = EGGNYANG;
//		setCamera(WINSIZEX, WINSIZEY);
//		break;
//
//	}
//
//	SetRect(&_tileInfo.rc,
//		_tool.rc.left + 200,
//		_tool.rc.top + 30,
//		_tool.rc.left + 500,
//		_tool.rc.top + 80);
//	_tileInfo.width = _tileInfo.rc.right - _tileInfo.rc.left;
//	_tileInfo.height = _tileInfo.rc.bottom - _tileInfo.rc.top;
//}
//
//void mapmap::buttonRender()
//{
//
//	D2DRENDER->FillRectangle(_btnSave.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnSave.rc.left, _btnSave.rc.top,
//		L"세이브",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::White,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->FillRectangle(_btnLoad.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnLoad.rc.left, _btnLoad.rc.top,
//		L"로드",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::White,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_message, D2DDEFAULTBRUSH::Red);
//
//	메세지 관련
//	switch (_ctrlSelect)
//	{
//	case CTRL_TERRAINDRAW:
//		D2DRENDER->RenderTextField
//		(
//			_message.left, _message.top,
//			L"지형 선택",
//			20,
//			200, 30,
//			D2DDEFAULTBRUSH::Red,
//			DWRITE_TEXT_ALIGNMENT_CENTER
//		);
//		break;
//	case CTRL_OBJDRAW:
//		D2DRENDER->RenderTextField
//		(
//			_message.left, _message.top,
//			L"오브젝트 선택",
//			20,
//			200, 30,
//			D2DDEFAULTBRUSH::Red,
//			DWRITE_TEXT_ALIGNMENT_CENTER
//		);
//		break;
//	case CTRL_ERASER:
//		D2DRENDER->RenderTextField
//		(
//			_message.left, _message.top,
//			L"지우개 선택",
//			20,
//			200, 30,
//			D2DDEFAULTBRUSH::Red,
//			DWRITE_TEXT_ALIGNMENT_CENTER
//		);
//		break;
//	}
//
//	D2DRENDER->DrawRectangle(_btnTerrain.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnTerrain.rc.left, _btnTerrain.rc.top,
//		L"지형",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::Red,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_btnObject.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnObject.rc.left, _btnObject.rc.top,
//		L"오브젝트",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::Red,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_btnEraser.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnEraser.rc.left, _btnEraser.rc.top,
//		L"지우개",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::Red,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_btnClear.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnClear.rc.left, _btnClear.rc.top,
//		L"클리어",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::Red,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_btnEnter.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->RenderTextField(
//		_btnEnter.rc.left, _btnEnter.rc.top,
//		L"확인",
//		20,
//		100, 30,
//		D2DDEFAULTBRUSH::Red,
//		DWRITE_TEXT_ALIGNMENT_CENTER);
//
//	D2DRENDER->DrawRectangle(_btnPrevios.rc, D2DDEFAULTBRUSH::Red);
//	D2DRENDER->DrawRectangle(_btnNext.rc, D2DDEFAULTBRUSH::Red);
//
//
//}
//
//void mapmap::tapTool()
//{
//
//	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
//	{
//
//		_dragMouse.currentStartX = 0;
//		_dragMouse.currentStartY = 0;
//		_dragMouse.currentEndX = 0;
//		_dragMouse.currentEndY = 0;
//		_dragMouse.start.x = 0;
//		_dragMouse.start.y = 0;
//		_dragMouse.end.x = 0;
//		_dragMouse.end.y = 0;
//
//		_tool.isOn = true;
//		_dragStart = true;
//	}
//
//}
//
//void mapmap::dragField()
//{
//	changeSample();
//
//	if (_leftButtonDown)
//	{
//		if (PtInRect(&_btnTerrain.rc, _ptMouse))_ctrlSelect = CTRL_TERRAINDRAW;
//		if (PtInRect(&_btnObject.rc, _ptMouse))_ctrlSelect = CTRL_OBJDRAW;
//		if (PtInRect(&_btnEraser.rc, _ptMouse))_ctrlSelect = CTRL_ERASER;
//		if (PtInRect(&_btnClear.rc, _ptMouse))clear();
//		if (PtInRect(&_btnSave.rc, _ptMouse))save();
//		if (PtInRect(&_btnLoad.rc, _ptMouse))load();
//		if (PtInRect(&_btnEnter.rc, _ptMouse))_tool.isOn = false;
//	}
//	for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
//	{
//		if (PtInRect(&_sample[i].rc, _ptMouse))
//		{
//			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//			{
//				_dragMouse.start.x = _sample[i].rc.left;
//				_dragMouse.start.y = _sample[i].rc.top;
//				_dragMouse.currentStartX = _sample[i].frameX;
//				_dragMouse.currentStartY = _sample[i].frameY;
//			}
//			if (_leftButtonDown)
//			{
//				_dragMouse.end.x = _sample[i].rc.right;
//				_dragMouse.end.y = _sample[i].rc.bottom;
//				_dragMouse.currentEndX = _sample[i].frameX;
//				_dragMouse.currentEndY = _sample[i].frameY;
//			}
//			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
//			{
//				_dragMouse.end.x = _sample[i].rc.right;
//				_dragMouse.end.y = _sample[i].rc.bottom;
//				_dragMouse.currentEndX = _sample[i].frameX;
//				_dragMouse.currentEndY = _sample[i].frameY;
//			}
//			_dragMouse.rc = RectMakeDrag(_dragMouse.start.x, _dragMouse.start.y, _dragMouse.end.x, _dragMouse.end.y);
//		}
//	}
//}
//
//TERRAIN mapmap::terrainSelect(int frameX, int frameY)
//{
//	return CEMENT;
//}
//
//void mapmap::setTerrainRect(TERRAIN tr, int num)
//{
//	SetRect(&_tile[num].rc,
//		_tile[num].rc.left,
//		_tile[num].rc.top,
//		_tile[num].rc.left + _tile[num].sizeX,
//		_tile[num].rc.top + _tile[num].sizeY);
//}
//
//OBJECT mapmap::objSelect(int frameX, int frameY)
//{
//	switch (_tileInfo.type)
//	{
//	case OPENWORLD:
//		if ((frameY == 8 && (frameX == 1 || frameX == 4 || frameX == 7)) || (frameX == 11 && frameY == 8))
//		{
//			return BLOCK;
//		}
//		else if ((frameY == 5 && (frameX == 13 || frameX == 14 || frameX == 15)))
//		{
//			return BLOCK;
//		}
//		else if ((frameY == 6 && (frameX == 13 || frameX == 14)))return BLOCK;
//		else if ((frameX == 10 && frameY == 8) ||
//			(frameX == 4 && frameY == 4))
//		{
//			return BLOCK_LHALF;
//		}
//		else if (frameX == 5 && frameY == 4)
//		{
//			return BLOCK_RHALF;
//		}
//		else if (frameX == 4 && frameY == 3)
//		{
//			return BLOCK_LTRIPLE;
//		}
//		else if (frameX == 5 && frameY == 3)
//		{
//			return BLOCK_RTRIPLE;
//		}
//		break;
//	case BULLETKING:
//		if ((frameX == 13 && frameY == 7) ||
//			(frameX == 14 && frameY == 7) ||
//			(frameX == 15 && frameY == 7) ||
//			(frameX == 17 && frameY == 7) ||
//			(frameX == 18 && frameY == 7))
//		{
//			return BLOCK;
//		}
//		break;
//	case AMOCONDA:
//		if ((frameX == 1 && frameY == 5) ||
//			(frameX == 4 && frameY == 5) ||
//			(frameX == 6 && frameY == 5))
//		{
//			return BLOCK;
//		}
//		else if (frameX == 3 && frameY == 5)
//		{
//			return BLOCK_LTRIPLE;
//		}
//		else if (frameX == 5 && frameY == 5)
//		{
//			return BLOCK_RTRIPLE;
//		}
//		break;
//	case NIFLHEIM:
//		if (frameY == 0 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 4 || frameX == 5 || frameX == 6 || frameX == 7 || frameX == 8 ||
//			frameX == 9 || frameX == 10 || frameX == 11 || frameX == 12 || frameX == 13 ||
//			frameX == 14 || frameX == 15 || frameX == 16 || frameX == 17 || frameX == 18))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 1 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 7 || frameX == 8 || frameX == 9 || frameX == 17 || frameX == 18))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 2 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 4 || frameX == 5 || frameX == 6 || frameX == 7 || frameX == 8 ||
//			frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 3 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 4 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 5 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 6 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 7 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 11 ||
//			frameX == 12 || frameX == 13 || frameX == 14 || frameX == 15 || frameX == 16 ||
//			frameX == 17 || frameX == 18 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 8 && (frameX == 0 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		break;
//	case EGGNYANG:
//		if (frameY == 0 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 4 || frameX == 5 || frameX == 6 || frameX == 7 || frameX == 8 ||
//			frameX == 9 || frameX == 10 || frameX == 11 || frameX == 12 || frameX == 13 ||
//			frameX == 14 || frameX == 15 || frameX == 16 || frameX == 17 || frameX == 18))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 1 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 7 || frameX == 8 || frameX == 9 || frameX == 17 || frameX == 18))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 2 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 3 ||
//			frameX == 4 || frameX == 5 || frameX == 6 || frameX == 7 || frameX == 8 ||
//			frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 3 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 4 && (frameX == 0 || frameX == 1 || frameX == 2 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 5 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 6 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 7 && (frameX == 0 || frameX == 9 || frameX == 10 || frameX == 11 ||
//			frameX == 12 || frameX == 13 || frameX == 14 || frameX == 15 || frameX == 16 ||
//			frameX == 17 || frameX == 18 || frameX == 19))
//		{
//			return BLOCK;
//		}
//		else if (frameY == 8 && (frameX == 0 || frameX == 9))
//		{
//			return BLOCK;
//		}
//		break;
//	}
//	return OBJ_Be;
//}
//
//void mapmap::setObjectRect(OBJECT obj, int num)
//{
//	switch (_tileInfo.type)
//	{
//	case OPENWORLD:
//		if (obj == BLOCK)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_LHALF)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left + _tile[num].sizeX / 2,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_RHALF)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right - _tile[num].sizeX / 2,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_LTRIPLE)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left + _tile[num].sizeX / 3,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_RTRIPLE)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right - _tile[num].sizeX / 3,
//				_tile[num].rc.bottom);
//		}
//
//		break;
//	case BULLETKING:
//		if (obj == BLOCK)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		break;
//	case AMOCONDA:
//		if (obj == BLOCK)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_LTRIPLE)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left + _tile[num].sizeX / 3,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		else if (obj == BLOCK_RTRIPLE)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right - _tile[num].sizeX / 3,
//				_tile[num].rc.bottom);
//		}
//		break;
//	case NIFLHEIM:
//		if (obj == BLOCK)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		break;
//	case EGGNYANG:
//		if (obj == BLOCK)
//		{
//			SetRect(&_tile[num].checkRect,
//				_tile[num].rc.left,
//				_tile[num].rc.top,
//				_tile[num].rc.right,
//				_tile[num].rc.bottom);
//		}
//		break;
//	}
//
//
//
//}