#pragma once
#include "bulletKingState.h"
#include "bulletKing.h"
#include "bulletKingHit.h"
#include "bulletKingDeath.h"
#include "bulletKingAttack1.h"
#include "bulletKingAttack2.h"
#include "bulletKingAttack3.h"

class bulletKingIdle : public bulletKingState
{
private:
	//이미지 프레임용
	int _count;
	
	//이동 관련
	int _randCount;
	int _rand;

	//보스 상태변경 관련
	int _changeCount;
	int _changeRand;
public:
	virtual bulletKingState* InputHandle(bulletKing* bulletKing);
	virtual void enter(bulletKing* bulletKing);
	virtual void update(bulletKing* bulletKing);
	virtual void render(bulletKing* bulletKing);
	virtual void exit(bulletKing* bulletKing);

};

