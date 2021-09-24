#pragma once
#include "eggNyangStateBase.h"

#define MAXEFFECT 5
class eggNyang;

struct tagBoom
{
	image* img;					//이미지
	float x, y;						//좌표
	int effectFrameX;				//이펙트 프레임
	bool playeEffectEnd;			//이펙트 재생이 끝났는지
};
class eggNyangDie : public eggNyangStateBase
{
	vector<tagBoom> _vBoom;

	int _effectFrameCount;			//이펙트 프레임
	int _playEffectNum;				//이펙트 재생된 횟수
	int _randomEffect;				//이펙트 랜덤생성 값
	int	_countEffect;
public :
	virtual eggNyangStateBase* inputHandle(eggNyang* eggNyang);
	virtual void update(eggNyang* eggNyang);
	virtual void enter(eggNyang* eggNyang);
	virtual void render(eggNyang* eggNyang);
	virtual void exit(eggNyang* eggNyang);

	void produceEffect(eggNyang* eggNyang);
	void playEffect(eggNyang* eggNyang);
};

