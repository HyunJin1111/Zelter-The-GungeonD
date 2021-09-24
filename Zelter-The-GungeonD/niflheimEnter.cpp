#include "stdafx.h"
#include "niflheimEnter.h"

#include "niflheim.h"

#include "niflheimIdle.h"
#include "niflheimDie.h"
#include "niflheimAttack1.h"
#include "niflheimAttack2.h"
#include "niflheimAttack3.h"

state * niflheimEnter::inputHandle(niflheim * nifleheim)
{
	if (nifleheim->getNiflheim().currentHP <= 0) return new niflheimDie();
	if (_stateEnd && (_randomPatternCount % 3) == 0) return new niflheimAttack1();
	else if (_stateEnd && (_randomPatternCount % 3) == 1) return new niflheimAttack2();
	else if (_stateEnd && (_randomPatternCount % 3) == 2) return new niflheimAttack3();
	return nullptr;
}

void niflheimEnter::update(niflheim * niflheim)
{
	_count++;
	if (_count % 7 == 0)
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
}

void niflheimEnter::enter(niflheim * niflheim)
{
	_currentStateName = "niflheimEnter";
	niflheim->setImg(IMAGEMANAGER->findImage("niflheimEnter"));
	_count = 0;
	if (niflheim->getNiflheim().direction == 0)
	{
		_currentFrameX = 0;
		_currentFrameY = 0;
	}
	else
	{
		_currentFrameX = 15;
		_currentFrameY = 1;
	}

	_randomPatternCount = RND->getFromIntTo(0, 100);
	enterPosition(niflheim, _randomPatternCount % 5);
}

void niflheimEnter::exit(niflheim * niflheim)
{
}

void niflheimEnter::render(niflheim * niflheim)
{
	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}
}

void niflheimEnter::enterPosition(niflheim* niflheim, int randomCount)
{
	switch (randomCount)
	{
	case 0:
		niflheim->setX(WINSIZEX / 2);
		niflheim->setY(WINSIZEY / 2);
		break;
	case 1:
		niflheim->setX(200);
		niflheim->setY(WINSIZEY / 2);
		break;
	case 2:
		niflheim->setX(WINSIZEX / 2);
		niflheim->setY(200);
		break;
	case 3:
		niflheim->setX(WINSIZEX - (200 + niflheim->getNiflheim().img->getFrameWidth()));
		niflheim->setY(WINSIZEY / 2);
		break;
	case 4:
		niflheim->setX(WINSIZEX / 2);
		niflheim->setY(WINSIZEY - (300 + niflheim->getNiflheim().img->getFrameHeight()));
		break;
	}
}
