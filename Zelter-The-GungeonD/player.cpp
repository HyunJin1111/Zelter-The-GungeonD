#include "stdafx.h"
#include "player.h"
#include "playerStateIdle.h"
#include "playerBullet.h"
#include "ammoconda.h"
#include "eggNyang.h"
#include "bulletKing.h"
#include "niflheim.h"
#include "dinosaur.h"
#include "fishMan.h"


HRESULT player::init()
{
	addIMAGES(); //이미지추가

	//ShowCursor(false);

	_player.img = IMAGEMANAGER->findImage("gunner_idle");
	_playerGun.img = IMAGEMANAGER->findImage("GUN1");
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.y, 100, 10);
	_playerGun.rc = RectMakeCenter(_player.x + 30, _player.y, _playerGun.img->getWidth(), _playerGun.img->getHeight());
	_player.currentFrameX = _player.currentFrameY = 0;
	_player.isDeath = false;
	_player.isDunGreed = false;
	_player.isHit = false;
	_player.isEnd = true;
	_player.isJump = false;
	_player.isCollide = false;
	_player.maxHP = _player.currentHP = 100;
	_playerGun.x = _player.x;
	_playerGun.y = _player.y;
	_player.speed = 5.0f;
	_gunType = 0;
	_playerBullet = new playerBullet;
	_playerBullet->init();

	_mouse = IMAGEMANAGER->findImage("mouse");

	state = new playerStateIdle();

	_quickSlot = new quickSlot;
	_quickSlot->init();

	_progressBar = new progressBar();
	_progressBar->init(170, 25, 100, 30);
	_progressBar->setGauge(_player.currentHP, _player.maxHP);

	_inGame = new inGameMap;


	_dinosaur = new dinosaur;
	_dinosaur->init();

	_fishMan = new fishMan;
	_fishMan->init();
	

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	//cout << _player.direction << "방향" << endl;
	tileDetect(SCENEMANAGER->getSceneName());
	_cameraX = CAMERAMANAGER->getX();
	_cameraY = CAMERAMANAGER->getY();
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	//=================================================================

	RECT temp;
	_count++;

	inputHandle();
	state->update(this);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.rc.bottom, 50, 10);
	
	

	//플레이어 마우스 방향으로 바라보기
	_playerGun.angle = GetAngle(_playerGun.x, _playerGun.y, _mapMouse.x, _mapMouse.y) * (180 / PI);

	
	if (!_player.isDeath)
	{
		if (_playerGun.angle < 337.5 && 22.5 < _playerGun.angle) _player.direction = 0;
		if (_playerGun.angle < 112.5 && 67.5 < _playerGun.angle) _player.direction = 2;
		if (_playerGun.angle < 202.5 && 157.5 < _playerGun.angle) _player.direction = 1;
		if (_playerGun.angle < 292.5 && 247.5 < _playerGun.angle) _player.direction = 3;
		if (_playerGun.angle < 67.5 && 22.5< _playerGun.angle) _player.direction = 5;
		if (_playerGun.angle < 157.5 && 112.5 < _playerGun.angle) _player.direction = 4;
		if (_playerGun.angle < 247.5 && 202.5 < _playerGun.angle) _player.direction = 7;
		if (_playerGun.angle < 337.5 && 292.5 < _playerGun.angle) _player.direction = 6;
	}

	
	_playerGun.x = _player.x;
	_playerGun.y = _player.y;

	_playerGun.rc = RectMakeCenter(_player.x + 27, _player.y + 15, _playerGun.img->getWidth(), _playerGun.img->getHeight());
	
	switch (_gunType)
	{

	case 0:
		_playerGun.img = IMAGEMANAGER->findImage("GUN1");
		break;
	case 1:
		_playerGun.img = IMAGEMANAGER->findImage("GUN2");
		break;
	case 2:
		_playerGun.img = IMAGEMANAGER->findImage("GUN3");
		break;
	case 3:
		_playerGun.img = IMAGEMANAGER->findImage("GUN4");
		break;
	case 4:
		_playerGun.img = IMAGEMANAGER->findImage("GUN5");
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F9))_player.currentHP -= 10;

	if (SCENEMANAGER->isCurrentScene("openWorld"))
	{
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
		_playerGun.rc = RectMakeCenter(_player.x+18, _player.y+5, _playerGun.img->getWidth()*_openWorldSize, _playerGun.img->getHeight()*_openWorldSize);
	
		_playerBullet->move(_gunType);
	}

	//불렛 킹 총알 충돌
	if (SCENEMANAGER->isCurrentScene("bulletKing"))
	{
	
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_bulletKingSize, _player.img->getFrameHeight()*_bulletKingSize);
		_player.shadow = RectMakeCenter(_player.x, _player.rc.bottom, 50*_bulletKingSize, 10*_bulletKingSize);
		_playerGun.rc = RectMakeCenter(_player.x + 20, _player.y+10, _playerGun.img->getWidth()*_bulletKingSize, _playerGun.img->getHeight()*_bulletKingSize);
		_playerBullet->move(_gunType,_bulletKing->getBulletKing().x,_bulletKing->getBulletKing().y);
		if (!_player.isHit && _player.isEnd)
		{
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet1().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet1()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet2().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet2()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet3().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet3()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
		}
	}
	
	//아모콘다 총알 충돌
	if (SCENEMANAGER->isCurrentScene("ammoconda"))
	{
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
		_player.shadow = RectMakeCenter(_player.x, _player.rc.bottom, 50 * _ammoCondaSize, 10 * _ammoCondaSize);
		_playerGun.rc = RectMakeCenter(_player.x + 30, _player.y, _playerGun.img->getWidth()*_ammoCondaSize, _playerGun.img->getHeight()*_ammoCondaSize);
		_playerBullet->move(_gunType,_ammoconda->getAmmoconda(0).x,_ammoconda->getAmmoconda(0).y);
		if (!_player.isHit && _player.isEnd)
		{
			for (int i = 0; i < _ammoconda->getBAmmocondaBullet()->getVammoCondaBullet1().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVammoCondaBullet1()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _ammoconda->getBAmmocondaBullet()->getVammoCondaBullet2().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVammoCondaBullet2()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _ammoconda->getBAmmocondaBullet()->getVpotBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVpotBullet()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
		}
	}

	//니플헤임 총알 충돌
	if (SCENEMANAGER->isCurrentScene("niflheim"))
	{
		_playerBullet->move(_gunType,_niflheim->getNiflheim().x,_niflheim->getNiflheim().y);
		if (!_player.isHit && _player.isEnd)
		{
			for (int i = 0; i < _niflheim->getNiflheim().icePillar->getVbullet().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().icePillar->getVbullet()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _niflheim->getNiflheim().iceSpear->getVIceSpear().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().iceSpear->getVIceSpear()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _niflheim->getNiflheim().iceicle->getVIcicle().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().iceicle->getVIcicle()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
		}
	}


	//에그냥 총알 충돌
	if (SCENEMANAGER->isCurrentScene("eggNyang"))
	{
		_playerBullet->move(_gunType,_eggNyang->getEggNyang().x,_eggNyang->getEggNyang().y);
		if (!_player.isHit && _player.isEnd)
		{
			for (int i = 0; i < _eggNyang->getEggNyang().bullet->getEggNyangVBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().bullet->getEggNyangVBullet()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _eggNyang->getEggNyang().lazer->getEggNyangVLazer().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().lazer->getEggNyangVLazer()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _eggNyang->getEggNyang().sword->getEggNyangVSword().size(); i++)
			{
				if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().sword->getEggNyangVSword()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}

			}
		}
	}
	
	

	_quickSlot->update();

	if (_quickSlot->getQuickslotisOn(0))
	{
		_gunType = NORMAL;
	}
	if (_quickSlot->getQuickslotisOn(1))
	{
		_gunType = SHOTGUN;
	}
	if (_quickSlot->getQuickslotisOn(2))
	{
		_gunType = HOMING;
	}
	if (_quickSlot->getQuickslotisOn(3))
	{
		_gunType = GRENADE;
	}
	if (_quickSlot->getQuickslotisOn(4))
	{
		_gunType = FLAMETHROWER;
	}


	_progressBar->setGauge(_player.currentHP, _player.maxHP);
	_progressBar->update();
	_playerBullet->update();
	_playerBullet->moveGrenadeBullet();
}

void player::render()
{
	_progressBar->render();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDER->DrawRectangle(_player.rc, D2DRenderer::DefaultBrush::White, 1.f);
		D2DRENDER->DrawRectangle(_player.shadow, D2DRenderer::DefaultBrush::White, 1.f);
		D2DRENDER->DrawRectangle(_playerGun.rc, D2DRenderer::DefaultBrush::White, 1.f, _playerGun.angle);
	}
	_playerBullet->render();

	if (SCENEMANAGER->isCurrentScene("bulletKing"))
	{
		if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX() , _playerGun.rc.top- CAMERAMANAGER->getY(), 0.7f, -0.7f, _playerGun.angle);
				if(!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX,_player.currentFrameY,_player.img->getFrameWidth()*_bulletKingSize,_player.img->getFrameHeight()*_bulletKingSize);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 0.7f, 0.7f, _playerGun.angle);
				if(!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_bulletKingSize, _player.img->getFrameHeight()*_bulletKingSize);
			}
		}
		else
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if(!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_bulletKingSize, _player.img->getFrameHeight()*_bulletKingSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 0.7f, -0.7f, _playerGun.angle);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if(!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_bulletKingSize, _player.img->getFrameHeight()*_bulletKingSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 0.7f, 0.7f, _playerGun.angle);
			}
		}
	}
	if (SCENEMANAGER->isCurrentScene("ammoconda"))
	{
		if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left , _playerGun.rc.top , 0.7f, -0.7f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left , _playerGun.rc.top, 0.7f, 0.7f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
			}
		}
		else
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left , _playerGun.rc.top , 0.7f, -0.7f, _playerGun.angle);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left, _playerGun.rc.top , 0.7f, 0.7f, _playerGun.angle);
			}
		}
	}
	if (SCENEMANAGER->isCurrentScene("niflheim"))
	{
		if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, -1.f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, 1.f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			}
		}
		else
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, -1.f, _playerGun.angle);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, 1.f, _playerGun.angle);
			}
		}
	}
	if (SCENEMANAGER->isCurrentScene("eggNyang"))
	{
		if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, -1.f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, 1.f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			}
		}
		else
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, -1.f, _playerGun.angle);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left, _player.rc.top, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth(), _player.img->getFrameHeight());
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - CAMERAMANAGER->getX(), _playerGun.rc.top - CAMERAMANAGER->getY(), 1.f, 1.f, _playerGun.angle);
			}
		}
	}
	if (SCENEMANAGER->isCurrentScene("openWorld"))
	{
		if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 0.7f, 0.7f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left - _cameraX, _player.rc.top - _cameraY, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 0.7f, 0.7f, _playerGun.angle);
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left- _cameraX, _player.rc.top- _cameraY, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
			}
		}
		else
		{
			if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left-_cameraX, _player.rc.top-_cameraY, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 0.7f, -0.7f, _playerGun.angle);
			}
			else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
			{
				if (!_player.isDeath)_player.img->cutRender(_player.rc.left- _cameraX, _player.rc.top-_cameraY, _player.currentFrameX, _player.currentFrameY, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
				if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 0.7f, 0.7f,  _playerGun.angle);
			}
		}
	}
	
	_quickSlot->render();
	_mouse->render(_ptMouse.x - 7, _ptMouse.y - 5);
	/*if (KEYMANAGER->isToggleKey(VK_NUMPAD7)) 
	{
		for (int i = 0; i < 2; i++)
		{
			D2DRENDER->DrawRectangle(_rcc[i], D2DDEFAULTBRUSH::Red);
		}
		
	}
	if (KEYMANAGER->isToggleKey(VK_NUMPAD8)) 
	{
		for (int i = 0; i < 3; i++)
		{
			D2DRENDER->DrawRectangle(_rcc2[i], D2DDEFAULTBRUSH::Red);
		}
		
	}*/
	

}

void player::addIMAGES()
{
	IMAGEMANAGER->addImage("GUN1", L"무기/기본.png");
	IMAGEMANAGER->addImage("GUN2", L"무기/산탄.png");
	IMAGEMANAGER->addImage("GUN3", L"무기/유도총.png");
	IMAGEMANAGER->addImage("GUN4", L"무기/수류탄.png");
	IMAGEMANAGER->addImage("GUN5", L"무기/화염방사.png");
	IMAGEMANAGER->addImage("mouse", L"무기/마우스.png");

	IMAGEMANAGER->addImage("GUN1R", L"무기/기본반대.png");
	IMAGEMANAGER->addImage("GUN2R", L"무기/산탄반대.png");
	IMAGEMANAGER->addImage("GUN3R", L"무기/유도총반대.png");
	IMAGEMANAGER->addImage("GUN4R", L"무기/수류탄반대.png");
	IMAGEMANAGER->addImage("GUN5R", L"무기/화염방사반대.png");


	IMAGEMANAGER->addFrameImage("gunner_idle", L"STATE/IDLE/gunner_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_idle", L"STATE/IDLE/gunner_back_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_idle", L"STATE/IDLE/gunner_left_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_idle", L"STATE/IDLE/gunner_right_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_idle", L"STATE/IDLE/gunner_left-up_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_idle", L"STATE/IDLE/gunner_right-up_idle2.png", 4, 1);

	IMAGEMANAGER->addFrameImage("gunner_run", L"STATE/RUN/gunner_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_run", L"STATE/RUN/gunner_back_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_run", L"STATE/RUN/gunner_left_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_run", L"STATE/RUN/gunner_right_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_run", L"STATE/RUN/gunner_up_left_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_run", L"STATE/RUN/gunner_up_right_run.png", 6, 1);

	IMAGEMANAGER->addFrameImage("gunner_roll", L"STATE/ROLL/gunner_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_roll", L"STATE/ROLL/gunner_back_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_roll", L"STATE/ROLL/gunner_left_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_roll", L"STATE/ROLL/gunner_right_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_roll", L"STATE/ROLL/gunner_left_up_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_roll", L"STATE/ROLL/gunner_right_up_roll.png", 9, 1);

	IMAGEMANAGER->addFrameImage("gunner_left_jump", L"STATE/JUMP/gunner_left_jump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_jump", L"STATE/JUMP/gunner_right_jump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_downjump", L"STATE/JUMP/gunner_left_downjump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_downjump", L"STATE/JUMP/gunner_right_downjump.png", 6, 1);


	IMAGEMANAGER->addFrameImage("gunner_death", L"STATE/DEATH/gunner_death.png", 15, 1);

	IMAGEMANAGER->addImage("bullet1", L"bullets/bullet1.png");
	IMAGEMANAGER->addImage("bullet2", L"bullets/bullet2.png");
	IMAGEMANAGER->addImage("flame", L"bullets/flame.png");
	IMAGEMANAGER->addImage("backpack", L"UI/backpack.png");
	IMAGEMANAGER->addImage("quickslotback", L"UI/quickslotback.png");
	IMAGEMANAGER->addImage("quickslotfront", L"UI/quickslotfront.png");
	IMAGEMANAGER->addImage("quickslotbase", L"UI/quickslotbase.png");

	IMAGEMANAGER->addImage("hpback", L"UI/hpback.png");
	IMAGEMANAGER->addImage("hpfront", L"UI/hpfront.png");

	IMAGEMANAGER->addFrameImage("boom2", L"effect/boom2.png",13,1);

}

void player::inputHandle() //스테이트 호출
{
	playerState* newState = state->inputHandle(this);

	if (newState != nullptr)
	{
		SAFE_DELETE(state);
		state = newState;
		state->enter(this);
	}
}

float player::hitDamage(float damage)
{
	return _player.currentHP -= damage;
}