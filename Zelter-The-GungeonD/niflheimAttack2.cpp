#include "stdafx.h"
#include "niflheimAttack2.h"

#include "niflheim.h"

#include "niflheimIdle.h"
#include "niflheimDie.h"

state * niflheimAttack2::inputHandle(niflheim * niflheim)
{
	if (_stateEnd) return new niflheimIdle();
	if (niflheim->getNiflheim().currentHP <= 0) return new niflheimDie();
	return nullptr;
}

void niflheimAttack2::update(niflheim * niflheim)
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
				niflheim->getNiflheim().iceSpear->iceSpearFire(niflheim->getPlayer()->getPlayer().x, niflheim->getPlayer()->getPlayer().y);
				SOUNDMANAGER->play("니플헤임공격1");
			}
			_count = 0;
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0)
			{
				_stateEnd = true;
				niflheim->getNiflheim().iceSpear->iceSpearFire(niflheim->getPlayer()->getPlayer().x, niflheim->getPlayer()->getPlayer().y);
				SOUNDMANAGER->play("니플헤임공격1");
			}
			_count = 0;
		}
	}

	startLine.x = 50;
	startLine.y = niflheim->getPlayer()->getPlayer().y;
	endLine.x = WINSIZEX - 100;
	endLine.y = startLine.y;
}

void niflheimAttack2::enter(niflheim * niflheim)
{
	SOUNDMANAGER->addSound("니플헤임공격1", "sound/니플헤임공격1.wav", false, false);

	_currentStateName = "niflheimIceSpear";
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

	
}

void niflheimAttack2::exit(niflheim * niflheim)
{
}

void niflheimAttack2::render(niflheim * niflheim)
{
	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}

	if (_currentFrameX >= 5 && !_stateEnd)
	{
		D2DRENDER->DrawLine(startLine, endLine, D2DDEFAULTBRUSH::Red, 5.0f);
	}
}
