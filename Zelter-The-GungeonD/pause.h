#pragma once
#include "gameNode.h"
struct tagButton
{
	RECT rc;
	image* img;
	float x, y;

};
class pause :
	public gameNode
{
};

