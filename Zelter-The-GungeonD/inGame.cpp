#include "stdafx.h"
#include "inGame.h"


HRESULT inGame::init()
{
	SOUNDMANAGER->addSound("openWorldBGM", "sound/오픈월드 배경음악.wav", true, true);
	SOUNDMANAGER->play("openWorldBGM");
	_inGameMap = new inGameMap;
	_inGameMap->init();

	_player = new player;
	_player->init();

	_player->setKeyType(false);
	_player->linkOpenWorldMap(_inGameMap);
	_player->linkNiflheimMap(_niflheimMap);
/*
	_player->setPlayerX(10500);
	_player->setPlayerY(100);*/

	_dinosaur = new dinosaur;
	_dinosaur->init();
	_dinosaur->linkOpenWorldMap(_inGameMap);
	_dinosaur->setEnemy();

	_fishMan = new fishMan;
	_fishMan->init();
	_fishMan->linkOpenWorldMap(_inGameMap);
	_fishMan->setEnemy();

	return S_OK;
}

void inGame::release()
{
	_inGameMap->release();
	_player->release();
}

void inGame::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse, _player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_inGameMap->update();
	_player->update();

	collisionDoor();
	collisionEnemy();

	
	_dinosaur->dinoState();
	_dinosaur->dinoMove(_player->getPlayer().x, _player->getPlayer().y);


	_fishMan->fishState();
	_fishMan->fishMove(_player->getPlayer().x, _player->getPlayer().y);


	
	
}

void inGame::render()
{

	_inGameMap->render();
	_player->render();
	_dinosaur->render();
	_fishMan->render();

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_inGameMap->getTile()[i].object == OBJ_NONE)continue;

		if (0 <= _inGameMap->getTile()[i].rc.right - CAMERAMANAGER->getX() &&
			_inGameMap->getTile()[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _inGameMap->getTile()[i].rc.bottom - CAMERAMANAGER->getY() &&
			_inGameMap->getTile()[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{
			/*if (_player->getPlayer().rc.bottom > _inGameMap->getTile()[i].checkRect.bottom)
			{*/
			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_inGameMap->getTile()[i].rc.left - CAMERAMANAGER->getX(), _inGameMap->getTile()[i].rc.top - CAMERAMANAGER->getY(),
				_inGameMap->getTile()[i].objX, _inGameMap->getTile()[i].objY,
				_inGameMap->getTile()[i].sizeX, _inGameMap->getTile()[i].sizeY
			);
			//}
		}
	}

}

void inGame::collisionDoor()
{
	for (int i = 0; i < 4; i++)
	{
		if (IsCollision(_inGameMap->getBossDoor(i).rc, _player->getPlayer().rc))
		{
			SOUNDMANAGER->stop("openWorldBGM");
			switch (i)
			{
			case 0:
				SCENEMANAGER->changeScene("eggNyang");
				break;
			case 1:
				SCENEMANAGER->changeScene("niflheim");
				break;
			case 2:
				SCENEMANAGER->changeScene("bulletKing");
				break;
			case 3:
				SCENEMANAGER->changeScene("ammoconda");
				break;
			}
		}
	}
}

void inGame::collisionEnemy()
{
	playerBullet* _playerBullet = _player->getPlayerBullet();
	RECT temp;
	//공룡, 플레이어 충돌
	for (int j = 0; j < _dinosaur->getVDinosaur().size(); ++j)
	{
		for (int i = 0; i < _playerBullet->getVBulletF().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletF()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				cout << _dinosaur->getVDinosaur()[j].currentHp << "공룡 현재체력" << endl;
				_playerBullet->releaseF(i);
			}
		}
		for (int i = 0; i < _playerBullet->getvBulletG().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getvBulletG()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				_playerBullet->releaseG(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletH().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletH()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				_playerBullet->releaseH(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletN().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletN()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				_playerBullet->releaseBullet(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletS().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletS()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				_playerBullet->releaseS(i);
			}
		}
		for (int i = 0; i < _playerBullet->getvGrenadeBullet().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getvGrenadeBullet()[i].rc, &_dinosaur->getVDinosaur()[j].rc))
			{
				_dinosaur->getVDinosaur()[j].currentHp -= 20;
				_playerBullet->releaseGrenadeBullet(i);
			}
		}
	}
	//피쉬맨, 플레이어 충돌
	for (int j = 0; j < _fishMan->getVfishMan().size(); ++j)
	{
		for (int i = 0; i < _playerBullet->getVBulletF().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletF()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseF(i);
			}
		}
		for (int i = 0; i < _playerBullet->getvBulletG().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getvBulletG()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseG(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletH().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletH()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseH(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletN().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletN()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseBullet(i);
			}
		}
		for (int i = 0; i < _playerBullet->getVBulletS().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getVBulletS()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseS(i);
			}
		}
		for (int i = 0; i < _playerBullet->getvGrenadeBullet().size(); ++i)
		{
			if (IntersectRect(&temp, &_playerBullet->getvGrenadeBullet()[i].rc, &_fishMan->getVfishMan()[j].rc))
			{
				_fishMan->getVfishMan()[j].currentHp -= 20;
				_playerBullet->releaseGrenadeBullet(i);
			}
		}
	}


}


