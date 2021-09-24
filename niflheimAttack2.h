#pragma once
#include "state.h"
#include "player.h"

class niflheim;

class niflheimAttack2 :public state
{
	POINT startLine, endLine;

public:
	virtual state* inputHandle(niflheim* niflheim);
	virtual void update(niflheim* niflheim);
	virtual void enter(niflheim* niflheim);
	virtual void exit(niflheim* niflheim);
	virtual void render(niflheim* nniflheim);
};

