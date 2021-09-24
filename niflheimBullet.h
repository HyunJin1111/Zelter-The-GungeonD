#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image*	img;				//총알 이미지
	RECT	rc;					//총알 렉트
	SHAPE	rotateCollsion;		//회전 충돌 체크용 shape생성
	float	x, y;				//총알 중점좌표
	float	angle;				//총알 회전 앵글
	float	width, height;		//총알 폭, 높이 (렉트)
	float	radiusX;			//총알 반지름(빗변의 반)
	float	radiusY;
	float	speed;				//총알 스피드
	int		frameCount;
	int		currentFrameX;
	int		currentFrameY;
	int		currentHP, maxHP;	//(icePillar) 체력
	bool	ready;				//생성되는 프레임이 끝났는가..
	bool	destroy;			//파괴되었는가
	bool	hp0;
};

#define MAXICEPILLAR 4
#define MAXICEBULLET 40
class niflheimIcePillar : public gameNode
{
	vector<tagBullet>			_vIcePillar;	//얼음기둥
	vector<tagBullet>			_vBullet;		//기둥에서 발사되는 총알

	int icePillar1, icePillar2;

public :
	virtual HRESULT init();
	virtual void release(int index);
	void dieRelease(int index);
	virtual void update(float niflheimX, float niflheimY);
	virtual void render();

	void seticePillar(float niflheimX, float niflheimY);
	void icePillarMove(float niflheimX, float niflheimY);

	void fireBullet1(float x, float y, int icePillar);
	void fireBullet2(float x, float y, int icePillar);
	void bulletMove();
	void releaseBullet(int index);
	void bulletRender();

	vector<tagBullet> getVIcePillar() { return _vIcePillar; }
	void setCurrentHP(int index, int hp) { _vIcePillar[index].currentHP = hp; }

	vector<tagBullet> getVbullet() { return _vBullet; }
};

#define MAXICESPEAR 2
class niflheimIceSpear : public gameNode
{
	vector <tagBullet>		_vIceSpear;

public :
	virtual HRESULT init();
	virtual void release(int index);
	virtual void update();
	virtual void render();

	void iceSpearFire(float x, float y);
	void iceSpearMove();

	vector<tagBullet> getVIceSpear() { return _vIceSpear; }
};

#define MAXICICLE 12
class niflheimIcicle : public gameNode
{
	vector<tagBullet>		_vIcicle;

	bool	_isSceond;

public:
	virtual HRESULT init();
	virtual void release(int index);
	virtual void update();
	virtual void render();

	void firstIcicleFire();
	void sceondIcicleFire();
	void icicleMove();

	vector<tagBullet> getVIcicle() { return _vIcicle; }
};