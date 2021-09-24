#include "stdafx.h"
#include "eggNyangAttack3.h"

#include "eggNyangIdle.h"
#include "eggNyangDie.h"

#include "eggNyang.h"

eggNyangStateBase * eggNyangAttack3::inputHandle(eggNyang * eggNyang)
{
	if (eggNyang->getBulletFireCount() >= EGGNYANGBULLETMAX) return new eggNyangIdle();
	else if (eggNyang->getEggNyang().currentHp <= 0) return new eggNyangDie();

	return nullptr;
}

void eggNyangAttack3::update(eggNyang * eggNyang)
{
	_count++;

	if (_count % 20 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= eggNyang->getEggNyang().img->getMaxFrameX()) _currentFrameX = 1;
		}
		else if (_currentFrameY == 1)
		{
			_currentFrameX--;
			if (_currentFrameX <= 0) _currentFrameX = 0;
		}
	}

	eggNyangMove(eggNyang, _eggNyangPositionPattern);

	eggNyang->getEggNyang().rc = RectMake(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
		eggNyang->getEggNyang().img->getFrameWidth(), eggNyang->getEggNyang().img->getFrameHeight());
}

void eggNyangAttack3::enter(eggNyang * eggNyang)
{
	_stateName = "eggNyangAttack3";
	eggNyang->setImage(IMAGEMANAGER->findImage("eggNyangAttack"));
	_count = 0;
	_currentFrameY = eggNyang->getEggNyang().direction;
	if (_currentFrameY == 0) _currentFrameX = 0;
	else _currentFrameX = 1;

	_stateEnd = false;

	_eggNyangPositionPattern = 3;
	movePosition(eggNyang, _eggNyangPositionPattern);
}

void eggNyangAttack3::render(eggNyang * eggNyang)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(eggNyang->getEggNyang().rc, D2DDEFAULTBRUSH::Red, 1.0f);
	}
	eggNyang->getEggNyang().img->frameRender2(eggNyang->getEggNyang().rc.left, eggNyang->getEggNyang().rc.top, _currentFrameX, _currentFrameY);
}

void eggNyangAttack3::exit(eggNyang * eggNyang)
{
}

void eggNyangAttack3::movePosition(eggNyang * eggNyang, int eggNyangPositionPattern)
{
	switch (eggNyangPositionPattern)
	{
	case 1:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y, 200, 200);
		break;
	case 2:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
			WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()), 200);
		break;
	case 3:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
			WINSIZEX / 2 - 50, WINSIZEY / 2 - 200);
		break;
	case 4:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
			200, WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()));
		break;
	case 5:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
			WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()), WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()));
		break;
	}

	_isMove = true;
}

void eggNyangAttack3::eggNyangMove(eggNyang * eggNyang, int eggNyangPositionPattern)
{
	switch (eggNyangPositionPattern)
	{
	case 1:
		if (eggNyang->getEggNyang().x <= 200 || eggNyang->getEggNyang().y <= 200)
		{
			eggNyang->setEggNyangX(201);
			eggNyang->setEggNyangY(201);
			_isMove = false;
		}
		break;
	case 2:
		if (eggNyang->getEggNyang().x >= WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth())
			|| eggNyang->getEggNyang().y <= 200)
		{
			eggNyang->setEggNyangX(WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameHeight()) + 1);
			eggNyang->setEggNyangY(201);
			_isMove = false;
		}
		break;
	case 3:
		if (eggNyang->getEggNyang().x <= WINSIZEX / 2)
		{
			eggNyang->setEggNyangX(WINSIZEX / 2 - 50 + 1);
			eggNyang->setEggNyangY(WINSIZEY / 2 - 200);
			_isMove = false;
		}
		break;
	case 4:
		if (eggNyang->getEggNyang().x <= 200 || eggNyang->getEggNyang().y >= WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()))
		{
			eggNyang->setEggNyangX(201);
			eggNyang->setEggNyangY(WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()) + 1);
			_isMove = false;
		}
		break;
	case 5:
		if (eggNyang->getEggNyang().x >= WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()) || eggNyang->getEggNyang().y >= WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()))
		{
			eggNyang->setEggNyangX(WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()) + 1);
			eggNyang->setEggNyangY(WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()) + 1);
			_isMove = false;
		}
		break;
	}
}
