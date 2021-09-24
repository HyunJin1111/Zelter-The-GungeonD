#pragma once
#include "ammocondaState.h"
#include "ammoconda.h"

class ammocondaAttack1 : public ammocondaState
{
private:
	//상태변환 카운트
	int _changeCount;
	//이미지 프레임용
	int _count;
	//앵글값 카운트
	int _angleCount;
	//공격용 랜덤값
	int _attackRand;
public:

	virtual ammocondaState* InputHandle(ammoconda* ammoconda);
	virtual void enter(ammoconda* ammoconda);
	virtual void update(ammoconda* ammoconda);
	virtual void render(ammoconda* ammoconda);
	virtual void exit(ammoconda* ammoconda);

	void attack(ammoconda* ammoconda, int bodyNum);
};

