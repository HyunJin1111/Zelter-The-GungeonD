#pragma once
#include "gameNode.h"
#define BULLETMAX 100

struct tagAmmocondaBullet
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
	int isWave;			//총알 웨이브효과용
};

class ammocondaBullet : public gameNode
{
private:
	//패턴1 총알
	vector<tagAmmocondaBullet>				_vAmmocondaBullet1;
	vector<tagAmmocondaBullet>::iterator	_viAmmocondaBullet1;
	//패턴2 총알
	vector<tagAmmocondaBullet>				_vAmmocondaBullet2;
	vector<tagAmmocondaBullet>::iterator	_viAmmocondaBullet2;
	//항아리 총알
	vector<tagAmmocondaBullet>				_vPotBullet;
	vector<tagAmmocondaBullet>::iterator	_viPotBullet;

	//이미지 프레임 카운트용
	int _count;

public:
	ammocondaBullet();
	~ammocondaBullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void bulletFire1(float x, float y, float playerX, float playerY);
	void bulletMove1();
	void bulletFire2(float x, float y, float playerX, float playerY);
	void bulletMove2();
	void bulletFirePot(float x, float y, float playerX, float playerY);
	void bulletMovePot();

	//패턴1 총알
	vector<tagAmmocondaBullet>				getVammoCondaBullet1() {return _vAmmocondaBullet1;}
	vector<tagAmmocondaBullet>::iterator	getVIammoCondaBullet1() { return _viAmmocondaBullet1; }
	//패턴2 총알
	vector<tagAmmocondaBullet>				getVammoCondaBullet2() {return _vAmmocondaBullet2;}
	vector<tagAmmocondaBullet>::iterator	getViammoCondaBullet2() {return _viAmmocondaBullet2;}
	//항아리 총알
	vector<tagAmmocondaBullet>				getVpotBullet() { return _vPotBullet;}
	vector<tagAmmocondaBullet>::iterator	getVipotBullet() { return _viPotBullet; }
	
};

