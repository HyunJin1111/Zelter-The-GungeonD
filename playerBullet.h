#pragma once
#include "gameNode.h"
#include <vector>

#define PI 3.141592

class player;



enum GUNTYPE
{
	NORMAL,
	SHOTGUN,
	HOMING,
	GRENADE,
	FLAMETHROWER
};


struct tagBoom2
{
	image* img;					//ÀÌ¹ÌÁö
	float x, y;						//ÁÂÇ¥
	int effectFrameX;				//ÀÌÆåÆ® ÇÁ·¹ÀÓ
	bool playeEffectEnd;			//ÀÌÆåÆ® Àç»ýÀÌ ³¡³µ´ÂÁö
};


struct tagPlayerBullet
{
	typedef struct SHAPE
	{
		double left, top, width, height, degreeAngle;
	};


	RECT rc;
	image* img;
	SHAPE bulletShape;
	float x, y;
	float fire;
	float angle;
	float speed;
	float power;
	float radius;
	float fireX, fireY;
	bool isFire;
	int count; // ¼ö·ùÅº Æø¹ß Ä«¿îÆ®
	int currentFrameX;
	int currentFrameY;
	int index;
	int bulletMax;
	float range;
	float damage;
	float gravity;
};


class playerBullet : public gameNode
{
private:
	int _cameraX;
	int _cameraY;


	vector<tagBoom2> _vBoom;
	int _effectFrameCount;
	int _playEffectNum;


public:
	vector<tagPlayerBullet> _vBulletN;
	vector<tagPlayerBullet>::iterator _viBulletN;


	vector<tagPlayerBullet> _vBulletS;
	vector<tagPlayerBullet>::iterator _viBulletS;

	vector<tagPlayerBullet> _vBulletH;
	vector<tagPlayerBullet>::iterator _viBulletH;

	vector<tagPlayerBullet> _vBulletG;
	vector<tagPlayerBullet>::iterator _viBulletG;

	vector<tagPlayerBullet> _vGrenadeBullet;
	vector<tagPlayerBullet>::iterator _viGrenadeBullet;

	vector<tagPlayerBullet> _vBulletF;
	vector<tagPlayerBullet>::iterator _viBulletF;

	//tagPlayerBullet _playerBullet;
	const char* _image;
	float _range;
	int _bulletMax;
	int _count;
	int _guntype;
	float _disX, _disY;

	player* _player;


	HRESULT init();
	void releaseBullet(int index);
	void releaseS(int index);
	void releaseH(int index);
	void releaseG(int index);
	void releaseGrenadeBullet(int index);
	void releaseF(int index);

	void update();
	void render();

	void fire(float x, float y, float angle, float speed, int type, float power);
	void move(int type, float x, float y);
	void move(int type); //¿ÀÇÂ¿ùµå


	// ¼ö·ùÅº ÃÑ¾Ë Àü¿ë
	void fireGrenadeBullet(float x, float y, float angle, float speed);
	void moveGrenadeBullet();




	float getPower() { return _viBulletN->power; }
	void setPower(float power) { _viBulletN->power = power; }
	void setplayerBulletCount(int count) { _viBulletG->count = count; }


	vector<tagPlayerBullet> getVBulletN() { return _vBulletN; }
	vector<tagPlayerBullet>::iterator getViBulletN() { return _viBulletN; }


	vector<tagPlayerBullet> getVBulletS() { return _vBulletS; }
	vector<tagPlayerBullet>::iterator getViBulletS() { return _viBulletS; }

	vector<tagPlayerBullet> getVBulletH() { return _vBulletH; }
	vector<tagPlayerBullet>::iterator getViBulletH() { return _viBulletH; }

	vector<tagPlayerBullet> getvBulletG() { return _vBulletG; }
	vector<tagPlayerBullet>::iterator getviBulletG() { return _viBulletG; }

	vector<tagPlayerBullet> getvGrenadeBullet() { return _vGrenadeBullet; }
	vector<tagPlayerBullet>::iterator getviGrenadeBullet() { return _viGrenadeBullet; }

	vector<tagPlayerBullet> getVBulletF() { return _vBulletF; }
	vector<tagPlayerBullet>::iterator getViBulletF() { return _viBulletF; }


	void setPlayerLink(player* player) { _player = player; }

	void produceEffect(float x, float y);
	void playEffect();

};

