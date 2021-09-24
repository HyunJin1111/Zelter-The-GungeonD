#include "stdafx.h"
#include "ammocondaDeath.h"

ammocondaState * ammocondaDeath::InputHandle(ammoconda * ammoconda)
{
	

	return nullptr;
}

void ammocondaDeath::enter(ammoconda * ammoconda)
{
	ammoconda->getAmmoconda(0).currentFrameY = 0;
	ammoconda->getAmmoconda(0).img = IMAGEMANAGER->findImage("ammocondaHead");
	for (int i = 1; i < AMMOCONDAMAX; i++)
	{
		ammoconda->getAmmoconda(i).isAttack = false;
		
	}
	_alphaNum = 1;
	SOUNDMANAGER->stop("ammocondaBGM");
}

void ammocondaDeath::update(ammoconda * ammoconda)
{
	_randomEffect = RND->getFromIntTo(0, 100);

	if (_randomEffect % 13 == 0)
	{
		produceEffect(ammoconda);
	}


	if (_vBoom.size() != 0) playEffect(ammoconda);

	_alphaNum -= 0.005f;
}

void ammocondaDeath::render(ammoconda * ammoconda)
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i].img->frameRender2(_vBoom[i].x, _vBoom[i].y, _vBoom[i].effectFrameX, 0);
	}
	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		ammoconda->getAmmoconda(i).img->setAlpha(_alphaNum);
	}

}

void ammocondaDeath::exit(ammoconda * ammoconda)
{
}

void ammocondaDeath::produceEffect(ammoconda * ammoconda)
{
	//5개 이상 이펙트가 있으면 생략, 아니면 이펙트 계속 랜덤위치(보스 이미지 내부)에 생성해줌
	if (_vBoom.size() <= 5)
	{
		tagBoom boom;
		boom.img = IMAGEMANAGER->findImage("boom");
		boom.effectFrameX = 0;
		boom.x = RND->getFromFloatTo(ammoconda->getAmmoconda(0).rc.left, ammoconda->getAmmoconda(0).rc.right);
		boom.y = RND->getFromFloatTo(ammoconda->getAmmoconda(0).rc.top, ammoconda->getAmmoconda(0).rc.bottom);
		boom.playeEffectEnd = false;

		_vBoom.push_back(boom);
	}
}

void ammocondaDeath::playEffect(ammoconda * ammoconda)
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

