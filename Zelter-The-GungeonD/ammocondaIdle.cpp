#include "stdafx.h"
#include "ammocondaIdle.h"
#include "ammocondaAttack1.h"
#include "ammocondaAttack2.h"
#include "ammocondaRecovery.h"
#include "ammocondaDeath.h"

ammocondaState * ammocondaIdle::InputHandle(ammoconda * ammoconda)
{
	int rand1 = RND->getFromIntTo(0, 2);
	int rand2 = RND->getFromIntTo(0, 3);
	//카운트 증가에따른 상태변환
	if (_changeCount >= 300)
	{
		switch (ammoconda->getIsPotCreate() ? rand2 : rand1)
		{
		case 0:
			return new ammocondaAttack1();
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

void ammocondaIdle::enter(ammoconda * ammoconda)
{
	ammoconda->getAmmoconda(0).currentFrameY = 0;
	ammoconda->getAmmoconda(0).img = IMAGEMANAGER->findImage("ammocondaHead");
	//상태변환, 앵글값에 대한 카운트 증가
	_changeCount = 0;
	_angleCount = 0;
	for (int i = 1; i < AMMOCONDAMAX; i++)
	{
		ammoconda->getAmmoconda(i).isAttack = false;
		ammoconda->getAmmoconda(i).currentFrameX = 0;
	}
	
}

void ammocondaIdle::update(ammoconda * ammoconda)
{
	_changeCount++;
	_angleCount++;

	ammoconda->bossMove(_angleCount, 30, "ammocondaHead");
}

void ammocondaIdle::render(ammoconda * ammoconda)
{
}

void ammocondaIdle::exit(ammoconda * ammoconda)
{
}
