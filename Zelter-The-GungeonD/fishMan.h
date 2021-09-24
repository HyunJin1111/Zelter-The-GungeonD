#pragma once
#include "gameNode.h"
#include <vector>
#include "bulletKing.h"
#include "dialogue.h"
#include "inGameMap.h"

enum FISHMANDIRECTION
{
	FISHMAN_RIGHT,
	FISHMAN_LEFT
};
enum FISHMANSTATE
{
	FISHMAN_IDLE,
	FISHMAN_WALK,
	FISHMAN_RUN,
	FISHMAN_ATTACK,
	FISHMAN_DEATH,
};

struct tagFishMan
{
	image* img;							//피쉬맨 이미지
	RECT rc;							//피쉬맨 렉트
	float speed;						//피쉬맨 속도
	float angle;						//피쉬맨 각도(라디안)
	float x, y;							//피쉬맨 x, y
	int width, height;					//피쉬맨 가로 길이, 세로 길이
	int currentFrameX;					//피쉬맨 x축 현재 프레임
	int currentFrameY;					//피쉬맨 y축 현재 프레임
	int maxHp, currentHp;				//피쉬맨 최대 체력, 현재 체력
	int count;							//이미지 프레임 카운트
	int changeCount;					//상태변환용 카운트
	int direction;
	RECT tileIdx[2];
	FISHMANDIRECTION direction_img;
	FISHMANSTATE state;
	RECT _rcc[2];
	RECT _rcc2[3];
};


class fishMan : public gameNode
{
private:
	//다이얼로그
	dialogue* _dialogue;

	//피쉬맨 구조체
	tagFishMan _fishMan;

	//피쉬맨 벡터
	vector<tagFishMan> _vFishMan;
	vector<tagFishMan>::iterator _viFishMan;

	//테스트 플레이어
	bulletKing* _bulletKing;

	////타일관련
	inGameMap* _inGame;

	
public:
	fishMan();
	~fishMan();

	HRESULT init();
	void release();
	void update();
	void render();
	void setEnemy();
	void fishMove(float x, float y);
	void fishState();
	void tileCheck();

	tagFishMan getFishMan() { return _fishMan; }

	void linkOpenWorldMap(inGameMap* map) { _inGame = map; }

	vector<tagFishMan>& getVfishMan() { return _vFishMan; }
	vector<tagFishMan>::iterator& getVifishMan() { return _viFishMan; }
};

