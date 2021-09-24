#include "stdafx.h"
#include "niflheimBullet.h"

HRESULT niflheimIcicle::init()
{
	return S_OK;
}

void niflheimIcicle::release(int index)
{
	_vIcicle.erase(_vIcicle.begin() + index);
}

void niflheimIcicle::update()
{
	for (int i = 0; i < _vIcicle.size(); i++)
	{
		_vIcicle[i].rc = RectMake(_vIcicle[i].x, _vIcicle[i].y, _vIcicle[i].width, _vIcicle[i].height);

		if (!_vIcicle[i].ready)
		{
			_vIcicle[i].frameCount++;
			if (_vIcicle[i].frameCount % 5 == 0)
			{
				_vIcicle[i].currentFrameX++;
				if (_vIcicle[i].currentFrameX >= 8) _vIcicle[i].ready = true;
				_vIcicle[i].frameCount = 0;
			}
		}
		else if (_vIcicle[i].ready && !_vIcicle[i].destroy)
		{
			_vIcicle[i].img = IMAGEMANAGER->findImage("icicle");
			icicleMove();
		}

		if (_vIcicle[i].destroy)
		{
			_vIcicle[i].frameCount++;
			if (_vIcicle[i].frameCount % 5 == 0)
			{
				_vIcicle[i].currentFrameX++;
				if (_vIcicle[i].currentFrameX >= 2)
				{
					release(i);
					if (!_isSceond) sceondIcicleFire();
				}
			}
		}
	}
}

void niflheimIcicle::render()
{
	for (int i = 0; i < _vIcicle.size(); i++)
	{
		if (!_vIcicle[i].ready || _vIcicle[i].destroy) _vIcicle[i].img->frameRender2(_vIcicle[i].x, _vIcicle[i].y, _vIcicle[i].currentFrameX, 0);
		else if (_vIcicle[i].ready && !_vIcicle[i].destroy) _vIcicle[i].img->render(_vIcicle[i].x, _vIcicle[i].y);

		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			D2DRENDER->DrawRectangle(_vIcicle[i].rc, D2DDEFAULTBRUSH::Purple);
		}
	}
}

void niflheimIcicle::firstIcicleFire()
{

	for (int i = 0; i < 6; i++)
	{
		if (_vIcicle.size() >= MAXICICLE) return;

		tagBullet icicle;
		ZeroMemory(&icicle, sizeof(tagBullet));
		icicle.img = IMAGEMANAGER->findImage("icicleReady");
		icicle.width = icicle.img->getFrameWidth();
		icicle.height = icicle.img->getFrameHeight();
		icicle.radiusX = icicle.img->getFrameWidth() / 2;
		icicle.radiusY = icicle.img->getFrameHeight() / 2;
		icicle.ready = false;
		icicle.destroy = false;

		icicle.x = 200 + (i * 200);
		icicle.y = 50;

		icicle.speed = 20;
		icicle.frameCount = 0;
		icicle.currentFrameX = 0;
		icicle.currentFrameY = 0;

		icicle.rc = RectMake(icicle.x, icicle.y, icicle.width, icicle.height);

		_vIcicle.push_back(icicle);
	}

	_isSceond = false;
}

void niflheimIcicle::sceondIcicleFire()
{
	for (int i = 0; i < 6; i++)
	{
		if (_vIcicle.size() >= MAXICICLE) return;

		tagBullet icicle;
		ZeroMemory(&icicle, sizeof(tagBullet));
		icicle.img = IMAGEMANAGER->findImage("icicleReady");
		icicle.width = icicle.img->getFrameWidth();
		icicle.height = icicle.img->getFrameHeight();
		icicle.radiusX = icicle.img->getFrameWidth() / 2;
		icicle.radiusY = icicle.img->getFrameHeight() / 2;
		icicle.ready = false;
		icicle.destroy = false;

		icicle.x = 100 + (i * 200);
		icicle.y = 50;

		icicle.speed = 20;
		icicle.frameCount = 0;
		icicle.currentFrameX = 0;
		icicle.currentFrameY = 0;

		icicle.rc = RectMake(icicle.x, icicle.y, icicle.width, icicle.height);

		_vIcicle.push_back(icicle);
	}

	_isSceond = true;
}

void niflheimIcicle::icicleMove()
{
	for (int i = 0; i < _vIcicle.size(); i++)
	{
		_vIcicle[i].y += _vIcicle[i].speed;

		if (_vIcicle[i].y >= WINSIZEY - 100)
		{
			_vIcicle[i].destroy = true;
			_vIcicle[i].img = IMAGEMANAGER->findImage("icicleDestroy");
			_vIcicle[i].currentFrameX = 0;
		}
	}
}