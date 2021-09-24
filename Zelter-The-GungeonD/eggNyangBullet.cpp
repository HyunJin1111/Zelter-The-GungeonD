#include "stdafx.h"
#include "eggNyangBullet.h"

HRESULT eggNyangBullet::init()
{
	return S_OK;
}

void eggNyangBullet::release(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

void eggNyangBullet::update()
{
	bulletMove();

	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].frameCount++;
		if (_vBullet[i].frameCount % 7 == 0)
		{
			_vBullet[i].currentFrameX++;
			if (_vBullet[i].currentFrameX >= _vBullet[i].image->getMaxFrameX()) _vBullet[i].currentFrameX = 0;
			
			_vBullet[i].frameCount = 0;
		}
		
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y, _vBullet[i].width, _vBullet[i].height);

		if (_vBullet[i].x <= 0 || _vBullet[i].x >= WINSIZEX ||
			_vBullet[i].y <= 0 || _vBullet[i].y >= WINSIZEY)	//화면밖에 도달했을 때 해당 인덱스 삭제
		{
			release(i);
		}
	}
}

void eggNyangBullet::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].image->frameRender2(_vBullet[i].x, _vBullet[i].y, _vBullet[i].currentFrameX, 0);

		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			D2DRENDER->DrawRectangle(_vBullet[i].rc, D2DDEFAULTBRUSH::Purple, 1.0f);
		}
	}
}

void eggNyangBullet::bulletFire(float x, float y, int bulletCount)
{
	if (EGGNYANGBULLETMAX <= bulletCount) return;
	
	tagEggNyangBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEggNyangBullet));
	bullet.image = IMAGEMANAGER->findImage("eggNyangBullet");
	bullet.width = bullet.image->getFrameWidth();
	bullet.height = bullet.image->getFrameHeight();
	bullet.x = x;
	bullet.y = y;
	bullet.radiusX = bullet.image->getFrameWidth() / 2;
	bullet.speed = 5;
	bullet.frameCount = 0;
	bullet.currentFrameX = 0;
	bullet.rc = RectMake(bullet.x, bullet.y,
		bullet.image->getFrameWidth(), bullet.image->getFrameHeight());

	if (bulletCount % 4 == 0)
	{
		bullet.angle = GetAngle(bullet.x, bullet.y, WINSIZEX, bullet.y) + (bulletCount / 4) * 0.1;
	}
	else if (bulletCount % 4 == 1)
	{
		bullet.angle = GetAngle(bullet.x, bullet.y, bullet.x, WINSIZEY) + (bulletCount / 4) * 0.1;
	}
	else if (bulletCount % 4 == 2)
	{
		bullet.angle = GetAngle(bullet.x, bullet.y, 0, bullet.y) + (bulletCount / 4) * 0.1;
	}
	else if (bulletCount % 4 == 3)
	{
		bullet.angle = GetAngle(bullet.x, bullet.y, bullet.x, 0) + (bulletCount / 4) * 0.1;
	}
	
	_vBullet.push_back(bullet);
}

void eggNyangBullet::bulletMove()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;
	}
}
