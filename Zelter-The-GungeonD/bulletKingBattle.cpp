#include "stdafx.h"
#include "bulletKingBattle.h"

bulletKingBattle::bulletKingBattle()
{
}

bulletKingBattle::~bulletKingBattle()
{
}

HRESULT bulletKingBattle::init()
{
	SOUNDMANAGER->addSound("bulletKingBGM", "sound/ÃÑÅºÅ· º¸½º ¹è°æÀ½¾Ç.wav", true, true);

	_bulletKingMap = new bulletKingMap;
	_bulletKingMap->init();

	_bulletKing = new bulletKing;
	_bulletKing->init();
	_player = new player;
	_player->init();
	_player->setKeyType(false);

	
	_player->linkBulletKing(_bulletKing);
	_player->linkBulletKingMap(_bulletKingMap);
	_bulletKing->linkPlayer(_player);

	SOUNDMANAGER->play("bulletKingBGM");

	return S_OK;
}

void bulletKingBattle::release()
{
}

void bulletKingBattle::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_bulletKing->update();

	_player->update();

	_bulletKingMap->update();

	for (int i = 0; i < WINSIZEY / 32; i++)
	{
		for (int j = 0; j < WINSIZEX / 32; j++)
		{
			if (!_player->getPlayer().isEnd)
			{
				if (_bulletKingMap->getTileAttribute()[i * TILEX + j] == NONEMOVE &&
					IsCollision(_bulletKingMap->getTile()[i * TILEX + j].rc, _player->getPlayer().rc))_player->setPlayerIscollde(true);
			}
		}
	}
}

void bulletKingBattle::render()
{
	_bulletKingMap->render();
	_player->render();
	_bulletKing->render();

}
