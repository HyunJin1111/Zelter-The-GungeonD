#pragma once
#include "gameNode.h"
#include <vector>
#define BULLETMAX 60

struct tagBulletKingBullet
{
	image* img;				//총알 이미지
	RECT rc;				//총알 렉트
	float x, y;				//총알 x, y
	float width, height;	//총알 가로길이, 세로길이
	float centerX, centerY; //총알 중앙
	float fireX, fireY;		//총알 렉트 중앙값
	int currentX;			//총알 현재 x축 프레임
	float speed;			//총알 속도
	float angle;			//총알 각도(라디안)
	bool isFire;			//총알 발사 여부
};

class bulletKingBullet : public gameNode
{
private:
	//패턴1 총알
	vector<tagBulletKingBullet>			  _vBulletKingBullet1;
	vector<tagBulletKingBullet>::iterator _viBulletKingBullet1;
	//패턴2 총알
	vector<tagBulletKingBullet>			  _vBulletKingBullet2;
	vector<tagBulletKingBullet>::iterator _viBulletKingBullet2;
	//패턴3 총알
	vector<tagBulletKingBullet>			  _vBulletKingBullet3;
	vector<tagBulletKingBullet>::iterator _viBulletKingBullet3;

	//이미지 프레임 카운트용
	int _count;
	

public:
	bulletKingBullet();
	~bulletKingBullet();

	void release();
	void update();
	void render();

	void bulletFire1(float x, float y);
	void bulletMove1();
	void bulletFire2(float x, float y, float playerX, float playerY);
	void bulletMove2();
	void bulletFire3(float x, float y);
	void bulletMove3();

	vector<tagBulletKingBullet>			    getvBulletKingBullet1() { return _vBulletKingBullet1; }
	vector<tagBulletKingBullet>::iterator   getviBulletKingBullet1() { return  _viBulletKingBullet1; }

	vector<tagBulletKingBullet>				getvBulletKingBullet2() { return _vBulletKingBullet2; }
	vector<tagBulletKingBullet>::iterator   getviBulletKingBullet2() { return _viBulletKingBullet2; }

	vector<tagBulletKingBullet>				getvBulletKingBullet3() { return _vBulletKingBullet3; }
	vector<tagBulletKingBullet>::iterator   getviBulletKingBullet3() { return _viBulletKingBullet3; }
};

