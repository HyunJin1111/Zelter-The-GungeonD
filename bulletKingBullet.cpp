#include "stdafx.h"
#include "bulletKingBullet.h"

bulletKingBullet::bulletKingBullet()
{
}

bulletKingBullet::~bulletKingBullet()
{
}


void bulletKingBullet::release()
{
}

void bulletKingBullet::update()
{
	bulletMove1();
	bulletMove2();
	bulletMove3();
}

void bulletKingBullet::render()
{
	int cameraX = CAMERAMANAGER->getX();
	int cameraY = CAMERAMANAGER->getY();
	//공격패턴1 총알 렌더
	for (_viBulletKingBullet1 = _vBulletKingBullet1.begin(); _viBulletKingBullet1 != _vBulletKingBullet1.end(); ++_viBulletKingBullet1)
	{
		_viBulletKingBullet1->img->render(_viBulletKingBullet1->rc.left- cameraX, _viBulletKingBullet1->rc.top- cameraY);
	}
	//공격패턴2 총알 렌더
	for (_viBulletKingBullet2 = _vBulletKingBullet2.begin(); _viBulletKingBullet2 != _vBulletKingBullet2.end(); ++_viBulletKingBullet2)
	{
		_viBulletKingBullet2->img->frameRender2(_viBulletKingBullet2->rc.left, _viBulletKingBullet2->rc.top, _viBulletKingBullet2->currentX, 0, 1, 1,
			_viBulletKingBullet2->angle * (180 / PI), _viBulletKingBullet2->centerX, _viBulletKingBullet2->centerY);
	}
	//공격패턴3 총알 렌더
	for (_viBulletKingBullet3 = _vBulletKingBullet3.begin(); _viBulletKingBullet3 != _vBulletKingBullet3.end(); ++_viBulletKingBullet3)
	{
		_viBulletKingBullet3->img->render(_viBulletKingBullet3->rc.left- cameraX, _viBulletKingBullet3->rc.top- cameraY);
	}
	//렉탱글 확인
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBulletKingBullet1 = _vBulletKingBullet1.begin(); _viBulletKingBullet1 != _vBulletKingBullet1.end(); ++_viBulletKingBullet1)
		{
			D2DRENDER->DrawRectangle(_viBulletKingBullet1->rc, D2DRenderer::DefaultBrush::Black);
		}
		for (_viBulletKingBullet2 = _vBulletKingBullet2.begin(); _viBulletKingBullet2 != _vBulletKingBullet2.end(); ++_viBulletKingBullet2)
		{
			D2DRENDER->FillRectangle(_viBulletKingBullet2->rc, D2DRenderer::DefaultBrush::Black, _viBulletKingBullet2->angle * (180 / PI));
		}
		for (_viBulletKingBullet3 = _vBulletKingBullet3.begin(); _viBulletKingBullet3 != _vBulletKingBullet3.end(); ++_viBulletKingBullet3)
		{
			D2DRENDER->DrawRectangle(_viBulletKingBullet3->rc, D2DRenderer::DefaultBrush::Black);
		}
	}
}
//공격패턴1 총알 발사 시
void bulletKingBullet::bulletFire1(float x, float y)
{
	for (int i = 0; i < BULLETMAX / 2; i++)
	{
		if (BULLETMAX < _vBulletKingBullet1.size()) return;

		tagBulletKingBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBulletKingBullet));
		bullet.img = IMAGEMANAGER->findImage("bulletKingBullet1");
		bullet.speed = 3.0f;
		bullet.angle = PI / 2 + (i * 0.21f);
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.width = 16;
		bullet.height = 16;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

		_vBulletKingBullet1.push_back(bullet);
	}
}
//공격패턴1 움직임
void bulletKingBullet::bulletMove1()
{
	for (_viBulletKingBullet1 = _vBulletKingBullet1.begin(); _viBulletKingBullet1 != _vBulletKingBullet1.end();)
	{
		_viBulletKingBullet1->x += cosf(_viBulletKingBullet1->angle) * _viBulletKingBullet1->speed;
		_viBulletKingBullet1->y += -sinf(_viBulletKingBullet1->angle) * _viBulletKingBullet1->speed;
		_viBulletKingBullet1->rc = RectMakeCenter(_viBulletKingBullet1->x, _viBulletKingBullet1->y, _viBulletKingBullet1->img->getWidth(), _viBulletKingBullet1->img->getHeight());
		//예외처리
		if (_viBulletKingBullet1->rc.left < 0 || _viBulletKingBullet1->rc.right > 2000 || _viBulletKingBullet1->rc.top < 0 || _viBulletKingBullet1->rc.bottom > 1000)
		{
			_viBulletKingBullet1 = _vBulletKingBullet1.erase(_viBulletKingBullet1);
		}
		else ++_viBulletKingBullet1;

	}
}
//공격패턴2 총알 발사 시
void bulletKingBullet::bulletFire2(float x, float y, float playerX, float playerY)
{
	for (int i = 0; i < 3; i++)
	{
		if (BULLETMAX < _vBulletKingBullet2.size()) return;

		tagBulletKingBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBulletKingBullet));
		bullet.img = IMAGEMANAGER->findImage("bulletKingBullet2");

		bullet.speed = 5.0f;
		bullet.angle = GetAngle(x, y, playerX, playerY) + (i * 0.4f) - 0.4f;
		bullet.currentX = 0;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.width = 23;
		bullet.height = 12;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth() / bullet.img->getMaxFrameX(), bullet.img->getHeight());
		bullet.centerX = (bullet.rc.right - bullet.rc.left) / 2;
		bullet.centerY = (bullet.rc.bottom - bullet.rc.top) / 2;
		_vBulletKingBullet2.push_back(bullet);
	}
}
//공격패턴2 총알 움직임
void bulletKingBullet::bulletMove2()
{
	_count++;
	for (_viBulletKingBullet2 = _vBulletKingBullet2.begin(); _viBulletKingBullet2 != _vBulletKingBullet2.end();)
	{
		_viBulletKingBullet2->x += cosf(_viBulletKingBullet2->angle) * _viBulletKingBullet2->speed;
		_viBulletKingBullet2->y += -sinf(_viBulletKingBullet2->angle) * _viBulletKingBullet2->speed;
		_viBulletKingBullet2->rc = RectMakeCenter(_viBulletKingBullet2->x, _viBulletKingBullet2->y, _viBulletKingBullet2->img->getWidth() / _viBulletKingBullet2->img->getMaxFrameX(), _viBulletKingBullet2->img->getHeight());

		//총알 이미지 프레임
		if (_count % 10 == 0)
		{
			_viBulletKingBullet2->currentX++;
			if (_viBulletKingBullet2->currentX >= _viBulletKingBullet2->img->getMaxFrameX()) 	_viBulletKingBullet2->currentX = 0;
			_count = 0;
		}
		//예외처리
		if (_viBulletKingBullet2->rc.right < 0 || _viBulletKingBullet2->rc.left > 2000 || _viBulletKingBullet2->rc.bottom < 0 || _viBulletKingBullet2->rc.top > 1000)
		{
			_viBulletKingBullet2 = _vBulletKingBullet2.erase(_viBulletKingBullet2);
		}
		else ++_viBulletKingBullet2;
	}
}
//공격패턴3 총알 발사 시
void bulletKingBullet::bulletFire3(float x, float y)
{
	int count = 0;

	for (int i = 0; i < BULLETMAX * 10; i++)
	{
		count++;
		if (BULLETMAX * 10 < _vBulletKingBullet1.size()) return;

		tagBulletKingBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBulletKingBullet));
		bullet.img = IMAGEMANAGER->findImage("bulletKingBullet3");
		bullet.speed = 3.0f;
		bullet.angle = RND->getFromFloatTo(0, PI2);
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.width = 16;
		bullet.height = 16;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

		_vBulletKingBullet3.push_back(bullet);
		if (count >= 30) break;
	}
}
//공격패턴3 총알 움직임
void bulletKingBullet::bulletMove3()
{
	for (_viBulletKingBullet3 = _vBulletKingBullet3.begin(); _viBulletKingBullet3 != _vBulletKingBullet3.end();)
	{
		_viBulletKingBullet3->x += cosf(_viBulletKingBullet3->angle) * _viBulletKingBullet3->speed;
		_viBulletKingBullet3->y += -sinf(_viBulletKingBullet3->angle) * _viBulletKingBullet3->speed;
		_viBulletKingBullet3->rc = RectMakeCenter(_viBulletKingBullet3->x, _viBulletKingBullet3->y, _viBulletKingBullet3->img->getWidth(), _viBulletKingBullet3->img->getHeight());
		//예외처리
		if (_viBulletKingBullet3->rc.left < 0 || _viBulletKingBullet3->rc.right > 2000 || _viBulletKingBullet3->rc.top < 0 || _viBulletKingBullet3->rc.bottom > 1000)
		{
			_viBulletKingBullet3 = _vBulletKingBullet3.erase(_viBulletKingBullet3);
		}
		else ++_viBulletKingBullet3;

	}
}
