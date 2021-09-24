#include "stdafx.h"
#include "bulletKingIdle.h"

bulletKingState * bulletKingIdle::InputHandle(bulletKing * bulletKing)
{
	//카운트 증가에따른 상태변환
	if (_changeCount >= 150)
	{
		_changeRand = RND->getFromIntTo(0, 3);

		switch (_changeRand)
		{
		case 0:
			return new bulletKingAttack1();
			break;
		case 1:
			return new bulletKingAttack2();
			break;
		case 2:
			return new bulletKingAttack3();
			break;
		}
	}
	if (bulletKing->getBulletKing().currentHp <= 3) return new bulletKingDeath();
	return nullptr;
}

void bulletKingIdle::enter(bulletKing * bulletKing)
{	
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingIdle"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);

	_count = _randCount = _changeCount = 0;
	_rand = RND->getFromFloatTo(0, PI2);
}

void bulletKingIdle::update(bulletKing * bulletKing)
{
	_count++;
	_randCount++;
	_changeCount++;
	//보스 이미지 프레임
	if (_count % 10 == 0)
	{
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
		_count = 0;
	}
	//보스 이동
	if (_randCount % 50 == 0) 
	{
		_rand = RND->getFromFloatTo(0, PI2);
		_randCount = 0;
	}
	bulletKing->getBulletKing().x += cosf(_rand) * bulletKing->getBulletKing().speed;
	bulletKing->getBulletKing().y += -sinf(_rand) * bulletKing->getBulletKing().speed;
	bulletKing->getBulletKingChair().x += cosf(_rand) * bulletKing->getBulletKingChair().speed;
	bulletKing->getBulletKingChair().y += -sinf(_rand) * bulletKing->getBulletKingChair().speed;
}

void bulletKingIdle::render(bulletKing * bulletKing)
{
}

void bulletKingIdle::exit(bulletKing * bulletKing)
{
}
