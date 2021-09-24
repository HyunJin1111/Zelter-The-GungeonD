#include "stdafx.h"
#include "bulletKingAttack1.h"

bulletKingState * bulletKingAttack1::InputHandle(bulletKing * bulletKing)
{
	if (_count >= 45) return new bulletKingIdle();
	if (bulletKing->getBulletKing().currentHp <= 3) return new bulletKingDeath();
	return nullptr;
}

void bulletKingAttack1::enter(bulletKing * bulletKing)
{
	SOUNDMANAGER->addSound("ºí·¿Å·°ø°Ý2", "sound/ºí·¿Å·°ø°Ý2.wav", false, false);
	SOUNDMANAGER->play("ºí·¿Å·°ø°Ý2");
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingAttack1"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);
	bulletKing->setBulletKingY(bulletKing->getBulletKing().y - 10);
	_count = 0;

}

void bulletKingAttack1::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 20 == 0)
	{

		if (bulletKing->getBulletKing().currentFrameX == 0)
		{
			bulletKing->getBulletKingBullet()->bulletFire1(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y);
			bulletKing->setBulletKingY(bulletKing->getBulletKing().y + 10);

			bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
			if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
			_count = 0;
		}
	}
}

void bulletKingAttack1::render(bulletKing * bulletKing)
{
}

void bulletKingAttack1::exit(bulletKing * bulletKing)
{
}
