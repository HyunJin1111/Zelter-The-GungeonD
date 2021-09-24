#pragma once
#include "state.h"

class niflheim;

class niflheimIdle : public state
{

public :
	virtual state* inputHandle(niflheim* niflheim);
	virtual void update(niflheim* niflheim);
	virtual void enter(niflheim* niflheim);
	virtual void exit(niflheim* niflheim);
	virtual void render(niflheim* niflheim);
};