#include "stdafx.h"
#include "playerAttack.h"
#include "playerStateIdle.h"
#include "playerRun.h"
#include "playerRoll.h"
#include "playerDie.h"
#include "playerDash.h"
#include "playerFall.h"

playerState * playerAttack::inputHandle(player * player)
{

		

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (player->getPlayerGuntype() == GRENADE)
			{
				player->getPlayerBullet()->fire(player->getPlayerGunX(), player->getPlayerGunY(),
					GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 20.0f, player->getPlayerGuntype(), _pressPower);
				SOUNDMANAGER->play("플레이어발사4효과음");
			}

			return new playerStateIdle();
		}
	
		if (player->getPlayer().isDunGreed)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('A')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('D')) return new playerRun();
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerDash;
			if (!player->getPlayer().isCollide)return new playerFall;
		}
		else
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('A')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('D')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('W')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('S')) return new playerRun();
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll();
		}

		if (player->getPlayer().currentHP <= 0)
		{player->setPlayerisDeath(true);
			return new playerDie();
		}
	return nullptr;
}

void playerAttack::update(player * player)
{
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();

	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	if (player->getPlayer().isDunGreed)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setPlayerX(player->getPlayer().x + player->getPlayer().speed*2);
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setPlayerX(player->getPlayer().x - player->getPlayer().speed*2);
		}
		switch (player->getPlayer().direction)
		{

		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
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
	


	if (player->getPlayerGuntype() == FLAMETHROWER)
	{
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(), 0);
	}

	
	_pressTime++;
	if (_pressTime % 5 == 0)
	{
		if (player->getPlayerGuntype() == GRENADE)_pressPower += 0.5;
		
	}


	_count++;
	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);

		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
			player->setPlayerisEnd(true);
			_count = 0;
		}
	}
	if (player->getPlayer().isDunGreed)
	{
		if (!player->getPlayer().isCollide)
		{
			_jumpPower -= _gravity;

			player->setPlayerY(player->getPlayer().y - _jumpPower);
		}
	}
}
	
void playerAttack::enter(player * player)
{
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	_pressPower = 0;
	SOUNDMANAGER->addSound("플레이어발사1효과음", "sound/플레이어발사1.wav", false, false);
	SOUNDMANAGER->addSound("플레이어발사2효과음", "sound/플레이어발사2.wav", false, false);
	SOUNDMANAGER->addSound("플레이어발사3효과음", "sound/플레이어발사3.wav", false, false);
	SOUNDMANAGER->addSound("플레이어발사4효과음", "sound/플레이어발사4.wav", false, false);
	SOUNDMANAGER->addSound("플레이어발사5효과음", "sound/플레이어발사5.wav", false, false);
	switch (player->getPlayerGuntype())
	{
	case NORMAL:

		player->getPlayerBullet()->fire(player->getPlayerGunX(), player->getPlayerGunY(),
			GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 10, player->getPlayerGuntype(), 0);
		SOUNDMANAGER->play("플레이어발사1효과음");
		break;
	case SHOTGUN:

		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(), 0);
		SOUNDMANAGER->play("플레이어발사2효과음");
		break;
	case HOMING:

		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 10, player->getPlayerGuntype(), 0);
		SOUNDMANAGER->play("플레이어발사3효과음");
		break;

	case FLAMETHROWER:
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(), 0);
		SOUNDMANAGER->play("플레이어발사5효과음");
		break;
	}

	if (player->getPlayer().isDunGreed)
	{
		if (!player->getPlayer().isCollide)
		{
			_jumpPower = 0.0f;
			_gravity = 0.4f;
		}
	}
}

void playerAttack::exit(player * player)
{
}