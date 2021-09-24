#pragma once
#include "gameNode.h"

class niflheim;

class state : public gameNode
{

protected:
	niflheim*	_niflheim;

	string	_currentStateName;					//상태이름

	int		_count;								//프레임카운트
	int		_currentFrameX, _currentFrameY;		//프레임 배열 x,y카운트
	int		_randomPatternCount;				//랜덤 패턴 카운트
	bool	_stateEnd;							//상태가 끝났음
	float	_angle;								//이동할시 앵글
	bool	_isEnter;							//이동하라는 신호 함수

public :
	virtual state* inputHandle(niflheim* eggNyang) = 0;
	virtual void update(niflheim* eggNyang) = 0;
	virtual void enter(niflheim* eggNyang) = 0;
	virtual void exit(niflheim* eggNyang) = 0;
	virtual void render(niflheim* eggNyang) = 0;

	string getStateNamge() { return _currentStateName; }
	bool getEnter() { return _isEnter; }
};

