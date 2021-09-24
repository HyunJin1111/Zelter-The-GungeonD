#include "stdafx.h"
#include "eggNyang.h"
#include "eggNyangIdle.h"

#include "player.h"

HRESULT eggNyang::init()
{
	imageAdd();

	_eggNyang.bullet = new eggNyangBullet;
	_eggNyang.lazer = new eggNyangLazer;
	_eggNyang.sword = new eggNyangSword;
	_eggNyang.progressBar = new progressBar;
	_eggNyang.progressBar->init(650, WINSIZEY - 100, 50, 600);

	_eggNyang.x = WINSIZEX / 2;
	_eggNyang.y = WINSIZEY / 2;
	_eggNyang.currentHp = 100;
	_eggNyang.maxHp = 100;
	_eggNyang.direction = 0;
	_eggNyang.speed = 5.0f;
	_eggNyang.isDie = false;

	_isFire = false;

	_eggNyangState = new eggNyangIdle;
	_eggNyangState->enter(this);

	_eggNyang.rc = RectMake(_eggNyang.x, _eggNyang.y, _eggNyang.img->getFrameWidth(), _eggNyang.img->getFrameHeight());

	_invincibility = false;

	return S_OK;
}

void eggNyang::release()
{
}

void eggNyang::update()
{
	cout << _eggNyangState->getStateName() << endl;
	if (_eggNyang.currentHp <= 0) _eggNyang.currentHp = 0;
	_eggNyang.progressBar->setGauge(_eggNyang.currentHp, _eggNyang.maxHp);
	_eggNyang.progressBar->update();

	//=========상태 확인용=============
//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _eggNyang.currentHp = 0;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) _eggNyang.direction = 0;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) _eggNyang.direction = 1;
	//================================

	float directAngle = GetAngle(_player->getPlayer().x, _player->getPlayer().y, _eggNyang.x, _eggNyang.y);
	if (directAngle > PI / 2 && directAngle < 3 * PI / 2) _eggNyang.direction = 0;
	else _eggNyang.direction = 1;

	inPutHandle();
	attackPatternSign();
	hitEggNyang();

	_eggNyangState->update(this);

	if (_eggNyangState->getIsMove()) move();	//움직이는 상태일 때 bool값 angle값을 받아 움직임

	_eggNyang.rc = RectMake(_eggNyang.x, _eggNyang.y, _eggNyang.img->getFrameWidth(), _eggNyang.img->getFrameHeight());
}

void eggNyang::render()
{
	_eggNyangState->render(this);

	if (_eggNyang.bullet->getEggNyangVBullet().size() != 0) _eggNyang.bullet->render();
	else if (_eggNyang.lazer->getEggNyangVLazer().size() != 0) _eggNyang.lazer->render();
	else if (_eggNyang.sword->getEggNyangVSword().size() != 0) _eggNyang.sword->render();

	_eggNyang.progressBar->render();
}

void eggNyang::inPutHandle()
{
	eggNyangStateBase* newState = _eggNyangState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_eggNyangState);
		_eggNyangState = newState;
		_eggNyangState->enter(this);
	}
}

void eggNyang::hitEggNyang()
{
	RECT temp;
	if (_invincibility)
	{
		_timeCount++;
		if (_timeCount >= _timeCountEnd)
		{
			_invincibility = false;
			_timeCount = 0;
		}
	}

	for (int i = 0; i < _player->getPlayerBullet()->getVBulletF().size(); i++)
	{
		if (!_invincibility && IntersectRect(&temp, &_eggNyang.rc, &_player->getPlayerBullet()->getVBulletF()[i].rc))
		{
			_invincibility = true;
			_timeCount = TIMEMANAGER->getWorldTime();
			_timeCountEnd = _timeCount + 50;
			_player->getPlayerBullet()->releaseF(i);
			_eggNyang.currentHp -= 15;
		}
	}
	for (int i = 0; i < _player->getPlayerBullet()->getVBulletN().size(); i++)
	{
		if (!_invincibility && IntersectRect(&temp, &_eggNyang.rc, &_player->getPlayerBullet()->getVBulletN()[i].rc))
		{
			_invincibility = true;
			_timeCount = TIMEMANAGER->getWorldTime();
			_timeCountEnd = _timeCount + 50;
			_player->getPlayerBullet()->releaseBullet(i);
			_eggNyang.currentHp -= 15;
		}
	}
	for (int i = 0; i < _player->getPlayerBullet()->getvGrenadeBullet().size(); i++)
	{
		if (!_invincibility && IntersectRect(&temp, &_eggNyang.rc, &_player->getPlayerBullet()->getvGrenadeBullet()[i].rc))
		{
			_invincibility = true;
			_timeCount = TIMEMANAGER->getWorldTime();
			_timeCountEnd = _timeCount + 50;
			_player->getPlayerBullet()->releaseGrenadeBullet(i);
			_eggNyang.currentHp -= 15;
		}
	}
	for (int i = 0; i < _player->getPlayerBullet()->getVBulletH().size(); i++)
	{
		if (!_invincibility && IntersectRect(&temp, &_eggNyang.rc, &_player->getPlayerBullet()->getVBulletH()[i].rc))
		{
			_invincibility = true;
			_timeCount = TIMEMANAGER->getWorldTime();
			_timeCountEnd = _timeCount + 50;
			_player->getPlayerBullet()->releaseH(i);
			_eggNyang.currentHp -= 15;
		}
	}
	for (int i = 0; i < _player->getPlayerBullet()->getVBulletS().size(); i++)
	{
		if (!_invincibility && IntersectRect(&temp, &_eggNyang.rc, &_player->getPlayerBullet()->getVBulletS()[i].rc))
		{
			_invincibility = true;
			_timeCount = TIMEMANAGER->getWorldTime();
			_timeCountEnd = _timeCount + 50;
			_player->getPlayerBullet()->releaseS(i);
			_eggNyang.currentHp -= 15;
		}
	}
}

void eggNyang::imageAdd()	//이미지 추가
{
	//보스::에그냥 이미지
	IMAGEMANAGER->addFrameImage("eggNyangIdle", L"eggNyang/eggNyangIdle.png", 3, 2);
	IMAGEMANAGER->addFrameImage("eggNyangAttack", L"eggNyang/eggNyangAttack.png", 2, 2);
	IMAGEMANAGER->addFrameImage("eggNyangDie", L"eggNyang/eggNyangDie.png", 2, 2);
	IMAGEMANAGER->addFrameImage("eggNyangBomb", L"eggNyang/eggNyangBomb.png", 3, 1);
	//총알::에그냥 이미지
	IMAGEMANAGER->addFrameImage("eggNyangLazerReady", L"eggNyangBullet/eggNyangLazerReady.png", 1, 1);
	IMAGEMANAGER->addFrameImage("eggNyangLazer1", L"eggNyangBullet/eggNyangLazer1.png", 3, 2);
	IMAGEMANAGER->addFrameImage("eggNyangLazer1End", L"eggNyangBullet/eggNyangLazer1End.png", 4, 2);
	IMAGEMANAGER->addFrameImage("eggNyangLazer2", L"eggNyangBullet/eggNyangLazer2.png", 3, 2);
	IMAGEMANAGER->addFrameImage("eggNyangLazer2End", L"eggNyangBullet/eggNyangLazer2End.png", 4, 2);
	IMAGEMANAGER->addImage("eggNyangSword", L"eggNyangBullet/eggNyangSword.png");
	IMAGEMANAGER->addFrameImage("eggNyangBullet", L"eggNyangBullet/eggNyangBullet.png", 10, 1);
	//효과 이미지
	IMAGEMANAGER->addFrameImage("boom", L"effect/boom.png", 4, 1);
	//배경 이미지
	IMAGEMANAGER->addImage("eggNynagBackGround", L"eggNyang/eggNyangBackGround.png");

	SOUNDMANAGER->addSound("에그냥공격1", "sound/에그냥공격1.wav", false, false);
	SOUNDMANAGER->addSound("에그냥공격2", "sound/에그냥공격2.wav", false, false);
	SOUNDMANAGER->addSound("에그냥공격3", "sound/에그냥공격3.wav", false, false);
}

void eggNyang::move()
{
	_eggNyang.x += cosf(_eggNyangState->getAngle()) * _eggNyang.speed;
	_eggNyang.y += -sinf(_eggNyangState->getAngle()) * _eggNyang.speed;
}

void eggNyang::attackPatternSign()
{
	if (_eggNyang.bullet->getEggNyangVBullet().size() != 0) _eggNyang.bullet->update();
	else if (_eggNyang.lazer->getEggNyangVLazer().size() != 0) _eggNyang.lazer->update();
	else if (_eggNyang.sword->getEggNyangVSword().size() != 0)
	{
		_eggNyang.sword->moveSword(_player->getPlayer().x, _player->getPlayer().y, _eggNyangState->getIsMove()); //공격을 생성했다가 보스 움직임이 끝나면 발사
	}

	if (_eggNyangState->getStateName() == "eggNyangAttack3" && !_eggNyangState->getIsMove()
		&& _bulletFireCount < EGGNYANGBULLETMAX)
	{
		_bulletFireCount++;
		_eggNyang.bullet->bulletFire((_eggNyang.rc.left + _eggNyang.rc.right) / 2, (_eggNyang.rc.top + _eggNyang.rc.bottom) / 2, _bulletFireCount);
		
	}
	if (_eggNyangState->getStateName() == "eggNyangAttack3" && !_eggNyangState->getIsMove()	&& _bulletFireCount == EGGNYANGBULLETMAX / 2) SOUNDMANAGER->play("에그냥공격1");
	
}
