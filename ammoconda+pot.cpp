#include "stdafx.h"
#include "ammoconda.h"
#include "player.h"


void ammoconda::setPot(int x, int y)
{
	IMAGEMANAGER->addFrameImage("potIdle", L"ammoconda/항아리Idle_40_40_4.png", 4, 1);
	IMAGEMANAGER->addFrameImage("potAttack", L"ammoconda/항아리Attack_40_40_2.png", 2, 1);
	IMAGEMANAGER->addFrameImage("potDeath", L"ammoconda/항아리Death_40_40_2.png", 2, 1);

	_pot.x = x;
	_pot.y = y;
	_pot.img = IMAGEMANAGER->findImage("potIdle");
	_pot.width = 40;
	_pot.height = 40;
	_pot.isAttack = false;
	_pot.count = 0;
	_pot.attackCount = 0;
	_pot.rc = RectMakeCenter(_pot.x, _pot.y, _pot.width, _pot.height);
	_pot.currentHp = _pot.maxHp = 50;
	_pot.currentFrameX = 0;
	_pot.state = POT_IDLE;
}
void ammoconda::potState()
{

	_pot.count++;
	_pot.attackCount++;
	if (_pot.count % 10 == 0)
	{
		_pot.currentFrameX++;
		if (_pot.state == POT_IDLE)
		{
			_pot.img = IMAGEMANAGER->findImage("potIdle");
			if (_pot.currentFrameX >= _pot.img->getMaxFrameX());
			{
				_pot.currentFrameX = 0;
			}
		}
		if (_pot.state == POT_ATTACK)
		{
			_pot.img = IMAGEMANAGER->findImage("potAttack");
			if (_pot.currentFrameX >= _pot.img->getMaxFrameX())
			{
				_ammocondaBullet->bulletFirePot(_pot.x, _pot.y, _player->getPlayer().x, _player->getPlayer().y);
				_pot.state = POT_IDLE;
				_pot.currentFrameX = 0;
			}
		}
		if (_pot.state == POT_DEATH)
		{
			_pot.img = IMAGEMANAGER->findImage("potDeath");
			if (_pot.currentFrameX >= _pot.img->getMaxFrameX())
			{
				_isPotCreate = false;
			}
		}
		_pot.count = 0;
	}

}
void ammoconda::potMove()
{
	potState();
	//렉트 업데이트
	if (_pot.attackCount % 200 == 0)
	{
		_pot.state = POT_ATTACK;
		_pot.currentFrameX = 0;
		_pot.attackCount = 0;
	}
	_pot.rc = RectMakeCenter(_pot.x, _pot.y, _pot.width, _pot.height);

}

void ammoconda::potRender()
{
	//항아리 렌더
	_pot.img->frameRender2(_pot.rc.left, _pot.rc.top, _pot.currentFrameX, 0);
	//항아리 렉텡글
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDER->DrawRectangle(_pot.rc, D2DRenderer::DefaultBrush::White);
	}

}


