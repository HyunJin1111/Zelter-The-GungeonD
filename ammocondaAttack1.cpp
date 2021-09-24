#include "stdafx.h"
#include "ammocondaAttack1.h"
#include "ammocondaAttack2.h"
#include "ammocondaIdle.h"
#include "ammocondaRecovery.h"
#include "player.h"
#include "ammocondaDeath.h"

ammocondaState * ammocondaAttack1::InputHandle(ammoconda * ammoconda)
{
	int rand1 = RND->getFromIntTo(0, 2);
	int rand2 = RND->getFromIntTo(0, 3);
	//카운트 증가에따른 상태변환
	if (_changeCount >= 300)
	{
		switch (ammoconda->getIsPotCreate() ? rand2 : rand1)
		{
		case 0:
			return new ammocondaIdle();
			break;
		case 1:
			return new ammocondaAttack2();
			break;
		case 2:
			return new ammocondaRecovery();
			break;
		}
	}
	if (ammoconda->getCurrentHp() <= 3)
	{
		return new ammocondaDeath();
	}
	return nullptr;
}

void ammocondaAttack1::enter(ammoconda * ammoconda)
{
	SOUNDMANAGER->addSound("아모콘다공격1", "sound/아모콘다공격1.wav", false, false);

	_changeCount = 0;
	_angleCount = 0;
	ammoconda->getAmmoconda(0).currentFrameY = 0;
	for (int i = 1; i < AMMOCONDAMAX; i++)
	{
		ammoconda->getAmmoconda(i).isAttack = false;
		ammoconda->getAmmoconda(i).currentFrameX = 0;
	}
}

void ammocondaAttack1::update(ammoconda * ammoconda)
{
	//상태변환, 앵글값, 이미지에 대한 카운트 증가
	_changeCount++;
	_angleCount++;
	_count++;

	ammoconda->bossMove(_angleCount, 50, "ammocondaHead");

	_attackRand = RND->getFromIntTo(1, 100);

	//1 ~100까지의 랜덤값 중 몸통의 인덱스와 일치하면 isAttack라는 bool값 true
	if (_attackRand < AMMOCONDAMAX - 1) ammoconda->getAmmoconda(_attackRand + 1).isAttack = true;
	//각 몸통의 isAttack이라는 bool값 이 true면 공격 실행
	for (int i = 1; i < AMMOCONDAMAX; i++)
	{
		if (!ammoconda->getAmmoconda(i).isAttack) continue;
		attack(ammoconda, i);
	}
}

void ammocondaAttack1::render(ammoconda * ammoconda)
{
}

void ammocondaAttack1::exit(ammoconda * ammoconda)
{
}

void ammocondaAttack1::attack(ammoconda* ammoconda, int bodyNum)
{
	ammoconda->getAmmoconda(bodyNum).count++;

	//프레임 변환
	if (ammoconda->getAmmoconda(bodyNum).count % 20 == 0)
	{
		ammoconda->getAmmoconda(bodyNum).currentFrameX++;
		//총알 발사(이미지 프레임이 일치할 경우)
		if (ammoconda->getAmmoconda(bodyNum).currentFrameX == 3)
		{
			SOUNDMANAGER->play("아모콘다공격1");
			ammoconda->getBAmmocondaBullet()->bulletFire1(ammoconda->getAmmoconda(bodyNum).x, ammoconda->getAmmoconda(bodyNum).y, ammoconda->getPlayer()->getPlayer().x, ammoconda->getPlayer()->getPlayer().y);
		}
		//프레임 예외처리
		if (ammoconda->getAmmoconda(bodyNum).currentFrameX >= ammoconda->getAmmoconda(bodyNum).img->getMaxFrameX())
		{
			ammoconda->getAmmoconda(bodyNum).currentFrameX = 0;
			ammoconda->getAmmoconda(bodyNum).isAttack = false;
		}
	}
}

