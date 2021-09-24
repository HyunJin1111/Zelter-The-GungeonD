#include "stdafx.h"
#include "niflheimIdle.h"

#include "niflheim.h"

#include "niflheimEnter.h"
#include "niflheimDie.h"


state * niflheimIdle::inputHandle(niflheim * niflheim)
{
	if (niflheim->getNiflheim().currentHP <= 0) return new niflheimDie();
	if (_stateEnd) return new niflheimEnter();
	return nullptr;
}

void niflheimIdle::update(niflheim * niflheim)
{
	_count++;
	if (_count % 10 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= niflheim->getNiflheim().img->getMaxFrameX()) _currentFrameX = 0;
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0) _currentFrameX = 5;
		}
	}

	if (_count >= 300) _stateEnd = true;
}

void niflheimIdle::enter(niflheim * niflheim)
{
	_currentStateName = "niflheimIdle";
	niflheim->setImg(IMAGEMANAGER->findImage("niflheimIdle"));
	_count = 0;
	if (niflheim->getNiflheim().direction == 0)
	{
		_currentFrameX = 0;
		_currentFrameY = 0;
	}
	else
	{
		_currentFrameX = 5;
		_currentFrameY = 1;
	}
	_stateEnd = false;
}

void niflheimIdle::exit(niflheim * niflheim)
{
}

void niflheimIdle::render(niflheim * niflheim)
{
	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}
}
