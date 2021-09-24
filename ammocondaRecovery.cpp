#include "stdafx.h"
#include "ammocondaRecovery.h"
#include "ammocondaAttack1.h"
#include "ammocondaAttack2.h"
#include "ammocondaIdle.h"
#include "ammocondaDeath.h"

ammocondaState * ammocondaRecovery::InputHandle(ammoconda * ammoconda)
{
	if (_isYum) _changeCount++;
	if(_changeCount >= 40) return new ammocondaIdle();
	if (ammoconda->getCurrentHp() <= 3)
	{
		return new ammocondaDeath();
	}
	return nullptr;
}

void ammocondaRecovery::enter(ammoconda * ammoconda)
{
	ammoconda->getAmmoconda(0).img = IMAGEMANAGER->findImage("ammocondaYum");
	_changeCount = 0;
	_angleCount = 0;
	_count = 0;
	_isYum = false;
	ammoconda->getAmmoconda(0).currentFrameY = 0;
	for (int i = 1; i < AMMOCONDAMAX; i++)
	{
		ammoconda->getAmmoconda(i).isAttack = false;
		ammoconda->getAmmoconda(i).currentFrameX = 0;
	}
}

void ammocondaRecovery::update(ammoconda * ammoconda)
{
	
	_angleCount++;
	_count++;
	RECT temp;
	if (!IntersectRect(&temp, &ammoconda->getAmmoconda(0).rc, &ammoconda->getPot().rc))
	{
		ammoconda->bossRecoveryMove(_angleCount, 100, "ammocondaHead", ammoconda->getAmmoconda(0).x, ammoconda->getAmmoconda(0).y, ammoconda->getPot().x, ammoconda->getPot().y);
	}
	else 
	{
		if (_count % 20 == 0)
		{
			ammoconda->getAmmoconda(0).img = IMAGEMANAGER->findImage("ammocondaYum");
			ammoconda->getAmmoconda(0).currentFrameY++;
			if (ammoconda->getAmmoconda(0).currentFrameY >= ammoconda->getAmmoconda(0).img->getMaxFrameY())
			{
				ammoconda->getAmmoconda(0).currentFrameY = 0;
				ammoconda->getPot().state = POT_DEATH;
				_isYum = true;
			}
		}
	}
}

void ammocondaRecovery::render(ammoconda * ammoconda)
{

}

void ammocondaRecovery::exit(ammoconda * ammoconda)
{

}
