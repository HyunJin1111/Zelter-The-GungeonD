#include "stdafx.h"
#include "playerDonwJump.h"
#include "playerAttack.h"
#include "playerHit.h"
#include "playerDie.h"
#include "playerDash.h"

playerState * playerDonwJump::inputHandle(player * player)
{
	if (player->getPlayer().y >= WINSIZEY - 100)return new playerStateIdle;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack;
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerDash;
	if (player->getPlayer().isHit == true) return new playerHit;

	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}

	return nullptr;
}

void playerDonwJump::update(player * player)
{
	if (player->getPlayer().y < WINSIZEY - 100) player->setPlayerY(player->getPlayer().y + _jumpPower);
	

	_count++;

	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}
}

void playerDonwJump::enter(player * player)
{
	if (player->getPlayer().direction == 0) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_downjump"));
	if (player->getPlayer().direction == 1) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_downjump"));
	_jumpPower = 15.0f;
}

void playerDonwJump::exit(player * player)
{
}