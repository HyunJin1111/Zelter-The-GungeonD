#include "stdafx.h"
#include "playerHit.h"
#include "playerRun.h"
#include "playerAttack.h"
#include "playerJump.h"
#include "playerRoll.h"
#include "playerStateIdle.h"
#include "playerDie.h"
#include "playerFall.h"


playerState * playerHit::inputHandle(player * player)
{
	if (player->getPlayer().isHit == false )return new playerStateIdle();
	
	if (player->getPlayer().isDunGreed)
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) return new playerStateIdle;
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))return new playerJump;
		if (!player->getPlayer().isCollide) return new playerFall;
	}
	else
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') ||
			KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) return new playerStateIdle;

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack;
	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}

	return nullptr;
}

void playerHit::update(player * player)
{
	if (player->getPlayer().isHit)
	{
		_blinkCount++;

		if (_blinkCount <= 10 )player->getPlayer().img->setAlpha(0);
		else
		{
			player->getPlayer().img->setAlpha(1);
			_blink++;
			_blinkCount = 0;
		}
		if (_blink >= 3)
		{
			player->setHit(false);
			player->getPlayer().img->setAlpha(1);
		}
	}
	
	if (player->getPlayer().isDunGreed)
	{
		if (KEYMANAGER->isStayKeyDown('D'))player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
		if (KEYMANAGER->isStayKeyDown('A'))player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);

		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		}
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
		}

		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		case 2:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_back_run"));
			break;
		case 3:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_run"));
			break;
		case 4:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left-up_run"));
			break;
		case 5:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right-up_run"));
			break;
		case 6:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 7:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		}
	}
}

void playerHit::enter(player * player)
{

}

void playerHit::exit(player * player)
{
}

