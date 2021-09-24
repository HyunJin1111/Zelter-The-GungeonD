#include "stdafx.h"
#include "eggNyangAttack1.h"
#include "eggNyangIdle.h"
#include "eggNyangDie.h"

#include "eggNyang.h"

eggNyangStateBase * eggNyangAttack1::inputHandle(eggNyang * eggNyang)
{
	//나중에는 스테이트 엔드로 받아올 거예요
	if (_stateEnd) return new eggNyangIdle();
	else if (eggNyang->getEggNyang().currentHp <= 0) return new eggNyangDie();
	return nullptr;
}

void eggNyangAttack1::update(eggNyang * eggNyang)
{
	_count++;

	if (_count % 20 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= eggNyang->getEggNyang().img->getMaxFrameX()) _stateEnd = true;
		}
		else if (_currentFrameY == 1)
		{
			_currentFrameX--;
			if (_currentFrameX <= 0)  _stateEnd = true;
		}
	}

	eggNyangMove(eggNyang, _eggNyangPositionPattern);

	eggNyang->getEggNyang().rc = RectMake(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
		eggNyang->getEggNyang().img->getFrameWidth(), eggNyang->getEggNyang().img->getFrameHeight());
}

void eggNyangAttack1::enter(eggNyang * eggNyang)
{
	_stateName = "eggNyangAttack1";
	eggNyang->setImage(IMAGEMANAGER->findImage("eggNyangAttack"));
	_count = 0;
	_currentFrameY = eggNyang->getEggNyang().direction;
	if (_currentFrameY == 0) _currentFrameX = 0;
	else _currentFrameX = 1;

	_isMove = true;
	_stateEnd = false;

	_eggNyangPositionPattern = RND->getFromIntTo(1, 5);
	movePosition(eggNyang, _eggNyangPositionPattern);

	eggNyang->getEggNyang().sword->setSword(eggNyang->getPlayer()->getPlayer().x, eggNyang->getPlayer()->getPlayer().y);
}

void eggNyangAttack1::render(eggNyang * eggNyang)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(eggNyang->getEggNyang().rc, D2DDEFAULTBRUSH::Red, 1.0f);
	}
	eggNyang->getEggNyang().img->frameRender2(eggNyang->getEggNyang().rc.left, eggNyang->getEggNyang().rc.top, _currentFrameX, _currentFrameY);
}

void eggNyangAttack1::exit(eggNyang * eggNyang)
{
}

void eggNyangAttack1::movePosition(eggNyang* eggNyang, int eggNyangPositionPattern)
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
			200, WINSIZEY - (200 + eggNyang->getEggNyang().img->getFrameHeight()));
		break;
	case 5:
		_angle = GetAngle(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y,
			WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()), WINSIZEY - (200 + eggNyang->getEggNyang().img->getFrameHeight()));
		break;
	}

	_isMove = true;
}

void eggNyangAttack1::eggNyangMove(eggNyang* eggNyang, int eggNyangPositionPattern)
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
			eggNyang->setEggNyangX(WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()) + 1);
			eggNyang->setEggNyangY(201);
			_isMove = false;
		}
		break;
	case 3:
		if (eggNyang->getEggNyang().x <= WINSIZEX / 2 - 50)
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
			eggNyang->setEggNyangY(WINSIZEY - (200 + eggNyang->getEggNyang().img->getFrameHeight()) + 1);
			_isMove = false;
		}
		break;
	case 5:
		if (eggNyang->getEggNyang().x >= WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()) || eggNyang->getEggNyang().y >= WINSIZEY - (300 + eggNyang->getEggNyang().img->getFrameHeight()))
		{
			eggNyang->setEggNyangX(WINSIZEX - (200 + eggNyang->getEggNyang().img->getFrameWidth()) + 1);
			eggNyang->setEggNyangY(WINSIZEY - (200 + eggNyang->getEggNyang().img->getFrameHeight()) + 1);
			_isMove = false;
		}
		break;
	}
}