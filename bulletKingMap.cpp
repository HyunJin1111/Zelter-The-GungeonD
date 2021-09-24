#include "stdafx.h"
#include "bulletKingMap.h"

HRESULT bulletKingMap::init()
{
	IMAGEMANAGER->addFrameImage("bulletKing", L"tileImg/총탄킹.png", 20, 9);
	CAMERAMANAGER->setMapCamera(2000, 1000);

	load();

	return S_OK;
}

void bulletKingMap::release()
{
}

void bulletKingMap::update()
{
}

void bulletKingMap::render()
{
	//지형 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("bulletKing")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].terrainX, _tile[i].terrainY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}
	}

	//오브젝트 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tile[i].object == OBJ_NONE || _tile[i].object == OBJ_Be)continue;

		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("bulletKing")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].objX, _tile[i].objY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}
	}
}

void bulletKingMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("bulletKing.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	
	memset(_attribute, 0, sizeof(int) * TILEX * TILEY);
	memset(_pos, 0, sizeof(int) * 2);


	CloseHandle(file);

	////타일을 불러온 다음 타일이 어떤 지형인지 오브젝트인지 분별
	////해당 타일에 속성 부여

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		if (_tile[i].object == BLOCK ||
			_tile[i].object == BLOCK_LHALF ||
			_tile[i].object == BLOCK_RHALF ||
			_tile[i].object == BLOCK_LTRIPLE ||
			_tile[i].object == BLOCK_RTRIPLE)
		{
			_attribute[i] = NONEMOVE;
		}
	}
}
