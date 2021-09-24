#include "stdafx.h"
#include "playerFall.h"

#include "playerDie.h"
#include "playerAttack.h"
#include "playerDash.h"
#include "playerJump.h"
#include "playerStateIdle.h"
#include "playerHit.h"
#include "player.h"

playerState * playerFall::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerDash;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack();
	if (player->getPlayer().isCollide) return new playerStateIdle();

	if (player->getPlayer().isHit == true) return new playerHit();

	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}
	return nullptr;
}

void playerFall::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
	}

	_jumpPower -= _gravity;

	player->setPlayerY(player->getPlayer().y - _jumpPower);
	return;
}

void playerFall::enter(player * player)
{
	_jumpPower = 0.0f;
	_gravity = 0.4f;

	return;
}

void playerFall::exit(player * player)
{
}
