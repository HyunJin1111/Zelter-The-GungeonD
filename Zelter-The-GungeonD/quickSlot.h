#pragma once
#include "gameNode.h"

#define QUICKSLOTBASEMAX 5

struct tagQuickSlot
{
	RECT rc;
	image* img;
	image* gunimg;

	float x, y;
	bool isOn;
};
class quickSlot : public gameNode
{
private:
	tagQuickSlot _quickSlotFront;
	tagQuickSlot _quickSlotBack;
	tagQuickSlot _quickSlotBase[QUICKSLOTBASEMAX];
	
public:

	HRESULT init();

	void release();
	void update();
	void render();

	bool getQuickslotisOn(int index) { return _quickSlotBase[index].isOn; }

	void setQuickslotIsOn(int index, bool ison) { _quickSlotBase[index].isOn = ison; }
};

