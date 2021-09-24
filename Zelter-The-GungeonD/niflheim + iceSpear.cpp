#include "stdafx.h"
#include "niflheimBullet.h"

HRESULT niflheimIceSpear::init()
{
	return S_OK;
}

void niflheimIceSpear::release(int index)
{
	_vIceSpear.erase(_vIceSpear.begin() + index);
}

void niflheimIceSpear::update()
{
	for (int i = 0; i < _vIceSpear.size(); i++)
	{
		_vIceSpear[i].frameCount++;
		if (_vIceSpear[i].frameCount % 3 == 0)
		{
			_vIceSpear[i].currentFrameX++;
			if (_vIceSpear[i].currentFrameX >= 12) _vIceSpear[i].currentFrameX = 12;
		}
	}

	iceSpearMove();
}

void niflheimIceSpear::render()
{
	for (int i = 0; i < _vIceSpear.size(); i++)
	{
		_vIceSpear[i].img->frameRender2(_vIceSpear[i].x, _vIceSpear[i].y, _vIceSpear[i].currentFrameX, _vIceSpear[i].currentFrameY);
		
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			D2DRENDER->DrawRectangle(_vIceSpear[i].rc, D2DDEFAULTBRUSH::Purple);
		}
	}
}

void niflheimIceSpear::iceSpearFire(float x, float y)
{
	if (_vIceSpear.size() >= MAXICESPEAR) return;

	tagBullet iceSpear;
	ZeroMemory(&iceSpear, sizeof(tagBullet));
	iceSpear.img = IMAGEMANAGER->findImage("iceSpear");
	iceSpear.width = iceSpear.img->getFrameWidth();
	iceSpear.height = iceSpear.img->getFrameHeight();
	iceSpear.radiusX = iceSpear.img->getFrameWidth() / 2;
	iceSpear.radiusY = iceSpear.img->getFrameHeight() / 2;
	iceSpear.x = 0;
	iceSpear.y = y;
	iceSpear.speed = 35;
	iceSpear.frameCount = 0;
	iceSpear.currentFrameX = 0;
	iceSpear.currentFrameY = 0;

	iceSpear.rc = RectMake(iceSpear.x, iceSpear.y, iceSpear.width, iceSpear.height);

	_vIceSpear.push_back(iceSpear);
}

void niflheimIceSpear::iceSpearMove()
{
	for (int i = 0; i < _vIceSpear.size(); i++)
	{
		if (_vIceSpear[i].currentFrameX >= 12) _vIceSpear[i].x += _vIceSpear[i].speed;
		
		_vIceSpear[i].rc = RectMake(_vIceSpear[i].x, _vIceSpear[i].y, _vIceSpear[i].width, _vIceSpear[i].height);

		if (_vIceSpear[i].x >= WINSIZEX) release(i);
	}
}