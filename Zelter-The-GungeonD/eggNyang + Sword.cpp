#include "stdafx.h"
#include "eggNyangBullet.h"


HRESULT eggNyangSword::init()
{
	return S_OK;
}

void eggNyangSword::release(int index)
{
	_vSword.erase(_vSword.begin() + index);
}

void eggNyangSword::update()
{
}

void eggNyangSword::render()
{
	for (int i = 0; i < _vSword.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			D2DRENDER->FillRectangle(_vSword[i].rc, D2DDEFAULTBRUSH::Purple, _vSword[i].angle * (180 / PI));
		}

		_vSword[i].image->render(_vSword[i].x, _vSword[i].y, 1.0f, 1.0f, _vSword[i].angle * (180 / PI), _vSword[i].radiusX, _vSword[i].radiusY);
	}
}

void eggNyangSword::setSword(float targetX, float targetY)
{
	for (int i = 0; i < MAXSOWRD; i++)
	{
		if (MAXSOWRD <= _vSword.size()) return;

		tagEggNyangBullet sword;
		ZeroMemory(&sword, sizeof(tagEggNyangBullet));
		sword.image = IMAGEMANAGER->findImage("eggNyangSword");
		sword.width = sword.image->getWidth();
		sword.height = sword.image->getHeight();
		sword.x = 400 + i * 100;
		sword.y = 200;
		sword.radiusX = sword.image->getWidth() / 2;
		sword.radiusY = sword.image->getHeight() / 2;
		sword.speed = 15;
		sword.angle = (targetX, targetY, sword.x, sword.y);
		sword.frameCount = 0;
		sword.currentFrameX = 0;
		sword.rc = RectMake(sword.x, sword.y,
			sword.image->getWidth(), sword.image->getHeight());

		_vSword.push_back(sword);
	}
}

void eggNyangSword::moveSword(float targetX, float targetY, bool fire)
{
	for (int i = 0; i < _vSword.size(); i++)
	{
		SOUNDMANAGER->play("에그냥공격2");
		if (fire)
		{
			_vSword[i].angle = GetAngle(_vSword[i].x + _vSword[i].radiusX, _vSword[i].y + _vSword[i].radiusY, targetX, targetY);
			_vSword[i].rc = RectMake(_vSword[i].x, _vSword[i].y, _vSword[i].image->getWidth(), _vSword[i].image->getHeight());
		}
		else if (!fire)
		{
			_vSword[i].x += cosf(_vSword[i].angle) * _vSword[i].speed;
			_vSword[i].y += -sinf(_vSword[i].angle) * _vSword[i].speed;
		}
		if ((_vSword[i].y + _vSword[i].image->getHeight() / 2) >= WINSIZEY
			|| (_vSword[i].x + _vSword[i].image->getWidth() /2) >= WINSIZEX) release(i);
	}
	
}
