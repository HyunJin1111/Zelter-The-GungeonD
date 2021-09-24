 #include "stdafx.h"
#include "eggNyangDie.h"

#include "eggNyang.h"

eggNyangStateBase * eggNyangDie::inputHandle(eggNyang * eggNyang)
{
	return nullptr;
}

void eggNyangDie::update(eggNyang * eggNyang)
{
	_count++;

	if (_count % 10 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= eggNyang->getEggNyang().img->getMaxFrameX()) _currentFrameX = 0;
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0) _currentFrameX = 1;
		}
	}

	_randomEffect = RND->getFromIntTo(0, 100);


	if (_randomEffect % 13 == 0)
	{
		produceEffect(eggNyang);
	}

	

	if (_vBoom.size() != 0) playEffect(eggNyang);

}

void eggNyangDie::enter(eggNyang * eggNyang)
{
	eggNyang->setImage(IMAGEMANAGER->findImage("eggNyangDie"));
	_count = 0;
	_currentFrameY = eggNyang->getEggNyang().direction;
	if (_currentFrameY == 0) _currentFrameX = 0;
	else _currentFrameX = 1;
	
	_playEffectNum = 0;
	_countEffect = 0;
}

void eggNyangDie::render(eggNyang * eggNyang)
{
	eggNyang->getEggNyang().img->frameRender2(eggNyang->getEggNyang().x, eggNyang->getEggNyang().y, _currentFrameX, _currentFrameY);


	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i].img->frameRender2(_vBoom[i].x, _vBoom[i].y, _vBoom[i].effectFrameX, 0);
	}
}

void eggNyangDie::exit(eggNyang * eggNyang)
{
}

void eggNyangDie::produceEffect(eggNyang * eggNyang)
{
	//5개 이상 이펙트가 있으면 생략, 아니면 이펙트 계속 랜덤위치(보스 이미지 내부)에 생성해줌
	if (_vBoom.size() <= MAXEFFECT)
	{
		tagBoom boom;
		boom.img = IMAGEMANAGER->findImage("boom");
		boom.effectFrameX = 0;
		boom.x = RND->getFromFloatTo(eggNyang->getEggNyang().rc.left, eggNyang->getEggNyang().rc.right);
		boom.y = RND->getFromFloatTo(eggNyang->getEggNyang().rc.top, eggNyang->getEggNyang().rc.bottom);
		boom.playeEffectEnd = false;

		_vBoom.push_back(boom);
	}
}

void eggNyangDie::playEffect(eggNyang * eggNyang)
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

	if (_countEffect >= 15)
	{
		SOUNDMANAGER->stop("eggNyangBGM");
		SCENEMANAGER->changeScene("openWorld");
	}
}
