#include "stdafx.h"
#include "niflheimBattle.h"

HRESULT niflheimBattle::init()
{
	SOUNDMANAGER->addSound("niflheimBGM", "sound/니플헤임 보스 배경음악.wav", true, true);

	IMAGEMANAGER->addImage("niflheimBackGround", L"niflheim/niflheimBackGround.png");
	_backGround = IMAGEMANAGER->findImage("niflheimBackGround");

	_niflheimMap = new niflheimMap;
	_niflheimMap->init();
	CAMERAMANAGER->setX(0);
	CAMERAMANAGER->setY(0);

	_player = new player;
	_player->init();
	_player->setKeyType(true);

	_niflheim = new niflheim;
	_niflheim->init();

	_player->linkNiflheimMap(_niflheimMap);
	_player->linkNiflheim(_niflheim);
	_niflheim->linkPlayer(_player);

	SOUNDMANAGER->play("niflheimBGM");

	return S_OK;
}

void niflheimBattle::release()
{

}

void niflheimBattle::update()
{
	_player->setKeyType(true);

	_niflheimMap->update();
	_niflheim->update();
	_player->update();

	for (int i = 0; i < WINSIZEY / 32; i++)
	{
		for (int j = 0; j < WINSIZEX / 32; j++)
		{
			if (_player->getPlayer().isEnd)
			{
				if (_niflheimMap->getTileAttribute()[i * TILEX + j] == NONEMOVE &&
					IsCollision(_niflheimMap->getTile()[i * TILEX + j].rc, _player->getPlayer().rc))_player->setPlayerIscollde(true);
			}
		}
	}

}

void niflheimBattle::render()
{
	_backGround->render(0, 0);

	_niflheimMap->render();
	_niflheim->render();
	_player->render();
}
