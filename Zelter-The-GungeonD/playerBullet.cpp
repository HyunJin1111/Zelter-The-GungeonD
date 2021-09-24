#include "stdafx.h"
#include "playerBullet.h"
#include "player.h"


HRESULT playerBullet::init()
{
	_player = new player;

	return S_OK;
}

void playerBullet::releaseBullet(int index)
{
	_vBulletN.erase(_vBulletN.begin() + index);
}

void playerBullet::releaseS(int index)
{
	_vBulletS.erase(_vBulletS.begin() + index);
}

void playerBullet::releaseH(int index)
{
	_vBulletH.erase(_vBulletH.begin() + index);
}

void playerBullet::releaseG(int index)
{
	_vBulletG.erase(_vBulletG.begin() + index);
}

void playerBullet::releaseGrenadeBullet(int index)
{
	_vGrenadeBullet.erase(_vGrenadeBullet.begin() + index);
}

void playerBullet::releaseF(int index)
{
	_vBulletF.erase(_vBulletF.begin() + index);
}

void playerBullet::update()
{
	_cameraX = CAMERAMANAGER->getX();
	_cameraY = CAMERAMANAGER->getY();

	for (_viGrenadeBullet = _vGrenadeBullet.begin(); _viGrenadeBullet != _vGrenadeBullet.end(); ++_viGrenadeBullet)
	{
		_viGrenadeBullet->gravity += 0.03;
		break;
	}

	for (int i = 0; i < _vBulletG.size(); i++)
	{
		_vBulletG[i].count -= 1;
		if (_vBulletG[i].count <= 0)
		{
			produceEffect(_vBulletG[i].x,_vBulletG[i].y);
			releaseG(i);
		}

		break;
	}

	if (_vBoom.size() != 0) playEffect();

}

void playerBullet::render()
{

	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i].img->frameRender2(_vBoom[i].x, _vBoom[i].y, _vBoom[i].effectFrameX, 0);
	}

	for (_viBulletN = _vBulletN.begin(); _viBulletN != _vBulletN.end(); ++_viBulletN)
	{
		_viBulletN->img->render(_viBulletN->x- _cameraX, _viBulletN->y- _cameraY, 1.f, 1.f, _viBulletN->angle * 180 / PI, _viBulletN->img->getWidth() / 2, _viBulletN->img->getHeight() / 2);
		if(KEYMANAGER->isToggleKey(VK_TAB))
		D2DRENDER->DrawRectangle(_viBulletN->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	for (_viBulletS = _vBulletS.begin(); _viBulletS != _vBulletS.end(); ++_viBulletS)
	{
		_viBulletS->img->render(_viBulletS->x- _cameraX, _viBulletS->y- _cameraY,1.f,1.f,_viBulletS->angle *180/PI,_viBulletS->img->getWidth()/2, _viBulletS->img->getHeight()/2);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletS->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	for (_viBulletH = _vBulletH.begin(); _viBulletH != _vBulletH.end(); ++_viBulletH)
	{
		_viBulletH->img->render(_viBulletH->x- _cameraX, _viBulletH->y- _cameraY,1.f, 1.f, _viBulletH->angle * 180 / PI, _viBulletH->img->getWidth() / 2, _viBulletH->img->getHeight() / 2);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletH->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
	{
		_viBulletG->img->render(_viBulletG->x, _viBulletG->y);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletG->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	for (_viGrenadeBullet = _vGrenadeBullet.begin(); _viGrenadeBullet != _vGrenadeBullet.end(); ++_viGrenadeBullet)
	{
		_viGrenadeBullet->img->render(_viGrenadeBullet->x, _viGrenadeBullet->y, 1.f, 1.f, _viGrenadeBullet->angle * 180 / PI, _viGrenadeBullet->img->getWidth() / 2, _viGrenadeBullet->img->getHeight() / 2);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viGrenadeBullet->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	for (_viBulletF = _vBulletF.begin(); _viBulletF != _vBulletF.end(); ++_viBulletF)
	{
		_viBulletF->img->render(_viBulletF->x- _cameraX, _viBulletF->y- _cameraY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletF->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}
}

void playerBullet::fire(float x, float y, float angle, float speed, int type, float power)
{
	switch (type)
	{
		tagPlayerBullet bullet;
		ZeroMemory(&bullet, sizeof(tagPlayerBullet));
	case NORMAL:
		bullet.img = IMAGEMANAGER->findImage("bullet2");
		bullet.range = WINSIZEX;
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBulletN.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle)* 30 + x;
		bullet.y = bullet.fireY = -sinf(angle)* 30 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletN.push_back(bullet);
		break;

	case SHOTGUN:
		for (int i = 0; i < 4; i++)
		{
			bullet.img = IMAGEMANAGER->findImage("bullet1");
			bullet.range = WINSIZEX;
			bullet.bulletMax = 50;
			if (bullet.bulletMax < _vBulletS.size()) return;
			bullet.speed = speed;
			bullet.radius = bullet.img->getWidth() / 2;
			bullet.x = bullet.fireX = cosf(angle) * 50 + x;
			bullet.y = bullet.fireY = -sinf(angle) * 50 + y;
			bullet.angle = angle + (i * 0.1f);
			bullet.damage = 10;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
			_vBulletS.push_back(bullet);
		}
		break;

	case HOMING:
		bullet.img = IMAGEMANAGER->findImage("bullet2");
		bullet.range = WINSIZEX;
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBulletH.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 70 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletH.push_back(bullet);
		break;

	case GRENADE:
		bullet.img = IMAGEMANAGER->findImage("GUN4");
		bullet.range = GetDistance(_ptMouse.x, _ptMouse.y, x, y);
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBulletG.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 20 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 100 + y;
		bullet.angle = angle;
		bullet.damage = 1;
		bullet.power = power;
		bullet.gravity = 0;
		bullet.count = 50;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletG.push_back(bullet);
		break;

	case FLAMETHROWER:
		bullet.img = IMAGEMANAGER->findImage("flame");
		bullet.range = 300;
		bullet.bulletMax = 100;
		if (bullet.bulletMax < _vBulletF.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 80 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletF.push_back(bullet);
		break;
	}
}


void playerBullet::move(int type, float x, float y)
{
	if (_vBulletH.size() != 0)
	{
		for (_viBulletH = _vBulletH.begin(); _viBulletH != _vBulletH.end();)
		{
			if (GetDistance(_viBulletH->x, _viBulletH->y, x, y) <= 100)
			{
				_disX = x - _viBulletH->x;
				_disY = y - _viBulletH->y;

				_viBulletH->angle = -atan2f(_disY, _disX);
				_viBulletH->x += cosf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->y += -sinf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->rc = RectMakeCenter(_viBulletH->x, _viBulletH->y,
					_viBulletH->img->getWidth(),
					_viBulletH->img->getHeight());
			}
			else
			{
				_viBulletH->x += cosf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->y += -sinf(_viBulletH->angle )* _viBulletH->speed;
				_viBulletH->rc = RectMakeCenter(_viBulletH->x, _viBulletH->y,
					_viBulletH->img->getWidth(),
					_viBulletH->img->getHeight());
			}

			if (_viBulletH->range < GetDistance(_viBulletH->fireX, _viBulletH->fireY, _viBulletH->x, _viBulletH->y))
			{
				_viBulletH = _vBulletH.erase(_viBulletH);
			}
			else ++_viBulletH;
		}
	}

	if (_vBulletG.size() != 0)
	{
		for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
		{
			{ _viBulletG->x += cosf(_viBulletG->angle) * _viBulletG->speed;
			_viBulletG->y -= sinf(_viBulletG->angle) * (_viBulletG->speed );
		/*	_viBulletG->power -= _viBulletG->gravity;
			_viBulletG->gravity += 0.5;*/
			_viBulletG->rc = RectMakeCenter(_viBulletG->x, _viBulletG->y,
				_viBulletG->img->getWidth(),
				_viBulletG->img->getHeight());
			}

			if (_viBulletG->range < GetDistance(_viBulletG->fireX, _viBulletG->fireY, _viBulletG->x, _viBulletG->y))
			{
				_viBulletG->gravity = 0;
				_viBulletG->speed = 0;
				_viBulletG->power = 0;
			}
		}
	}

	if (_vBulletF.size() != 0)
	{
		for (_viBulletF = _vBulletF.begin(); _viBulletF != _vBulletF.end();)
		{
			_viBulletF->x += cosf(_viBulletF->angle) * (_viBulletF->speed/2);
			_viBulletF->y += -sinf(_viBulletF->angle) * (_viBulletF->speed/2);
			_viBulletF->rc = RectMakeCenter(_viBulletF->x, _viBulletF->y,
				_viBulletF->img->getWidth(),
				_viBulletF->img->getHeight());

			if (_viBulletF->range < GetDistance(_viBulletF->fireX, _viBulletF->fireY, _viBulletF->x, _viBulletF->y))
			{
				_viBulletF = _vBulletF.erase(_viBulletF);
			}
			else ++_viBulletF;
		}

	}
	if (_vBulletN.size() != 0)
	{
		for (_viBulletN = _vBulletN.begin(); _viBulletN != _vBulletN.end();)
		{
			_viBulletN->x += cosf(_viBulletN->angle) * _viBulletN->speed;
			_viBulletN->y += -sinf(_viBulletN->angle) * _viBulletN->speed;
			_viBulletN->rc = RectMakeCenter(_viBulletN->x, _viBulletN->y,
				_viBulletN->img->getWidth(),
				_viBulletN->img->getHeight());

			if (_viBulletN->range < GetDistance(_viBulletN->fireX, _viBulletN->fireY, _viBulletN->x, _viBulletN->y))
			{
				_viBulletN = _vBulletN.erase(_viBulletN);
			}
			else ++_viBulletN;
		}

	}
	if (_vBulletS.size() != 0)
	{
	for (_viBulletS = _vBulletS.begin(); _viBulletS != _vBulletS.end();)
	{
		_viBulletS->x += cosf(_viBulletS->angle) * _viBulletS->speed;
		_viBulletS->y += -sinf(_viBulletS->angle) * _viBulletS->speed;
		_viBulletS->rc = RectMakeCenter(_viBulletS->x, _viBulletS->y,
			_viBulletS->img->getWidth(),
			_viBulletS->img->getHeight());

		if (_viBulletS->range < GetDistance(_viBulletS->fireX, _viBulletS->fireY, _viBulletS->x, _viBulletS->y))
		{
			_viBulletS = _vBulletS.erase(_viBulletS);
		}
		else ++_viBulletS;
	}

	}
}

void playerBullet::move(int type)
{
	if (_vBulletH.size() != 0)
	{
		for (_viBulletH = _vBulletH.begin(); _viBulletH != _vBulletH.end();)
		{
			
				_viBulletH->x += cosf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->y += -sinf(_viBulletH->angle)* _viBulletH->speed;
				_viBulletH->rc = RectMakeCenter(_viBulletH->x, _viBulletH->y,
					_viBulletH->img->getWidth(),
					_viBulletH->img->getHeight());
		
			if (_viBulletH->range < GetDistance(_viBulletH->fireX, _viBulletH->fireY, _viBulletH->x, _viBulletH->y))
			{
				_viBulletH = _vBulletH.erase(_viBulletH);
			}
			else ++_viBulletH;
		}
	}

	if (_vBulletG.size() != 0)
	{
		for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
		{
			{ _viBulletG->x += cosf(_viBulletG->angle) * _viBulletG->speed;
			_viBulletG->y -= sinf(_viBulletG->angle) * (_viBulletG->speed);
			/*	_viBulletG->power -= _viBulletG->gravity;
				_viBulletG->gravity += 0.5;*/
			_viBulletG->rc = RectMakeCenter(_viBulletG->x, _viBulletG->y,
				_viBulletG->img->getWidth(),
				_viBulletG->img->getHeight());
			}

			if (_viBulletG->range < GetDistance(_viBulletG->fireX, _viBulletG->fireY, _viBulletG->x, _viBulletG->y))
			{
				_viBulletG->gravity = 0;
				_viBulletG->speed = 0;
				_viBulletG->power = 0;
			}
		}
	}

	if (_vBulletF.size() != 0)
	{
		for (_viBulletF = _vBulletF.begin(); _viBulletF != _vBulletF.end();)
		{
			_viBulletF->x += cosf(_viBulletF->angle) * (_viBulletF->speed / 2);
			_viBulletF->y += -sinf(_viBulletF->angle) * (_viBulletF->speed / 2);
			_viBulletF->rc = RectMakeCenter(_viBulletF->x, _viBulletF->y,
				_viBulletF->img->getWidth(),
				_viBulletF->img->getHeight());

			if (_viBulletF->range < GetDistance(_viBulletF->fireX, _viBulletF->fireY, _viBulletF->x, _viBulletF->y))
			{
				_viBulletF = _vBulletF.erase(_viBulletF);
			}
			else ++_viBulletF;
		}

	}
	if (_vBulletN.size() != 0)
	{
		for (_viBulletN = _vBulletN.begin(); _viBulletN != _vBulletN.end();)
		{
			_viBulletN->x += cosf(_viBulletN->angle) * _viBulletN->speed;
			_viBulletN->y += -sinf(_viBulletN->angle) * _viBulletN->speed;
			_viBulletN->rc = RectMakeCenter(_viBulletN->x, _viBulletN->y,
				_viBulletN->img->getWidth(),
				_viBulletN->img->getHeight());

			if (_viBulletN->range < GetDistance(_viBulletN->fireX, _viBulletN->fireY, _viBulletN->x, _viBulletN->y))
			{
				_viBulletN = _vBulletN.erase(_viBulletN);
			}
			else ++_viBulletN;
		}

	}
	if (_vBulletS.size() != 0)
	{
		for (_viBulletS = _vBulletS.begin(); _viBulletS != _vBulletS.end();)
		{
			_viBulletS->x += cosf(_viBulletS->angle) * _viBulletS->speed;
			_viBulletS->y += -sinf(_viBulletS->angle) * _viBulletS->speed;
			_viBulletS->rc = RectMakeCenter(_viBulletS->x, _viBulletS->y,
				_viBulletS->img->getWidth(),
				_viBulletS->img->getHeight());

			if (_viBulletS->range < GetDistance(_viBulletS->fireX, _viBulletS->fireY, _viBulletS->x, _viBulletS->y))
			{
				_viBulletS = _vBulletS.erase(_viBulletS);
			}
			else ++_viBulletS;
		}

	}
}


void playerBullet::fireGrenadeBullet(float x, float y, float angle, float speed)
{
	for (int i = 0; i < 16; i++)
	{
		tagPlayerBullet bullet;
		ZeroMemory(&bullet, sizeof(tagPlayerBullet));
		bullet.img = IMAGEMANAGER->findImage("bullet1");
		bullet.range = WINSIZEX;
		bullet.bulletMax = 400;
		if (bullet.bulletMax < _vGrenadeBullet.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 10 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 50 + y;
		bullet.angle = angle + (i * 0.4f);
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vGrenadeBullet.push_back(bullet);
	}
}

void playerBullet::moveGrenadeBullet()
{
	if (_vGrenadeBullet.size() != 0)
	{
		for (_viGrenadeBullet = _vGrenadeBullet.begin(); _viGrenadeBullet != _vGrenadeBullet.end();)
		{
			_viGrenadeBullet->x += cosf(_viGrenadeBullet->angle) * _viGrenadeBullet->speed;
			_viGrenadeBullet->y += -sinf(_viGrenadeBullet->angle) * _viGrenadeBullet->speed;
			_viGrenadeBullet->rc = RectMakeCenter(_viGrenadeBullet->x, _viGrenadeBullet->y,
				_viGrenadeBullet->img->getWidth(),
				_viGrenadeBullet->img->getHeight());

			if (_viGrenadeBullet->range < GetDistance(_viGrenadeBullet->fireX, _viGrenadeBullet->fireY, _viGrenadeBullet->x, _viGrenadeBullet->y))
			{
				_viGrenadeBullet = _vGrenadeBullet.erase(_viGrenadeBullet);
			}
			else ++_viGrenadeBullet;
		}
	}

	for (int i = 0; i < _vBulletG.size(); i++)
	{
		if (_vBulletG[i].count <= 1)
			fireGrenadeBullet(_vBulletG[i].x, _vBulletG[i].y, 0, 10);
	}
}

void playerBullet::produceEffect(float x, float y)
{
			tagBoom2 boom;
			boom.img = IMAGEMANAGER->findImage("boom2");
			boom.effectFrameX = 0;
			boom.x = x;
			boom.y = y;
			boom.playeEffectEnd = false;
			_vBoom.push_back(boom);
}

void playerBullet::playEffect()
{
	_effectFrameCount++;

	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (_effectFrameCount % 3 == 0)
		{
			//이펙트 프레임 재생
			_vBoom[i].effectFrameX++;
			if (_vBoom[i].effectFrameX >= _vBoom[i].img->getMaxFrameX())
			{
				_vBoom[i].playeEffectEnd = true;
			}

			//재생이 끝나면 해당 이펙트 지워줌
			if (_vBoom[i].playeEffectEnd)
			{
				_vBoom.erase(_vBoom.begin() + i);
			}

			_effectFrameCount = 0;
		}
	}
}
