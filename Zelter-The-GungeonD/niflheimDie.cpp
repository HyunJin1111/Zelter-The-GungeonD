#include "stdafx.h"
#include "niflheimDie.h"

#include "niflheim.h"

#include "niflheimIdle.h"

state * niflheimDie::inputHandle(niflheim * niflheim)
{
	//if (_stateEnd) return new niflheimIdle();
	return nullptr;
}

void niflheimDie::update(niflheim * niflheim)
{
	_count++;
	if (_count % 10 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= niflheim->getNiflheim().img->getMaxFrameX()) _stateEnd = true;

			_count = 0;
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0) _stateEnd = true;

			_count = 0;
		}
	}

	for (int i = 0; i < niflheim->getNiflheim().icePillar->getVIcePillar().size(); i++)
	{
		niflheim->getNiflheim().icePillar->dieRelease(i);
	}
	
	if (_stateEnd)
	{
		SOUNDMANAGER->stop("niflheimBGM");
		SCENEMANAGER->changeScene("openWorld");
	}
}

void niflheimDie::enter(niflheim * niflheim)
{
	_currentStateName = "niflheimDie";
	niflheim->setImg(IMAGEMANAGER->findImage("niflheimDie"));
	_count = 0;
	if (niflheim->getNiflheim().direction == 0)
	{
		_currentFrameY = 0;
		_currentFrameX = 0;
	}
	else
	{
		_currentFrameY = 1;
		_currentFrameX = 29;
	}
	
	_stateEnd = false;
}

void niflheimDie::exit(niflheim * niflheim)
{
}

void niflheimDie::render(niflheim * niflheim)
{
	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}
}
