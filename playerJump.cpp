#include "stdafx.h"
#include "playerJump.h"
#include "playerStateIdle.h"
#include "playerDie.h"
#include "playerHit.h"
#include "playerAttack.h"
#include "playerRun.h"
#include "playerDash.h"
#include "playerFall.h"

playerState * playerJump::inputHandle(player * player)
{
	
	if (_jumpPower <= 0)
	{
		player->setPlayerisEnd(true);
		return new playerFall;
	}

	if (player->getPlayer().y >= WINSIZEY - 100)
	{
		player->setIsjump(false);
		return new playerStateIdle();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack();
	if (player->getPlayer().isHit == true) return new playerHit();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerDash;
	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}
	return nullptr;
}

void playerJump::update(player * player)
{
	player->setPlayerY(player->getPlayer().y - _jumpPower);
	_jumpPower -= _gravity;


	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed*2);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed*2);
	}




	
	_count++;
	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}

	

	return;
	
}

void playerJump::enter(player * player)
{
	_jumpPower = 13.0f;
	_gravity = 0.4f;
	if (player->getPlayer().direction == 0) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_jump"));
	if (player->getPlayer().direction == 1) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_jump"));
	player->setIsjump(true);
	player->setPlayerisEnd(false);
	player->setPlayerIscollde(false);
}

void playerJump::exit(player * player)
{
}

