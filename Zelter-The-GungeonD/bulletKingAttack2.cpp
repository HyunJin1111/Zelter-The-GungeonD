#include "stdafx.h"
#include "bulletKingAttack2.h"
#include "player.h"

bulletKingState * bulletKingAttack2::InputHandle(bulletKing * bulletKing)
{
	if (_count >= 25) return new bulletKingIdle();
	if (bulletKing->getBulletKing().currentHp <= 3) return new bulletKingDeath();
	return nullptr;
}

void bulletKingAttack2::enter(bulletKing * bulletKing)
{
	SOUNDMANAGER->addSound("ºí·¿Å·°ø°Ý1", "sound/ºí·¿Å·°ø°Ý1.wav", false, false);
	SOUNDMANAGER->play("ºí·¿Å·°ø°Ý1");
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingAttack2"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);

	//ÃÑ¾Ë ¹ß»ç1
	bulletKing->getBulletKingBullet()->bulletFire2(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y, bulletKing->getPlayer()->getPlayer().x, bulletKing->getPlayer()->getPlayer().y);
	_count = 0;
}

void bulletKingAttack2::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 15 == 0)
	{
		//ÃÑ¾Ë ¹ß»ç2
		bulletKing->getBulletKingBullet()->bulletFire2(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y, bulletKing->getPlayer()->getPlayer().x, bulletKing->getPlayer()->getPlayer().y);
		SOUNDMANAGER->play("ºí·¿Å·°ø°Ý1");
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
	}
}

void bulletKingAttack2::render(bulletKing * bulletKing)
{
}

void bulletKingAttack2::exit(bulletKing * bulletKing)
{
}
