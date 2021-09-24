#pragma once
#include "gameNode.h"
#include "bulletKingState.h"
#include "bulletKingIdle.h"
#include "bulletKingBullet.h"
#include "progressBar.h"
#include "playerBullet.h"

class player;

struct tagBulletKing
{
	image* img;							//ÃÑÅºÅ· ÀÌ¹ÌÁö

	RECT rc;							//ÃÑÅºÅ· ·ºÆ®
	float speed;						//ÃÑÅºÅ· ¼Óµµ
	float angle;						//ÃÑÅºÅ· °¢µµ(¶óµð¾È)
	float x, y;							//ÃÑÅºÅ· x, y
	int width, height;					//ÃÑÅºÅ³ °¡·Î ±æÀÌ, ¼¼·Î ±æÀÌ
	int currentFrameX;					//ÃÑÅºÅ· xÃà ÇöÀç ÇÁ·¹ÀÓ
	int maxHp, currentHp;				//ÃÑÅºÅ· ÃÖ´ë Ã¼·Â, ÇöÀç Ã¼·Â
	bool isAttack3;						//3¹ø¤Š ÆÐÅÏ ¹ß»ý ¿©ºÎ
};

class bulletKing : public gameNode
{
private:
	//ÃÑÅºÅ· º»Ã¼ ¹× ÀÇÀÚ ±¸Á¶Ã¼
	tagBulletKing _bulletKing;
	tagBulletKing _bulletKingChair;

	//Ã¼·Â
	progressBar* _hp;
	image* _bulletKing_hp;

	//ÃÑ¾Ë Å¬·¡½º
	bulletKingBullet* _bullet;

	//ÃÑÅºÅ· »óÅÂÆÐÅÏ
	bulletKingState* _state;


	player* _player;

public:
	bulletKing();
	~bulletKing();

	HRESULT init();
	void release();
	void update();
	void render();
	void InputHandle();
	void setBoss();
	void collision();

	tagBulletKing& getBulletKing() { return _bulletKing; }
	void setBulletKingX(int x) { _bulletKing.x = x; }
	void setBulletKingY(int y) { _bulletKing.y = y; }
	void setBulletKingCurrentFrameX(int currentX) { _bulletKing.currentFrameX = currentX; }
	void setBulletKingImg(image* bulletKingImg) { _bulletKing.img = bulletKingImg; }
	void setBulletKingIsAttack3(bool bulletKingIsAttack3) { _bulletKing.isAttack3 = bulletKingIsAttack3; }

	tagBulletKing& getBulletKingChair() { return _bulletKingChair; }
	void setBulletKingChairX(int x) { _bulletKingChair.x = x; }
	void setBulletKingChairY(int y) { _bulletKingChair.y = y; }
	void setBulletKingChairCurrentFrameX(int currentX) { _bulletKingChair.currentFrameX = currentX; }
	void setBulletKingAttack3(bool bulletKingChairAttack3) { _bulletKingChair.isAttack3 = bulletKingChairAttack3; }

	//ÃÑ¾Ë get
	bulletKingBullet* getBulletKingBullet() { return _bullet; }


	void linkPlayer(player* player) { _player = player; }
	player* getPlayer() { return _player; }
};

