#pragma once
#include "tileNode.h"
#include "gameNode.h"

class ammocondaMap : public gameNode
{
private:
	tagTile _tile[TILEX*TILEY];
	DWORD _attribute[TILEX*TILEY];
	POINT _mapMouse;

	int _pos[2];


public:
	ammocondaMap() {};
	~ammocondaMap() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void load();

	tagTile* getTile() { return _tile; }
	//타일 속성에 대한 접근자도 만들어줘야 플레이어 객체랑 에너미 객체랑 연산 가능
	DWORD*  getTileAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

