#pragma once
#include "gameNode.h"
#include <vector>

struct tagEggNyangBullet
{
	image*	image;				//총알 이미지
	RECT	rc;					//총알 렉트
	//float	left, top;			//총알 레트프 탑
	float	x, y;				//총알 중점좌표
	float	angle;				//총알 회전 앵글
	float	width, height;		//총알 폭, 높이 (렉트)
	float	radiusX;				//총알 반지름(빗변의 반)
	float	radiusY;
	float	speed;				//총알 스피드
	int		frameCount;
	int		currentFrameX;
	int		currentFrameY;
};

#define EGGNYANGBULLETMAX 100
class eggNyangBullet : public gameNode
{
	vector<tagEggNyangBullet>	_vBullet;

	int icePillar1, icePillar2;

public :
	virtual HRESULT init();
	virtual void release(int index);
	virtual void update();
	virtual void render();

	void bulletFire(float x, float y, int bulletCount);
	void bulletMove();

	vector<tagEggNyangBullet> getEggNyangVBullet() { return _vBullet; }
};

//========================================

#define MAXLAZESIZE 40
class eggNyangLazer : public gameNode
{
	vector<tagEggNyangBullet>	_vLazer;

	int _lazerTime;				//레이저 준비 시간, 레이저 발사 시간 카운트용
	bool _lazerFire;			//레이저 발사 됐는지

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void lazerReady(float x, float y, int direction);
	void lazerFire();
	void lazerMove();

	vector<tagEggNyangBullet> getEggNyangVLazer() { return _vLazer; }
};

//==========================================

#define MAXSOWRD 5
class eggNyangSword : public gameNode
{
	vector<tagEggNyangBullet>	_vSword;

public :
	virtual HRESULT init();
	virtual void release(int index);
	virtual void update();
	virtual void render();

	void setSword(float targetX, float targetY);
	void moveSword(float targetX, float targetY, bool fire);

	vector<tagEggNyangBullet> getEggNyangVSword() { return _vSword; }
};
