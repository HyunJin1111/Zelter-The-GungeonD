#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "quickSlot.h"
#include "progressBar.h"

#include "inGameMap.h"
#include "bulletKingMap.h"
#include "ammocondaMap.h"
#include "niflheimMap.h"
#include "eggNyangMap.h"

#include "niflheimBullet.h"
#include "bulletKingBullet.h"
#include "eggNyangBullet.h"
#include "ammocondaBullet.h"


class bulletKing;
class ammoconda;
class niflheim;
class eggNyang;
class playerBullet;
class stageManager;
class fishMan;
class dinosaur;


struct tagPlayer
{
	image* img;
	RECT rc;
	RECT shadow;

	int currentHP;
	int maxHP;
	int direction;
	int movingDirection;
	float x, y;
	float speed;
	float angle;
	float jumpPower; // 던그리드 보스 씬에서 사용
	int currentFrameX;
	int currentFrameY;

	bool isHit;
	bool isEnd;
	bool isDeath;
	bool isDunGreed; // 던그리드 보스씬 구분용
	bool isJump; // 점프체크
	bool isCollide;
};
struct tagPlayerGun
{
	image* img;
	RECT rc;
	float x, y;
	float angle;
};

class player : public gameNode
{
private:
	tagPlayer _player;
	tagPlayerGun _playerGun;
	playerState* state;
	quickSlot* _quickSlot;
	progressBar* _progressBar;
	
	

	int _count;
	int _index;
	int _timer;
	int _blink;
	int _gunType;
	bool _imageON;
	float _bulletKingSize = 0.9;
	float _ammoCondaSize = 0.7;
	float _openWorldSize = 0.7;


	image* _mouse;
	playerBullet* _playerBullet;

	//======================다른 곳에서 불러온 변수=================
	inGameMap* _inGame;
	bulletKingMap* _bulletKingMap;
	ammocondaMap* _ammocondaMap;
	eggNyangMap* _eggNyangMap;
	niflheimMap* _niflheimMap;


	int _cameraX;
	int _cameraY;
	POINT _mapMouse;
	RECT _rcc[2];
	RECT _rcc2[3];

	bulletKing* _bulletKing;
	ammoconda* _ammoconda;
	niflheim* _niflheim;
	eggNyang* _eggNyang;
	fishMan* _fishMan;
	dinosaur* _dinosaur;

public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//플레이어 참조자
	//tagPlayer& getPlayer() { return _player; }

	RECT getRect() { return _player.rc; }
	RECT getShadowRect() { return _player.shadow; }
	playerState* getState() { return state; }
	playerBullet* getPlayerBullet() { return _playerBullet; }

	tagPlayer getPlayer() { return _player; }

	float getPlayerGunAngle() { return _playerGun.angle; }

	int getPlayerGuntype() { return _gunType; }

	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }

	void setHit(bool hit) { _player.isHit = hit; }
	float hitDamage(float damage);
	void setPlayerDirection(int direction) { _player.direction = direction; }

	void setPlayerImage(image* img) { _player.img = img; }

	void addIMAGES();

	void inputHandle();

	void setGuntype(int type) { _gunType = type; }
	void setGunRECT(RECT rc) { _playerGun.rc = rc; }

	float getPlayerGunX() { return _playerGun.x; }
	float getPlayerGunY() { return _playerGun.y; }

	float getGunAngle() { return _playerGun.angle; }
	void setGunAngle(float playerGunAngle) { _playerGun.angle = playerGunAngle; }

	void setPlayerCurrentFrameX(int frameX) { _player.currentFrameX = frameX; }

	void setPlayerisEnd(bool end) { _player.isEnd = end; }

	void setPlayerisDeath(bool death) { _player.isDeath = death; }

	void setplayerBulletLink(playerBullet* playerBullet) { _playerBullet = playerBullet; }

	void setPlayerMovingDirection(int movingdirection) { _player.movingDirection = movingdirection; }

	void setIsjump(bool jump) { _player.isJump = jump; }

	void setPlayerIscollde(bool collision) { _player.isCollide = collision; }

	//==================맵 링크 관련====================================
	void linkOpenWorldMap(inGameMap* map) { _inGame = map; }
	void linkBulletKingMap(bulletKingMap* map) { _bulletKingMap = map; }
	void linkAmmocondaMap(ammocondaMap* map) { _ammocondaMap = map; }
	void linkEggNyangMap(eggNyangMap* map) { _eggNyangMap = map; }
	void linkNiflheimMap(niflheimMap* map) { _niflheimMap = map; }
	void setKeyType(bool type) { _player.isDunGreed = type; }
	void tileDetect(string sceneName);

	//맵추가하자

	void linkBulletKing(bulletKing* bulletKing) { _bulletKing = bulletKing; }
	void linkAmmoconda(ammoconda* ammoconda) { _ammoconda = ammoconda; }
	void linkNiflheim(niflheim* niflheim) { _niflheim = niflheim; }
	void linkEggNyang(eggNyang* eggNyang) { _eggNyang = eggNyang; }
};
