#include "stdafx.h"
#include "bulletKingHit.h"

bulletKingState * bulletKingHit::InputHandle(bulletKing * bulletKing)
{
	if (_count >= 25) return new bulletKingIdle();
	if (bulletKing->getBulletKing().currentHp <= 3) return new bulletKingDeath();
	return nullptr;
}

void bulletKingHit::enter(bulletKing * bulletKing)
{
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingHit"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);
	_count = 0;
}

void bulletKingHit::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 10 == 0)
	{
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
		_count = 0;
	}
}

void bulletKingHit::render(bulletKing * bulletKing)
{
}

void bulletKingHit::exit(bulletKing * bulletKing)
{
}
