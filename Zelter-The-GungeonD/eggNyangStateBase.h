#pragma once
#include "gameNode.h"
#include <vector>

class eggNyang;


class eggNyangStateBase : public gameNode
{
	
protected:
	eggNyang*	_eggNyang;

	string	_stateName;							//상태이름

	int		_count;								//프레임카운트
	int		_currentFrameX, _currentFrameY;		//프레임 배열 x,y카운트
	int		_randomPatternCount;				//랜덤 패턴 카운트
	bool	_stateEnd;							//상태가 끝났음
	float	_angle;								//이동할시 앵글
	bool	_isMove;							//이동하라는 신호 함수

public:
	virtual eggNyangStateBase* inputHandle(eggNyang* eggNyang) = 0;
	virtual void update(eggNyang* eggNyang) = 0;
	virtual void enter(eggNyang* eggNyang) = 0;
	virtual void exit(eggNyang* eggNyang) = 0;
	virtual void render(eggNyang* eggNyang) = 0;

	string getStateName() { return _stateName; }
	float getAngle() { return _angle; }
	bool getIsMove() { return _isMove; }
};

