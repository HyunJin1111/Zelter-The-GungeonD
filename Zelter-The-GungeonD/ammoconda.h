#pragma once
#include "gameNode.h"
#include "ammocondaState.h"
#include "ammocondaBullet.h"
#include "progressBar.h"
#include "playerBullet.h"

#define AMMOCONDAMAX 11
#define PIDIVISION8		float(PI / 8.0f)

class player;

enum POTSTATE
{
	POT_IDLE,
	POT_ATTACK,
	POT_DEATH
};

struct tagAmmoconda
{
	image* img;							//아모콘다 이미지
	RECT rc;							//아모콘다 렉트
	float speed;						//아모콘다 속도
	float angle;						//아모콘다 각도(라디안)
	float radius;						//아모콘다 반지름
	float x, y;							//아모콘다 x, y
	int width, height;					//아모콘다 가로 길이, 세로 길이
	int differenceHeight;				//아모콘다 프레임별 세로 길이 차이
	int currentFrameX;					//아모콘다 x축 현재 프레임
	int currentFrameY;					//아모콘다 y축 현재 프레임
	int maxHp, currentHp;				//아모콘다 최대 체력, 현재 체력
	bool isAttack;						//아모콘다 공격여부
	int count;							//프레임카운트
	int attackCount;					//공격 카운트
	POTSTATE state;						//항아리용 enum문(상태)
};

class ammoconda : public gameNode
{
private:
	//아모콘다 구조체
	tagAmmoconda _ammoconda[AMMOCONDAMAX];
	int _currentHp, _maxHp;
	//아모콘다 총알
	ammocondaBullet* _ammocondaBullet;

	//체력
	progressBar* _hp;
	image* _bulletKing_hp;

	//아모콘다 상태패턴
	ammocondaState* _state;

	//z-oder용 벡터
	vector<tagAmmoconda*>				_vAmmoconda;
	vector<tagAmmoconda*>::iterator		_viAmmoconda;

	//항아리 구조체
	tagAmmoconda _pot;

	//항아리 등장여부
	bool _isPotCreate;
	int _potCount;


	player* _player;

public:
	ammoconda();
	~ammoconda();

	HRESULT init();
	void release();
	void update();
	void render();
	void InputHandle();
	void setBoss();
	void bossMove(int count, int division, string keyValue);
	void bossRecoveryMove(int count, int division, string keyValue, float x, float y, float playerX, float playerY);
	void setPot(int x, int y);
	void potMove();
	void potState();
	void potRender();
	void collision();


	//아모콘다 참조자
	tagAmmoconda& getAmmoconda(int index) { return _ammoconda[index]; }

	//항아리 참조자
	tagAmmoconda& getPot() { return _pot; }
	bool getIsPotCreate() { return _isPotCreate; }

	
	int getCurrentHp() { return _currentHp; }

	//총알 get
	ammocondaBullet* getBAmmocondaBullet() { return _ammocondaBullet; }

	void linkPlayer(player* player) { _player = player; }

	player* getPlayer() { return _player; }
};

