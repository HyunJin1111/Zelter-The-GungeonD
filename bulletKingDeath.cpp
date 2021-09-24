#include "stdafx.h"
#include "bulletKingDeath.h"

bulletKingState * bulletKingDeath::InputHandle(bulletKing * bulletKing)
{
	return nullptr;
}

void bulletKingDeath::enter(bulletKing * bulletKing)
{
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingDeath"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);

	_count = 0;
	SOUNDMANAGER->stop("bulletKingBGM");
}

void bulletKingDeath::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 10 == 0)
	{
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		bulletKing->setBulletKingChairCurrentFrameX(1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
		_count = 0;
	}
	_randomEffect = RND->getFromIntTo(0, 100);

	if (_randomEffect % 13 == 0)
	{
		produceEffect(bulletKing);
	}


	if (_vBoom.size() != 0) playEffect(bulletKing);
}

void bulletKingDeath::render(bulletKing * bulletKing)
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i].img->frameRender2(_vBoom[i].x, _vBoom[i].y, _vBoom[i].effectFrameX, 0);
	}
}

void bulletKingDeath::exit(bulletKing * bulletKing)
{
}

void bulletKingDeath::produceEffect(bulletKing * bulletKing)
{
	//5개 이상 이펙트가 있으면 생략, 아니면 이펙트 계속 랜덤위치(보스 이미지 내부)에 생성해줌
	if (_vBoom.size() <= 5)
	{
		tagBoom boom;
		boom.img = IMAGEMANAGER->findImage("boom");
		boom.effectFrameX = 0;
		boom.x = RND->getFromFloatTo(bulletKing->getBulletKingChair().rc.left, bulletKing->getBulletKingChair().rc.right);
		boom.y = RND->getFromFloatTo(bulletKing->getBulletKingChair().rc.top, bulletKing->getBulletKingChair().rc.bottom);
		boom.playeEffectEnd = false;

		_vBoom.push_back(boom);
	}
}

void bulletKingDeath::playEffect(bulletKing * bulletKing)
{
	_effectFrameCount++;

	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (_effectFrameCount % 10 == 0)
		{
			//이펙트 프레임 재생
			_vBoom[i].effectFrameX++;
			if (_vBoom[i].effectFrameX >= _vBoom[i].img->getMaxFrameX())
			{
				_vBoom[i].playeEffectEnd = true;
			}

			//재생이 끝나면 해당 이펙트 지워줌
			if (_vBoom[i].playeEffectEnd)
			{
				_vBoom.erase(_vBoom.begin() + i);

				_countEffect++;
			}

			_effectFrameCount = 0;
		}
	}

	if (_countEffect >= 15) SCENEMANAGER->changeScene("openWorld");
}
