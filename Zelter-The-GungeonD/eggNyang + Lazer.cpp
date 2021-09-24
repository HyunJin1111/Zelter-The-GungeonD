#include "stdafx.h"
#include "eggNyangBullet.h"

HRESULT eggNyangLazer::init()
{
	return S_OK;
}

void eggNyangLazer::release()
{
	_vLazer.clear();
}

void eggNyangLazer::update()
{
	_lazerTime++;
	if (_lazerTime == 50 && !_lazerFire)
	{
		_vLazer[0].image = IMAGEMANAGER->findImage("eggNyangLazer1");
		
		for (int i = 0; i < _vLazer.size(); i++)
		{
			if (_vLazer[i].currentFrameY == 0)  _vLazer[i].currentFrameX = 2;
			else  _vLazer[i].currentFrameX = 0;
		}
	}
	else if (_lazerTime >= 350 && !_lazerFire)
	{
		_lazerFire = true;
	}
	else if (_lazerTime >= 400) release();

	for (int i = 0; i < _vLazer.size(); i++)	//프레임 돌려줍니다
	{
		if (_lazerTime >= 50)
		{
			_vLazer[i].frameCount++;
			if (_vLazer[i].frameCount % 5 == 0)
			{
				if (_vLazer[i].currentFrameY == 0)
				{
					_vLazer[i].currentFrameX++;
					if (_vLazer[i].currentFrameX >= _vLazer[i].image->getMaxFrameX()) _vLazer[i].currentFrameX = 0;
				}
				else
				{
					if (_vLazer[i].currentFrameX <= 0) _vLazer[i].currentFrameX = _vLazer[i].image->getMaxFrameX();
					_vLazer[i].currentFrameX--;
				}

				_vLazer[i].frameCount = 0;
			}
		}
	}

	lazerFire();
}

void eggNyangLazer::render()
{
	for (int i = 0; i < _vLazer.size(); i++)
	{
		if (_lazerTime >= 50)
		{
			_vLazer[i].image->frameRender2(_vLazer[i].rc.left, _vLazer[i].rc.top, _vLazer[i].currentFrameX, _vLazer[i].currentFrameY);
			
			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				D2DRENDER->DrawRectangle(_vLazer[i].rc, D2DDEFAULTBRUSH::Purple);
			}
		}
		else if (i == 0)_vLazer[i].image->render(_vLazer[i].rc.left, _vLazer[i].rc.top);
	}
}

void eggNyangLazer::lazerReady(float x, float y, int direction)
{
	for (int i = 0; i < MAXLAZESIZE; i++)
	{
		if (MAXLAZESIZE <= _vLazer.size()) return;
		tagEggNyangBullet lazer;
		ZeroMemory(&lazer, sizeof(tagEggNyangBullet));
		if (i == 0)
		{
			lazer.image = IMAGEMANAGER->findImage("eggNyangLazerReady");
			if (direction == 0) lazer.currentFrameY = 1;
			else lazer.currentFrameY = 0;
			lazer.currentFrameX = 0;
			if (lazer.currentFrameY == 0) lazer.x = 0 + 200;
			else lazer.x = WINSIZEX - 250;
		}
		else
		{
			lazer.image = IMAGEMANAGER->findImage("eggNyangLazer2");
			if (direction == 0) lazer.currentFrameY = 1;
			else lazer.currentFrameY = 0;

			if (lazer.currentFrameY == 0)
			{
				lazer.currentFrameX = 0;
				lazer.x = _vLazer[i - 1].x - lazer.image->getFrameWidth();
			}
			else
			{
				lazer.currentFrameX = 2;
				lazer.x = _vLazer[i - 1].x + _vLazer[i - 1].image->getFrameWidth();
			}
		}
		lazer.y = y;
		lazer.width = lazer.image->getFrameWidth();
		lazer.height = lazer.image->getFrameHeight();
		lazer.radiusX = lazer.image->getFrameWidth() / 2;
		lazer.frameCount = 0;
		
		lazer.rc = RectMake(lazer.x, lazer.y,
			lazer.image->getFrameWidth(), lazer.image->getFrameHeight());

		_vLazer.push_back(lazer);
	}
	
	_lazerFire = false;
	_lazerTime = 0;
}

void eggNyangLazer::lazerFire()
{
	SOUNDMANAGER->play("에그냥공격3");
	for (int i = 0; i < _vLazer.size(); i++)	//이미지가 계속 바뀌기 때문에 x, 값, 가로세로, rc 갱신 계속 해주기
	{
		_vLazer[i].width = _vLazer[i].image->getFrameWidth();
		_vLazer[i].height = _vLazer[i].image->getFrameHeight();
		
		if (i > 0)
		{
			if (_vLazer[i].currentFrameY == 0) _vLazer[i].x = _vLazer[i - 1].x + _vLazer[i - 1].image->getFrameWidth();
			else _vLazer[i].x = _vLazer[i - 1].x - _vLazer[i].image->getFrameWidth();

			_vLazer[i].rc = RectMake(_vLazer[i].x, _vLazer[i].y - 1.5f, _vLazer[i].image->getFrameWidth(), _vLazer[i].image->getFrameHeight());
		}

		if (_lazerFire)
		{		
			if (i == 0) _vLazer[i].image = IMAGEMANAGER->findImage("eggNyangLazer1End");
			else _vLazer[i].image = IMAGEMANAGER->findImage("eggNyangLazer2End");

			_vLazer[i].rc = RectMake(_vLazer[i].x, _vLazer[i].y, _vLazer[i].image->getFrameWidth(), _vLazer[i].image->getFrameHeight());
		}
	}
}

void eggNyangLazer::lazerMove()
{
}
