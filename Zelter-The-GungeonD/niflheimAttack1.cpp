#include "stdafx.h"
#include "niflheimAttack1.h"

#include "niflheim.h"

#include "niflheimDie.h"
#include "niflheimIdle.h"

state * niflheimAttack1::inputHandle(niflheim * niflheim)
{
	if (_stateEnd) return new niflheimIdle();
	if (niflheim->getNiflheim().currentHP <= 0) return new niflheimDie();

	return nullptr;
}

void niflheimAttack1::update(niflheim * niflheim)
{
	_count++;
	if (_count % 12 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= niflheim->getNiflheim().img->getMaxFrameX())
			{
				_stateEnd = true;
				niflheim->getNiflheim().iceicle->firstIcicleFire();
				SOUNDMANAGER->play("니플헤임공격3");
			}

			_count = 0;
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0)\
			{
				_stateEnd = true;
				niflheim->getNiflheim().iceicle->firstIcicleFire();
				SOUNDMANAGER->play("니플헤임공격3");
			}

			_count = 0;
		}
	}
}

void niflheimAttack1::enter(niflheim * niflheim)
{
	SOUNDMANAGER->addSound("니플헤임공격3", "sound/니플헤임공격3.wav", false, false);
	_currentStateName = "niflheimIcicle";
	niflheim->setImg(IMAGEMANAGER->findImage("niflheimAttack"));
	if (niflheim->getNiflheim().direction == 0)
	{
		_currentFrameY = 0;
		_currentFrameX = 0;
	}
	else
	{
		_currentFrameY = 1;
		_currentFrameX = 10;
	}
	_count = 0;
	_stateEnd = false;

	for (int i = 0; i < MAXICICLE; i++)
	{
		POINT startPoint;
		POINT endPoint;
		if (i % 2 == 0)
		{
			startPoint.x = 200 + (i / 2 * 200);
			endPoint.x = startPoint.x;
		}
		else
		{
			startPoint.x = 100 + (i / 2 * 200);
			endPoint.x = startPoint.x;
		}

		startPoint.y = 50;
		endPoint.y = WINSIZEY - 50;

		_vStartPoint.push_back(startPoint);
		_vEndPoint.push_back(endPoint);
	}
	
}

void niflheimAttack1::exit(niflheim * niflheim)
{
}

void niflheimAttack1::render(niflheim * niflheim)
{
	for (int i = 0; i < MAXICICLE; i++)
	{
		if (_currentFrameX > 4 && _currentFrameX < 8 && i % 2 == 0)
		{
			D2DRENDER->DrawLine(_vStartPoint[i], _vEndPoint[i], D2DDEFAULTBRUSH::Red, 5.0f);
		}
		if (_currentFrameY == 0 && _currentFrameX >= 8 && i % 2 == 1)
		{
			D2DRENDER->DrawLine(_vStartPoint[i], _vEndPoint[i], D2DDEFAULTBRUSH::Red, 5.0f);
		}
		else if (_currentFrameY == 1 && _currentFrameX <= 3 && i % 2 == 1)
		{
			D2DRENDER->DrawLine(_vStartPoint[i], _vEndPoint[i], D2DDEFAULTBRUSH::Red, 5.0f);
		}
	}

	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}
}
