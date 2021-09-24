#include "stdafx.h"
#include "playerDash.h"
#include "player.h"
#include "playerHit.h"
#include "playerDie.h"
#include "playerAttack.h"
#include "playerRun.h"
#include "playerStateIdle.h"
#include "playerFall.h"

playerState * playerDash::inputHandle(player * player)
{
	if (player->getPlayer().isEnd && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D') ||
		KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))
	{
		return new playerRun;
	}

	if (player->getPlayer().isEnd) return new playerFall;
	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}
	return nullptr;
}

void playerDash::update(player * player)
{
	switch (player->getPlayer().direction)
	{
	case 0:
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 1:
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 2:
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 3:
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 4:
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed*10);
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed*10);
		player->setPlayerisEnd(true);
		break;
	case 5:
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 10);
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 6:
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 10);
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	case 7:
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 10);
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 10);
		player->setPlayerisEnd(true);
		break;
	}
}

void playerDash::enter(player * player)
{
	switch (player->getPlayer().direction)
	{
	case 0:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
		break;
	case 1:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
		break;
	case 2:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
		break;
	case 3:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
		break;
	case 4:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
		break;
	case 5:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
		break;
	case 6:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
		break;
	case 7:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
		break;
	}

	player->setPlayerisEnd(false);
	player->setIsjump(false);
	player->setPlayerisEnd(false);
	_gravity = 0.f;
	return;
	
}

void playerDash::exit(player * player)
{
}
