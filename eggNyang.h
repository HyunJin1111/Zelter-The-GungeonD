#pragma once
#include "gameNode.h"

#include "progressBar.h"
#include "eggNyangStateBase.h"
#include "eggNyangBullet.h"

#include "playerBullet.h"

class player;

struct tagEggNyang
{
	image*	img;						//이미지
	RECT	rc;							//보스 렉트 (히트박스)
	float	x, y;						//x,y좌표
	int		currentHp, maxHp;			//체력
	int		direction;					//방향 (왼쪽 오른쪽)
	bool	isDie;
	float	speed;						//스피드
	int		inPattern;					//이전 공격패턴 기록 (중복된 패턴 나오지 않도록)
	int		outPattern;

	eggNyangBullet*		bullet;
	eggNyangLazer*		lazer;
	eggNyangSword*		sword;
	progressBar*		progressBar;
};
enum EGGNYANGPATTERN
{
	BULLET = 1,
	LAZER,
	SWORD
};
class eggNyang : public gameNode
{
	player*	_player;

	eggNyangStateBase* _eggNyangState;

	tagEggNyang _eggNyang;

	int _bulletFireCount;
	bool _isFire;

	bool _invincibility;
	float _timeCount;
	float _timeCountEnd;

	

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void inPutHandle();

	void hitEggNyang();

	void imageAdd();
	void move();
	void attackPatternSign();

	void linkPlayer(player* player) { _player = player; }
	player* getPlayer() { return _player; }

	tagEggNyang getEggNyang() { return _eggNyang; }
	void setImage(image* eggNyangImage) { _eggNyang.img = eggNyangImage; }

	void setEggNyangX(float x) { _eggNyang.x = x; }
	void setEggNyangY(float y) { _eggNyang.y = y; }
	int getBulletFireCount() { return _bulletFireCount; }
	void setBulletFireCount(int bulletCount) { _bulletFireCount = bulletCount; }
};

