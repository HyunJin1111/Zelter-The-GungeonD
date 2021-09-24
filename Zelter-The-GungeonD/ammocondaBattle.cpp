#include "stdafx.h"
#include "ammocondaBattle.h"
#include "player.h"

ammocondaBattle::ammocondaBattle()
{
}

ammocondaBattle::~ammocondaBattle()
{
}

HRESULT ammocondaBattle::init()
{
	SOUNDMANAGER->addSound("ammocondaBGM", "sound/아모콘다 보스 배경음악.wav", true, true);

	_ammocondaMap = new ammocondaMap;
	_ammocondaMap->init();
	CAMERAMANAGER->setX(0);
	CAMERAMANAGER->setY(0);

	_ammoconda = new ammoconda;
	_ammoconda->init();

	_player = new player;
	_player->init();
	
	_player->linkAmmoconda(_ammoconda);
	_player->linkAmmocondaMap(_ammocondaMap);
	_ammoconda->linkPlayer(_player);

	_player->setKeyType(false);

	SOUNDMANAGER->play("ammocondaBGM");

	return S_OK;
}

void ammocondaBattle::release()
{
}

void ammocondaBattle::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_ammocondaMap->update();

	_ammoconda->update();
	_player->update();

	for (int i = 0; i < WINSIZEY / 32; i++)
	{
		for (int j = 0; j < WINSIZEX / 32; j++)
		{
			if (_ammocondaMap->getTileAttribute()[i * TILEX + j] == NONEMOVE &&
				IsCollision(_ammocondaMap->getTile()[i * TILEX + j].rc, _player->getPlayer().rc))_player->setPlayerIscollde(true);
		}
	}

}

void ammocondaBattle::render()
{
	_ammocondaMap->render();

	_ammoconda->render();
	_player->render();
}
