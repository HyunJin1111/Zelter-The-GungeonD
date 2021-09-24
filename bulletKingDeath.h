#pragma once
#include "bulletKingState.h"
#include "bulletKing.h"
#include <vector>

struct tagBoom
{
	image* img;					
	float x, y;						
	int effectFrameX;				
	bool playeEffectEnd;			
};


class bulletKingDeath : public bulletKingState
{
private:
	int _count;
	int rand;
	vector<tagBoom> _vBoom;
	int _effectFrameCount;			
	int _playEffectNum;				
	int _randomEffect;			
	int	_countEffect;

public:
	virtual bulletKingState* InputHandle(bulletKing* bulletKing);
	virtual void enter(bulletKing* bulletKing);
	virtual void update(bulletKing* bulletKing);
	virtual void render(bulletKing* bulletKing);
	virtual void exit(bulletKing* bulletKing);

	void produceEffect(bulletKing* bulletKing);
	void playEffect(bulletKing* bulletKing);
};

