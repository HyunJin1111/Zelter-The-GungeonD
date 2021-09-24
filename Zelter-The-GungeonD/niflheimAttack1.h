#pragma once
#include "state.h"
#include <vector>

class niflheim;

class niflheimAttack1 : public state
{
	vector<POINT>		_vStartPoint;
	vector<POINT>		_vEndPoint;

public:
	virtual state* inputHandle(niflheim* niflheim);
	virtual void update(niflheim* niflheim);
	virtual void enter(niflheim* niflheim);
	virtual void exit(niflheim* niflheim);
	virtual void render(niflheim* niflheim);
};

