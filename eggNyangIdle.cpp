#include "stdafx.h"
#include "eggNyangIdle.h"
#include "eggNyangAttack1.h"
#include "eggNyangAttack2.h"
#include "eggNyangAttack3.h"
#include "eggNyangDie.h"

#include "eggNyang.h"

eggNyangStateBase * eggNyangIdle::inputHandle(eggNyang* eggNyang)
{
	if (_stateEnd && _rndPattern == 0) return new eggNyangAttack1();
	else if (_stateEnd && _rndPattern == 1) return new eggNyangAttack2();
	else if (_stateEnd && _rndPattern == 2) return new eggNyangAttack3();
	else if (eggNyang->getEggNyang().currentHp <= 0) return new eggNyangDie();

	return nullptr;
}

void eggNyangIdle::update(eggNyang* eggNyang)
{
	_count++;

	if (_count % 20 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= eggNyang->getEggNyang().img->getMaxFrameX() - 1) _currentFrameX = 0;
		}
		else if (_currentFrameY == 1)
		{
			if (_currentFrameX <= 0) _currentFrameX = 1;
			_currentFrameX--;
		}
	}

	if (_count >= _randomPatternCount) _stateEnd = true;

}

void eggNyangIdle::enter(eggNyang * eggNyang)
{
	_stateName = "eggNyangIdle";
	eggNyang->setImage(IMAGEMANAGER->findImage("eggNyangIdle"));
	_count = 0;
	_currentFrameY = eggNyang->getEggNyang().direction;
	if (_currentFrameY == 0) _currentFrameX = 0;
	else _currentFrameX = 1;
	eggNyang->getEggNyang().rc = RectMake(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y, eggNyang->getEggNyang().img->getFrameWidth(), eggNyang->getEggNyang().img->getFrameHeight());
	_randomPatternCount = RND->getFromIntTo(0, 100);
	_rndPattern = RND->getFromIntTo(0, 3);
	_isMove = false;

	eggNyang->setBulletFireCount(0);
}

void eggNyangIdle::render(eggNyang * eggNyang)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(eggNyang->getEggNyang().rc, D2DDEFAULTBRUSH::Red, 1.0f);
	}

	eggNyang->getEggNyang().img->frameRender2(eggNyang->getEggNyang().rc.left, eggNyang->getEggNyang().rc.top, _currentFrameX, _currentFrameY);
}

void eggNyangIdle::exit(eggNyang * eggNyang)
{
}
