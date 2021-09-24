#include "stdafx.h"
#include "ammoconda.h"
#include "ammocondaIdle.h"
#include <vector>
#include <algorithm>
#include "player.h"

ammoconda::ammoconda()
{
}

ammoconda::~ammoconda()
{
}

HRESULT ammoconda::init()
{
	//상태패턴 할당
	_state = new ammocondaIdle();
	_state->enter(this);
	//hp 할당
	_hp = new progressBar;
	_hp->init(650, WINSIZEY - 100, 600, 50);
	//총알 할당
	_ammocondaBullet = new ammocondaBullet;

	//보스 초기화
	setBoss();

	//항아리용 카운트 및 생성여부
	_potCount = 0;
	_isPotCreate = false;

	return S_OK;
}

void ammoconda::release()
{
}
bool compare(tagAmmoconda * begin, tagAmmoconda * end)
{
	return begin->rc.bottom < end->rc.bottom;
}
void ammoconda::update()
{
	collision();
	//hp
	_hp->update();
	_hp->setGauge(_currentHp, _maxHp);
	if (_currentHp <= 3) _currentHp = 3;
	
	//항아리 생성
	if (!_isPotCreate)
	{
		_potCount++;

		if (_potCount >= 1000)
		{
			setPot(RND->getFromIntTo(100, 1150), RND->getFromIntTo(100, 600));
			_potCount = 0;
			_isPotCreate = true;
		}
	}
	//항아리 움직임
	if (_isPotCreate) potMove();

	//z-order 아모콘다 머리부터 몸통까지!
	for (int i = 0; i < _vAmmoconda.size(); i++)
	{
		sort(_vAmmoconda.begin(), _vAmmoconda.end(), compare);
	}

	//상태패턴
	InputHandle();
	_state->update(this);

	//총알 업데이트
	_ammocondaBullet->update();



}

void ammoconda::render()
{
	//항아리 렌더
	if (_isPotCreate) potRender();

	
	_hp->render();
	//본체 렌더
	for (int i = 0; i < _vAmmoconda.size(); i++)
	{
		_vAmmoconda[i]->img->
			frameRender2(_vAmmoconda[i]->rc.left, _vAmmoconda[i]->rc.top - _vAmmoconda[i]->differenceHeight, _vAmmoconda[i]->currentFrameX, _vAmmoconda[i]->currentFrameY);

		//렉트 확인용
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			D2DRENDER->DrawRectangle(_vAmmoconda[i]->rc, D2DRenderer::DefaultBrush::White);
		}
	}

	//총알 렌더
	_ammocondaBullet->render();
	//상태패턴 렌더
	_state->render(this);

}

void ammoconda::InputHandle()
{
	ammocondaState* newState = _state->InputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}
//보스 세팅
void ammoconda::setBoss()
{
	IMAGEMANAGER->addFrameImage("ammocondaHead", L"ammoconda/아모콘다머리Idle_60_45_8.png", 8, 1);
	IMAGEMANAGER->addFrameImage("ammocondaYum", L"ammoconda/아모콘다머리항아리냠_60_54_8_3.png", 8, 3);
	IMAGEMANAGER->addFrameImage("ammocondaBody1", L"ammoconda/아모콘다몸통1_41_57_4.png", 4, 1);
	IMAGEMANAGER->addFrameImage("ammocondaBody2", L"ammoconda/아모콘다몸통2_32_45_4.png", 4, 1);
	IMAGEMANAGER->addFrameImage("ammocondaBody3", L"ammoconda/아모콘다몸통3_21_30_4.png", 4, 1);
	IMAGEMANAGER->addFrameImage("ammocondaBody4", L"ammoconda/아모콘다몸통4_14_20_4.png", 4, 1);

	IMAGEMANAGER->addImage("ammocondaBullet1", L"ammoconda/아모콘다총알1_18_18.png");
	IMAGEMANAGER->addFrameImage("ammocondaBullet2", L"ammoconda/아모콘다총알2_22_22_10.png", 10, 1);
	IMAGEMANAGER->addImage("potBullet", L"ammoconda/항아리총알_18_18.png");
	//효과 이미지
	IMAGEMANAGER->addFrameImage("boom", L"effect/boom.png", 4, 1);
	_currentHp = _maxHp = 100;
	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		if (i == 0)
		{
			_ammoconda[i].img = IMAGEMANAGER->findImage("ammocondaHead");
			_ammoconda[i].x = WINSIZEX / 2;
			_ammoconda[i].y = WINSIZEY / 2 + 100;
			_ammoconda[i].angle = PI / 2 + PI;
			_ammoconda[i].radius = 60;
			_ammoconda[i].currentFrameX = 6;
			_ammoconda[i].currentFrameY = 0;
		}
		if (i > 0 && i <= 3)
		{
			_ammoconda[i].img = IMAGEMANAGER->findImage("ammocondaBody1");
			_ammoconda[i].radius = 41;
			_ammoconda[i].angle = _ammoconda[i - 1].angle;
			_ammoconda[i].currentFrameX = 0;
			_ammoconda[i].differenceHeight = 11;

		}
		if (i > 3 && i <= 6)
		{
			_ammoconda[i].img = IMAGEMANAGER->findImage("ammocondaBody2");
			_ammoconda[i].radius = 32;
			_ammoconda[i].angle = _ammoconda[i - 1].angle;
			_ammoconda[i].currentFrameX = 0;
			_ammoconda[i].differenceHeight = 9;
		}
		if (i > 6 && i <= 8)
		{
			_ammoconda[i].img = IMAGEMANAGER->findImage("ammocondaBody3");
			_ammoconda[i].radius = 21;
			_ammoconda[i].angle = _ammoconda[i - 1].angle;
			_ammoconda[i].currentFrameX = 0;
			_ammoconda[i].differenceHeight = 5;
		}
		if (i > 8 && i <= 10)
		{
			_ammoconda[i].img = IMAGEMANAGER->findImage("ammocondaBody4");
			_ammoconda[i].radius = 14;
			_ammoconda[i].angle = _ammoconda[i - 1].angle;
			_ammoconda[i].currentFrameX = 0;
			_ammoconda[i].differenceHeight = 3;
		}
		if (i != 0)
		{
			_ammoconda[i].x = _ammoconda[i - 1].x - cosf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
			_ammoconda[i].y = _ammoconda[i - 1].y - -sinf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
		}
		_ammoconda[i].speed = 5.f;
		_ammoconda[i].rc = RectMakeCenter(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i].radius, _ammoconda[i].radius);

		_vAmmoconda.push_back(&_ammoconda[i]);
	}
}

void ammoconda::bossMove(int count, int division, string keyValue)
{
	_ammoconda[0].img = IMAGEMANAGER->findImage(keyValue);
	//보스 이동 예외처리
	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		if (_ammoconda[i].rc.left <= 0)
		{
			_ammoconda[i].x = _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.right >= WINSIZEX)
		{
			_ammoconda[i].x = WINSIZEX - _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.top <= 0)
		{
			_ammoconda[i].y = _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI2 - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.bottom >= WINSIZEY)
		{
			_ammoconda[i].y = WINSIZEY - _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI2 - _ammoconda[0].angle;
		}
	}
	//아마콘다 앵글값 변경
	if (count % division == 0)
	{
		int rand;
		float angle;
		rand = RND->getFromIntTo(0, 2);
		angle = RND->getFromFloatTo(0, 1.5f);
		switch (rand)
		{
		case 0:
			_ammoconda[0].angle = _ammoconda[0].angle - angle;
			break;
		case 1:
			_ammoconda[0].angle = _ammoconda[0].angle + angle;
			break;
		}
	}

	//아모콘다 머리 각도 예외처리
	if (_ammoconda[0].angle >= PI2) _ammoconda[0].angle -= PI2;
	if (_ammoconda[0].angle <= 0) _ammoconda[0].angle += PI2;
	//아모콘다 머리 현재 프레임 설정
	_ammoconda[0].currentFrameX = int(_ammoconda[0].angle / (PIDIVISION8 * 2));

	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		if (i == 0)
		{
			//머리 이동
			_ammoconda[i].x += cosf(_ammoconda[i].angle) * _ammoconda[i].speed;
			_ammoconda[i].y += -sinf(_ammoconda[i].angle) * _ammoconda[i].speed;
		}
		else
		{
			//원의 지름과 앞의 원과의 거리 비교
			if (_ammoconda[i].radius / 2 <= GetDistance(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i - 1].x, _ammoconda[i - 1].y))
			{
				_ammoconda[i].angle = GetAngle(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i - 1].x, _ammoconda[i - 1].y);
				//보정 작업
				_ammoconda[i].x = _ammoconda[i - 1].x - cosf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
				_ammoconda[i].y = _ammoconda[i - 1].y - -sinf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
			}
			//몸통 이동
			_ammoconda[i].x += cosf(_ammoconda[i].angle) * _ammoconda[i].speed;
			_ammoconda[i].y += -sinf(_ammoconda[i].angle) * _ammoconda[i].speed;
		}
		_ammoconda[i].rc = RectMakeCenter(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i].radius, _ammoconda[i].radius);
	}


}

void ammoconda::bossRecoveryMove(int count, int division, string keyValue, float x, float y, float playerX, float playerY)
{
	_ammoconda[0].img = IMAGEMANAGER->findImage(keyValue);
	//보스 이동 예외처리
	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		if (_ammoconda[i].rc.left <= 0)
		{
			_ammoconda[i].x = _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.right >= WINSIZEX)
		{
			_ammoconda[i].x = WINSIZEX - _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.top <= 0)
		{
			_ammoconda[i].y = _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI2 - _ammoconda[0].angle;
		}
		if (_ammoconda[i].rc.bottom >= WINSIZEY)
		{
			_ammoconda[i].y = WINSIZEY - _ammoconda[i].radius / 2;
			_ammoconda[0].angle = PI2 - _ammoconda[0].angle;
		}
	}
	//아마콘다 앵글값 변경
	if (count % division == 0)
	{
		_ammoconda[0].angle = GetAngle(x, y, playerX, playerY);
	}

	//아모콘다 머리 각도 예외처리
	if (_ammoconda[0].angle >= PI2) _ammoconda[0].angle -= PI2;
	if (_ammoconda[0].angle <= 0) _ammoconda[0].angle += PI2;
	//아모콘다 머리 현재 프레임 설정
	_ammoconda[0].currentFrameX = int(_ammoconda[0].angle / (PIDIVISION8 * 2));

	for (int i = 0; i < AMMOCONDAMAX; i++)
	{
		if (i == 0)
		{
			//머리 이동
			_ammoconda[i].x += cosf(_ammoconda[i].angle) * _ammoconda[i].speed;
			_ammoconda[i].y += -sinf(_ammoconda[i].angle) * _ammoconda[i].speed;
		}
		else
		{
			//원의 지름과 앞의 원과의 거리 비교
			if (_ammoconda[i].radius / 2 <= GetDistance(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i - 1].x, _ammoconda[i - 1].y))
			{
				_ammoconda[i].angle = GetAngle(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i - 1].x, _ammoconda[i - 1].y);
				//보정 작업
				_ammoconda[i].x = _ammoconda[i - 1].x - cosf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
				_ammoconda[i].y = _ammoconda[i - 1].y - -sinf(_ammoconda[i].angle) * (_ammoconda[i].radius / 2 + _ammoconda[i - 1].radius / 2);
			}
			//몸통 이동
			_ammoconda[i].x += cosf(_ammoconda[i].angle) * _ammoconda[i].speed;
			_ammoconda[i].y += -sinf(_ammoconda[i].angle) * _ammoconda[i].speed;
		}
		_ammoconda[i].rc = RectMakeCenter(_ammoconda[i].x, _ammoconda[i].y, _ammoconda[i].radius, _ammoconda[i].radius);
	}


}
void ammoconda::collision()
{
	if (_currentHp > 3) 
	{
		for (int j = 0; j < AMMOCONDAMAX; ++j)
		{
			for (int i = 0; i < _player->getPlayerBullet()->getVBulletN().size(); ++i)
			{
				if (IsCollision(_ammoconda[j].rc, _player->getPlayerBullet()->getVBulletN()[i].rc))
				{
					_currentHp--;
					_player->getPlayerBullet()->releaseBullet(i);
				}
			}
			for (int i = 0; i < _player->getPlayerBullet()->getVBulletF().size(); ++i)
			{
				if (IsCollision(_ammoconda[j].rc, _player->getPlayerBullet()->getVBulletF()[i].rc))
				{
					_currentHp--;
					_player->getPlayerBullet()->releaseF(i);
				}
			}
			for (int i = 0; i < _player->getPlayerBullet()->getvGrenadeBullet().size(); ++i)
			{
				if (IsCollision(_ammoconda[j].rc, _player->getPlayerBullet()->getvGrenadeBullet()[i].rc))
				{
					_currentHp--;
					_player->getPlayerBullet()->releaseGrenadeBullet(i);
				}
			}
			for (int i = 0; i < _player->getPlayerBullet()->getVBulletH().size(); ++i)
			{
				if (IsCollision(_ammoconda[j].rc, _player->getPlayerBullet()->getVBulletH()[i].rc))
				{
					_currentHp--;
					_player->getPlayerBullet()->releaseH(i);
				}
			}
			for (int i = 0; i < _player->getPlayerBullet()->getVBulletS().size(); ++i)
			{
				if (IsCollision(_ammoconda[j].rc, _player->getPlayerBullet()->getVBulletS()[i].rc))
				{
					_currentHp--;
					_player->getPlayerBullet()->releaseS(i);
				}
			}
		}
		
	}
	//항아리 충돌
	if (_pot.currentHp > 3)
	{		
		for (int i = 0; i < _player->getPlayerBullet()->getVBulletN().size(); ++i)
		{
			if (IsCollision(_pot.rc, _player->getPlayerBullet()->getVBulletN()[i].rc))
			{
				_pot.currentHp--;
				_player->getPlayerBullet()->releaseBullet(i);
			}
		}
		for (int i = 0; i < _player->getPlayerBullet()->getVBulletF().size(); ++i)
		{
			if (IsCollision(_pot.rc, _player->getPlayerBullet()->getVBulletF()[i].rc))
			{
				_pot.currentHp--;
				_player->getPlayerBullet()->releaseF(i);
			}
		}
		for (int i = 0; i < _player->getPlayerBullet()->getvGrenadeBullet().size(); ++i)
		{
			if (IsCollision(_pot.rc, _player->getPlayerBullet()->getvGrenadeBullet()[i].rc))
			{
				_pot.currentHp--;
				_player->getPlayerBullet()->releaseGrenadeBullet(i);
			}
		}
		for (int i = 0; i < _player->getPlayerBullet()->getVBulletH().size(); ++i)
		{
			if (IsCollision(_pot.rc, _player->getPlayerBullet()->getVBulletH()[i].rc))
			{
				_pot.currentHp--;
				_player->getPlayerBullet()->releaseH(i);
			}
		}
		for (int i = 0; i < _player->getPlayerBullet()->getVBulletS().size(); ++i)
		{
			if (IsCollision(_pot.rc, _player->getPlayerBullet()->getVBulletS()[i].rc))
			{
				_pot.currentHp--;
				_player->getPlayerBullet()->releaseS(i);
			}
		}
	}
	if (_pot.currentHp <= 3) _isPotCreate = false;
}



