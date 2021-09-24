#include "stdafx.h"
#include "bulletKingAttack3.h"

bulletKingState * bulletKingAttack3::InputHandle(bulletKing * bulletKing)
{
	if (_count >= 200) return new bulletKingIdle();
	if (bulletKing->getBulletKing().currentHp <= 3) return new bulletKingDeath();
	return nullptr;
}

void bulletKingAttack3::enter(bulletKing * bulletKing)
{
	SOUNDMANAGER->addSound("ºí·¿Å·°ø°Ý3", "sound/ºí·¿Å·°ø°Ý3.wav", false, false);
	SOUNDMANAGER->play("ºí·¿Å·°ø°Ý3");
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingAttack3"));
	bulletKing->setBulletKingIsAttack3(true);
	bulletKing->setBulletKingCurrentFrameX(0);

	_count = 0;
	bulletKing->getBulletKingBullet()->bulletFire3(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y);
}

void bulletKingAttack3::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 10 == 0)
	{
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		if(bulletKing->getBulletKing().currentFrameX == 1) bulletKing->getBulletKingBullet()->bulletFire3(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
	}
}

void bulletKingAttack3::render(bulletKing * bulletKing)
{
}

void bulletKingAttack3::exit(bulletKing * bulletKing)
{
}
