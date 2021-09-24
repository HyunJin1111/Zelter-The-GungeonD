#include "stdafx.h"
#include "inGameMap.h"

HRESULT inGameMap::init()
{
	IMAGEMANAGER->addFrameImage("openWorld", L"tileImg/오픈월드.png", 20, 9);
	CAMERAMANAGER->setMapCamera(BACKGROUNDX * 1.5, BACKGROUNDY * 1.5);


	load();

	setDoor();

	return S_OK;
}

void inGameMap::release()
{
}

void inGameMap::update()
{
}

void inGameMap::render()
{
	//지형 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].terrainX, _tile[i].terrainY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}
	}

	//오브젝트 그리기
	/*for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tile[i].object == OBJ_NONE)continue;

		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].objX, _tile[i].objY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}
		D2DRENDER->DrawRectangle(_tile[i].checkRect, D2DDEFAULTBRUSH::Red);
	}*/
	//보스 진입문 렌더
	for (int i = 0; i < 4; i++)
	{
		_bossDoorRect[i].img->render(_bossDoorRect[i].rc.left - CAMERAMANAGER->getX(), _bossDoorRect[i].rc.top - CAMERAMANAGER->getY());
	}
}

void inGameMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("openWorld.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	memset(_pos, 0, sizeof(int) * 2);

	////타일을 불러온 다음 타일이 어떤 지형인지 오브젝트인지 분별
	////해당 타일에 속성 부여

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		if (_tile[i].object == BLOCK ||
			_tile[i].object == BLOCK_BHALF||
			_tile[i].object == BLOCK_LHALF ||
			_tile[i].object == BLOCK_RHALF ||
			_tile[i].object == BLOCK_LTRIPLE ||
			_tile[i].object == BLOCK_RTRIPLE)
		{
			_attribute[i] = NONEMOVE;
		}
	}

	CloseHandle(file);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		_tile[i].sizeX = TILESIZEX * 1.5;
		_tile[i].sizeY = TILESIZEY * 1.5;
		_tile[i].rc.left *= 1.5;
		_tile[i].rc.top *= 1.5;
		_tile[i].rc.right *= 1.5;
		_tile[i].rc.bottom *= 1.5;
		_tile[i].checkRect.left *= 1.5;
		_tile[i].checkRect.top *= 1.5;
		_tile[i].checkRect.right *= 1.5;
		_tile[i].checkRect.bottom *= 1.5;
	}
}

void inGameMap::setDoor()
{
	IMAGEMANAGER->addImage("eggNyngDoor", L"UI/에그냥도어.png");
	IMAGEMANAGER->addImage("niflheimDoor", L"UI/니플헤임도어.png");
	IMAGEMANAGER->addImage("bulletKingDoor", L"UI/총탄킹도어.png");
	IMAGEMANAGER->addImage("ammocondaDoor", L"UI/아모콘다도어.png");

	_bossDoorRect[0].img = IMAGEMANAGER->findImage("eggNyngDoor");
	_bossDoorRect[1].img = IMAGEMANAGER->findImage("niflheimDoor");
	_bossDoorRect[2].img = IMAGEMANAGER->findImage("bulletKingDoor");
	_bossDoorRect[3].img = IMAGEMANAGER->findImage("ammocondaDoor");

	_bossDoorRect[0].x = 6900;
	_bossDoorRect[0].y = 350;
	_bossDoorRect[1].x = 450;
	_bossDoorRect[1].y = 2600;
	_bossDoorRect[2].x = 6180;
	_bossDoorRect[2].y = 5500;
	_bossDoorRect[3].x = 10450;
	_bossDoorRect[3].y = 200;

	for (int i = 0; i < 4; i++)
	{
		_bossDoorRect[i].rc = RectMakeCenter(_bossDoorRect[i].x, _bossDoorRect[i].y, _bossDoorRect[i].img->getWidth(), _bossDoorRect[i].img->getHeight());
	}
}

