#pragma once
#include "gameNode.h"
#include "state.h"

#include "progressBar.h"
#include "niflheimBullet.h"

#include "playerBullet.h"

class player;

struct tagNiflheim
{
	image*	img;				//니플헤임이미지
	RECT	rc;					//히트박스
	float	x, y;				//좌표
	float	currentHP, maxHP;	//현재hp, 최대hp
	int		direction;			//방향
	int		inPattern;			//현재공격패턴
	int		outPattern;			//이정공격패턴
	bool	isDie;				//공략되었나

	niflheimIcePillar*	icePillar;	//얼음벽, 기본총알
	niflheimIceSpear*	iceSpear;	//얼음창
	niflheimIcicle*		iceicle;	//고드름
	progressBar*		progressBar;
};
enum DIRECTION
{
	RIGHT,
	LEFT
};
enum NIFLHEIMPATTERN
{
	ICICLE,
	ICESPEAR,
};
class niflheim : public gameNode
{
	player* _player;

	state*	_state;

	tagNiflheim	_niflheim;

	int _bulletFireCount;
	bool _invincibility;
	float _timeCount;
	float _timeCountEnd;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void inPutHandle();
	void hitNifleheim();

	void bulletUpdate();
	void bulletRender();

	void imageAdd();

	void linkPlayer(player* player) { _player = player; }
	player* getPlayer() { return _player; }

	tagNiflheim getNiflheim() { return _niflheim; }
	void setImg(image* img) { _niflheim.img = img; }

	void setX(float x) { _niflheim.x = x; }
	void setY(float y) { _niflheim.y = y; }
};

