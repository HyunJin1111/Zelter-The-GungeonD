#include "stdafx.h"
#include "niflheimBullet.h"

HRESULT niflheimIcePillar::init()
{
	return S_OK;
}

void niflheimIcePillar::release(int index)
{
	_vIcePillar[index].img = IMAGEMANAGER->findImage("nullImg");
}

void niflheimIcePillar::dieRelease(int index)
{
	_vIcePillar.erase(_vIcePillar.begin() + index);
}

void niflheimIcePillar::update(float niflheimX, float niflheimY)
{
	icePillarMove(niflheimX, niflheimY);

	for (int i = 0; i < _vIcePillar.size(); i++)
	{
		if (_vIcePillar[i].currentHP <= 0 && !_vIcePillar[i].hp0)
		{
			_vIcePillar[i].img = IMAGEMANAGER->findImage("icePillarDestroy");
			_vIcePillar[i].currentFrameX = 0;
			_vIcePillar[i].hp0 = true;
		}

		_vIcePillar[i].frameCount++;
		if (_vIcePillar[i].frameCount % 20 == 0)
		{
			_vIcePillar[i].currentFrameX++;
			if (_vIcePillar[i].currentFrameX >= _vIcePillar[i].img->getMaxFrameX() && !_vIcePillar[i].ready)
			{
				_vIcePillar[i].currentFrameX = 0;
				_vIcePillar[i].img = IMAGEMANAGER->findImage("icePillar");
			}
			else if (_vIcePillar[i].currentFrameX >= 2 && _vIcePillar[i].currentHP <= 0) _vIcePillar[i].destroy = true;
			else if (_vIcePillar[i].currentFrameX >= _vIcePillar[i].img->getMaxFrameX() && _vIcePillar[i].currentHP > 0) _vIcePillar[i].currentFrameX = 0;
		}

		if (_vIcePillar[i].destroy) release(i);

		_vIcePillar[i].rc = RectMake(_vIcePillar[i].x, _vIcePillar[i].y, _vIcePillar[i].img->getFrameWidth(), _vIcePillar[i].img->getFrameHeight());
		
		_vIcePillar[i].rotateCollsion.degreeAngle = _vIcePillar[i].angle;
		_vIcePillar[i].rotateCollsion.height = _vIcePillar[i].height;
		_vIcePillar[i].rotateCollsion.width = _vIcePillar[i].width;
		_vIcePillar[i].rotateCollsion.left = _vIcePillar[i].rc.left;
		_vIcePillar[i].rotateCollsion.top = _vIcePillar[i].rc.top;
	}
}

void niflheimIcePillar::render()
{
	if (_vIcePillar.size() > 0)
	{
		for (int i = 0; i < _vIcePillar.size(); i++)
		{
			_vIcePillar[i].img->frameRender2(_vIcePillar[i].rc.left, _vIcePillar[i].rc.top,
				_vIcePillar[i].currentFrameX, _vIcePillar[i].currentFrameY,
				1.0f, 1.0f,
				_vIcePillar[i].angle, _vIcePillar[i].radiusX, _vIcePillar[i].radiusY);

			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				D2DRENDER->DrawRectangle(_vIcePillar[i].rc, D2DDEFAULTBRUSH::Purple, 1.0f, _vIcePillar[i].angle);
			}
		}
	}
}

void niflheimIcePillar::seticePillar(float niflheimX, float niflheimY)
{
	for (int i = 0; i < MAXICEPILLAR; i++)
	{
		if (MAXICEPILLAR <= _vIcePillar.size()) return;

		tagBullet icePillar;
		ZeroMemory(&icePillar, sizeof(tagBullet));
		icePillar.img = IMAGEMANAGER->findImage("icePillarReady");
		icePillar.width = icePillar.img->getFrameWidth();
		icePillar.height = icePillar.img->getFrameHeight();
		icePillar.radiusX = icePillar.img->getFrameWidth() / 2;
		icePillar.radiusY = icePillar.img->getFrameHeight() / 2;
		icePillar.speed = 15;
		icePillar.frameCount = 0;
		icePillar.currentFrameX = 0;
		icePillar.currentFrameY = 0;
		icePillar.ready = false;
		icePillar.destroy = false;
		icePillar.hp0 = false;
		switch (i)
		{
		case 0:		//오른쪽
			icePillar.x = niflheimX + 50;
			icePillar.y = niflheimY;
			break;
		case 1:		//아래
			icePillar.x = niflheimX - 50;
			icePillar.y = niflheimY + (50 + icePillar.img->getFrameWidth() / 2);
			break;
		case 2:		//왼쪽
			icePillar.x = niflheimX - icePillar.img->getFrameWidth();
			icePillar.y = niflheimY;
			break;
		case 3:		//위
			icePillar.x = niflheimX - 20;
			icePillar.y = niflheimY - (50 + icePillar.img->getFrameWidth() / 2);
			break;
		}
		icePillar.angle = 0;
		icePillar.rc = RectMake(icePillar.x, icePillar.y,
			icePillar.img->getFrameWidth(), icePillar.img->getFrameHeight());
		icePillar.currentHP = 100;
		icePillar.maxHP = 100;

		_vIcePillar.push_back(icePillar);
	}
}

void niflheimIcePillar::icePillarMove(float niflheimX, float niflheimY)
{
	for (int i = 0; i < _vIcePillar.size(); i++)
	{
		if (_vIcePillar[i].currentHP > 0) _vIcePillar[i].angle += 5;
		switch (i)
		{
		case 0:		//오른쪽
			_vIcePillar[i].x = niflheimX + 100;
			_vIcePillar[i].y = niflheimY;
			break;
		case 1:		//아래
			_vIcePillar[i].x = niflheimX - 10;
			_vIcePillar[i].y = niflheimY + (50 + _vIcePillar[i].img->getFrameWidth() / 2);
			break;
		case 2:		//왼쪽
			_vIcePillar[i].x = niflheimX - (30 + _vIcePillar[i].img->getFrameWidth());
			_vIcePillar[i].y = niflheimY;
			break;
		case 3:		//위
			_vIcePillar[i].x = niflheimX - 10;
			_vIcePillar[i].y = niflheimY - (50 + _vIcePillar[i].img->getFrameWidth() / 2);
			break;
		}
	}
}


//기둥에서 발사되는 얼음총알===============================================
void niflheimIcePillar::fireBullet1(float x, float y, int icePillar)
{
	for (int i = 0; i < 20; i++)
	{
		if (_vBullet.size() >= MAXICEBULLET) return;


		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = IMAGEMANAGER->findImage("iceBullet");
		bullet.width = bullet.img->getFrameWidth();
		bullet.height = bullet.img->getFrameHeight();
		bullet.radiusX = bullet.img->getFrameWidth() / 2;
		bullet.radiusY = bullet.img->getFrameHeight() / 2;

		bullet.angle = GetAngle(_vIcePillar[icePillar].x + _vIcePillar[icePillar].radiusX,
			_vIcePillar[icePillar].y + _vIcePillar[icePillar].radiusY,
			x, y);
		bullet.x = _vIcePillar[icePillar].x + _vIcePillar[icePillar].radiusX - cosf(bullet.angle) * (i * 7);
		bullet.y = _vIcePillar[icePillar].y + _vIcePillar[icePillar].radiusY - -sinf(bullet.angle) * (i * 7);

		bullet.speed = 7;
		bullet.frameCount = 0;
		bullet.currentFrameX = 0;
		bullet.currentFrameY = 0;
		bullet.destroy = false;

		_vBullet.push_back(bullet);
	}
}

void niflheimIcePillar::fireBullet2(float x, float y, int icePillar)
{
	for (int i = 0; i < 20; i++)
	{
		if (_vBullet.size() >= MAXICEBULLET) return;

		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = IMAGEMANAGER->findImage("iceBullet");
		bullet.width = bullet.img->getFrameWidth();
		bullet.height = bullet.img->getFrameHeight();
		bullet.radiusX = bullet.img->getFrameWidth() / 2;
		bullet.radiusY = bullet.img->getFrameHeight() / 2;

		bullet.angle = GetAngle(_vIcePillar[icePillar].x + _vIcePillar[icePillar].radiusX,
			_vIcePillar[icePillar].y + _vIcePillar[icePillar].radiusY,
			x, y);

		bullet.x = _vIcePillar[icePillar].x + _vIcePillar[icePillar].radiusX - cosf(bullet.angle) * (i * 7);
		bullet.y = _vIcePillar[icePillar].y + _vIcePillar[icePillar].radiusY - -sinf(bullet.angle) * (i * 7);

		bullet.speed = 7;
		bullet.frameCount = 0;
		bullet.currentFrameX = 0;
		bullet.currentFrameY = 0;
		bullet.destroy = false;

		_vBullet.push_back(bullet);
	}
}

void niflheimIcePillar::bulletMove()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;

		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y, _vBullet[i].img->getWidth(), _vBullet[i].img->getHeight());

		_vBullet[i].rotateCollsion.left = _vBullet[i].rc.left;
		_vBullet[i].rotateCollsion.top = _vBullet[i].rc.top;
		_vBullet[i].rotateCollsion.width = _vBullet[i].width;
		_vBullet[i].rotateCollsion.height = _vBullet[i].height;
		_vBullet[i].rotateCollsion.degreeAngle = radianToDegree(_vBullet[i].angle);
		
		if (_vBullet[i].x <= 0 || _vBullet[i].x >= WINSIZEX
			|| _vBullet[i].y <= 0 || _vBullet[i].y >= WINSIZEY) _vBullet.erase(_vBullet.begin() + i);
	}
}

void niflheimIcePillar::releaseBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

void niflheimIcePillar::bulletRender()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].img->render(_vBullet[i].x, _vBullet[i].y, 2.0f, 2.0f,
			radianToDegree(_vBullet[i].angle), _vBullet[i].radiusX, _vBullet[i].radiusY);
	}
}
