#include "stdafx.h"
#include "playerDie.h"

playerState * playerDie::inputHandle(player * player)
{
	return nullptr;
}

void playerDie::update(player * player)
{
	_count++;

	if (_count % 10 == 0)
	{
		if(player->getPlayer().isDeath)player->setPlayerCurrentFrameX( player->getPlayer().currentFrameX + 1);

		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(player->getPlayer().img->getMaxFrameX()-1);
		_count = 0;
		}
	}
	return;
}

void playerDie::enter(player * player)
{
	player->setPlayerImage(IMAGEMANAGER->findImage("gunner_death"));
	player->setIsjump(false);
}

void playerDie::exit(player * player)
{
}

