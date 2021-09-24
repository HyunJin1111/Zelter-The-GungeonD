#pragma once
#include "ammocondaState.h"
#include "ammoconda.h"
#include <vector>

struct tagBoom
{
	image* img;
	float x, y;
	int effectFrameX;
	bool playeEffectEnd;
};

class ammocondaDeath : public ammocondaState
{
private:
	int _count;
	int rand;
	vector<tagBoom> _vBoom;
	int _effectFrameCount;
	int _playEffectNum;
	int _randomEffect;
	int	_countEffect;

	float _alphaNum;

public:
	virtual ammocondaState* InputHandle(ammoconda* ammoconda);
	virtual void enter(ammoconda* ammoconda);
	virtual void update(ammoconda* ammoconda);
	virtual void render(ammoconda* ammoconda);
	virtual void exit(ammoconda* ammoconda);

	void produceEffect(ammoconda* ammoconda);
	void playEffect(ammoconda* ammoconda);
};

