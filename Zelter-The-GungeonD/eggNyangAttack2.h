#pragma once
#include "eggNyangStateBase.h"
#include "player.h"

class eggNyang;

class eggNyangAttack2 : public eggNyangStateBase
{
	int _eggNyangPositionPattern;	//이동 포지션 설정 상좌, 상우, 중단, 하좌, 하우

public:
	virtual eggNyangStateBase* inputHandle(eggNyang* eggNyang);
	virtual void update(eggNyang* eggNyang);
	virtual void enter(eggNyang* eggNyang);
	virtual void render(eggNyang* eggNyang);
	virtual void exit(eggNyang* eggNyang);

	void movePosition(eggNyang* eggNyang, int eggNyangPositionPattern);
	void eggNyangMove(eggNyang* eggNyang, int eggNyangPositionPattern);
};

