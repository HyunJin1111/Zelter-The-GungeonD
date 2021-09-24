#pragma once
#include "tileNode.h"
#include "gameNode.h"


struct tagBossDoor
{
	image* img;		//보스 입장문 이미지
	RECT rc;		//보스 입장문 렉트
	float x, y;		//보스 입장문 위치	
};

class inGameMap : public gameNode
{
private:

	tagTile _tile[TILEX*TILEY];
	DWORD _attribute[TILEX*TILEY];
	POINT _mapMouse;

	int _pos[2];

	//보스 진입 구조체
	tagBossDoor _bossDoorRect[4];
public:
	inGameMap() {};
	~inGameMap() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void load();
	void setDoor();

	tagTile* getTile() { return _tile; }
	//타일 속성에 대한 접근자도 만들어줘야 플레이어 객체랑 에너미 객체랑 연산 가능
	DWORD*  getTileAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

	tagBossDoor getBossDoor(int index) { return _bossDoorRect[index]; }

};

