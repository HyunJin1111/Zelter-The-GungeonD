#include "stdafx.h"
#include "playerStateIdle.h"

#include "player.h"
#include "playerRoll.h" //구르기
#include "playerJump.h" // 점프
#include "playerDonwJump.h"
#include "playerRun.h" // 달리기
#include "playerAttack.h"
#include "playerHit.h"
#include "playerDie.h"
#include "playerDash.h"
#include "playerFall.h"


playerState * playerStateIdle::inputHandle(player * player)
{
	if ((player->getPlayer().x < WINSIZEX - CAMERAMANAGER->getX()|| player->getPlayer().x>0 - CAMERAMANAGER->getX() ) && (player->getPlayer().y < WINSIZEY - CAMERAMANAGER->getY() || player->getPlayer().y>0 - CAMERAMANAGER->getY()))
	{
		if (player->getPlayer().isDunGreed == true)
		{
			if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new playerDonwJump();
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new playerJump();
			if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D'))return new playerRun();
			if (!player->getPlayer().isEnd&&KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerDash;
			if (!player->getPlayer().isCollide) return new playerFall;
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D') ||
				KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S'))
			{
				return new playerRun();
			}
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack();

	if (player->getPlayer().isHit == true) return new playerHit();

	if (player->getPlayer().currentHP <= 0)
	{
		player->setPlayerisDeath(true);
		return new playerDie();
	}
	return nullptr;
}

void playerStateIdle::update(player * player)
{
	if (player->getPlayer().isDunGreed)
	{
		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		case 2:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 3:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		case 4:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		case 5:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 6:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 7:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		}
	}


	else
	{
		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		case 2:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_back_idle"));
			break;
		case 3:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_idle"));
			break;
		case 4:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left-up_idle"));
			break;
		case 5:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right-up_idle"));
			break;
		case 6:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 7:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		}
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

void playerStateIdle::enter(player * player)
{
	switch (player->getPlayer().direction)
	{
	case 0:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
		break;
	case 1:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
		break;
	case 2:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_back_idle"));
		break;
	case 3:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_idle"));
		break;
	case 4:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left-up_idle"));
		break;
	case 5:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right-up_idle"));
		break;
	case 6:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
		break;
	case 7:
		player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
		break;
	}
}

void playerStateIdle::exit(player * player)
{
}