#include "stdafx.h"
#include "ammocondaBullet.h"

ammocondaBullet::ammocondaBullet()
{
}

ammocondaBullet::~ammocondaBullet()
{
}

HRESULT ammocondaBullet::init()
{
	return S_OK;
}

void ammocondaBullet::release()
{
}

void ammocondaBullet::update()
{
	bulletMove1();
	bulletMove2();
	bulletMovePot();
}

void ammocondaBullet::render()
{
	//공격패턴1 총알 렌더
	for (_viAmmocondaBullet1 = _vAmmocondaBullet1.begin(); _viAmmocondaBullet1 != _vAmmocondaBullet1.end(); ++_viAmmocondaBullet1)
	{
		_viAmmocondaBullet1->img->render(_viAmmocondaBullet1->rc.left, _viAmmocondaBullet1->rc.top);
	}
	//공격패턴2 총알 렌더
	for (_viAmmocondaBullet2 = _vAmmocondaBullet2.begin(); _viAmmocondaBullet2 != _vAmmocondaBullet2.end(); ++_viAmmocondaBullet2)
	{
		_viAmmocondaBullet2->img->frameRender2(_viAmmocondaBullet2->rc.left, _viAmmocondaBullet2->rc.top, _viAmmocondaBullet2->currentX, 0, 1, 1,
			_viAmmocondaBullet2->angle * (180 / PI), _viAmmocondaBullet2->centerX, _viAmmocondaBullet2->centerY);
	}
	//항아리 총알 렌더
	for (_viPotBullet = _vPotBullet.begin(); _viPotBullet != _vPotBullet.end(); ++_viPotBullet)
	{
		_viPotBullet->img->render(_viPotBullet->rc.left, _viPotBullet->rc.top);
	}
	//렉트 확인용
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viAmmocondaBullet1 = _vAmmocondaBullet1.begin(); _viAmmocondaBullet1 != _vAmmocondaBullet1.end(); ++_viAmmocondaBullet1)
		{
			D2DRENDER->DrawRectangle(_viAmmocondaBullet1->rc, D2DRenderer::DefaultBrush::White);
		}
		for (_viAmmocondaBullet2 = _vAmmocondaBullet2.begin(); _viAmmocondaBullet2 != _vAmmocondaBullet2.end(); ++_viAmmocondaBullet2)
		{
			D2DRENDER->DrawRectangle(_viAmmocondaBullet2->rc, D2DRenderer::DefaultBrush::White);
		}
		for (_viPotBullet = _vPotBullet.begin(); _viPotBullet != _vPotBullet.end(); ++_viPotBullet)
		{
			D2DRENDER->DrawRectangle(_viPotBullet->rc, D2DRenderer::DefaultBrush::White);
		}
	}
}

void ammocondaBullet::bulletFire1(float x, float y, float playerX, float playerY)
{
	for (int i = 0; i < 3; i++)
	{
		//총알의 총 갯수보다 크면 더이상 발사 x
		if (BULLETMAX < _vAmmocondaBullet1.size()) return;

		tagAmmocondaBullet bullet;
		ZeroMemory(&bullet, sizeof(tagAmmocondaBullet));
		bullet.img = IMAGEMANAGER->findImage("ammocondaBullet1");
		bullet.speed = 5.0f;
		bullet.angle = GetAngle(x, y, playerX, playerY) + (i * 0.4f) - 0.4f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.width = 18;
		bullet.height = 18;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		//총알의 정보를 벡터에 담아준다
		_vAmmocondaBullet1.push_back(bullet);
	}
}

void ammocondaBullet::bulletMove1()
{
	for (_viAmmocondaBullet1 = _vAmmocondaBullet1.begin(); _viAmmocondaBullet1 != _vAmmocondaBullet1.end();)
	{
		//총알이동
		_viAmmocondaBullet1->x += cosf(_viAmmocondaBullet1->angle) * _viAmmocondaBullet1->speed;
		_viAmmocondaBullet1->y += -sinf(_viAmmocondaBullet1->angle) * _viAmmocondaBullet1->speed;
		_viAmmocondaBullet1->rc = RectMakeCenter(_viAmmocondaBullet1->x, _viAmmocondaBullet1->y, _viAmmocondaBullet1->img->getWidth(), _viAmmocondaBullet1->img->getHeight());

		//예외처리
		if (_viAmmocondaBullet1->rc.right < 0 || _viAmmocondaBullet1->rc.left > 2000 || _viAmmocondaBullet1->rc.bottom < 0 || _viAmmocondaBullet1->rc.top > 1000)
		{
			_viAmmocondaBullet1 = _vAmmocondaBullet1.erase(_viAmmocondaBullet1);
		}
		else ++_viAmmocondaBullet1;
	}
}

void ammocondaBullet::bulletFire2(float x, float y, float playerX, float playerY)
{
	for (int i = 0; i < 1; i++)
	{
		if (BULLETMAX < _vAmmocondaBullet2.size()) return;
		tagAmmocondaBullet bullet;
		ZeroMemory(&bullet, sizeof(tagAmmocondaBullet));
		bullet.img = IMAGEMANAGER->findImage("ammocondaBullet2");
		bullet.speed = 7.0f;
		bullet.angle = GetAngle(x, y, playerX, playerY);
		bullet.currentX = 0;
		bullet.x = x;
		bullet.y = y;
		bullet.width = 22;
		bullet.height = 22;
		bullet.isWave = 4;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth() / bullet.img->getMaxFrameX(), bullet.img->getHeight());
		bullet.centerX = (bullet.rc.right - bullet.rc.left) / 2;
		bullet.centerY = (bullet.rc.bottom - bullet.rc.top) / 2;
		_vAmmocondaBullet2.push_back(bullet);
	}
}

void ammocondaBullet::bulletMove2()
{
	_count++;
	for (_viAmmocondaBullet2 = _vAmmocondaBullet2.begin(); _viAmmocondaBullet2 != _vAmmocondaBullet2.end();)
	{
		//앵글값 예외처리(마이너스 혹은 PI2 초과 값 방지)
		if (_viAmmocondaBullet2->angle >= PI2) _viAmmocondaBullet2->angle -= PI2;
		if (_viAmmocondaBullet2->angle <= 0) _viAmmocondaBullet2->angle += PI2;

		//웨이브효과 
		_viAmmocondaBullet2->isWave++;
		if (_viAmmocondaBullet2->isWave < 10)_viAmmocondaBullet2->angle += 0.05f;
		else if (_viAmmocondaBullet2->isWave >= 10 && _viAmmocondaBullet2->isWave < 20)_viAmmocondaBullet2->angle -= 0.05f;
		else _viAmmocondaBullet2->isWave = 0;
		//총알 이동
		_viAmmocondaBullet2->x += cosf(_viAmmocondaBullet2->angle) * _viAmmocondaBullet2->speed;
		_viAmmocondaBullet2->y += -sinf(_viAmmocondaBullet2->angle) * _viAmmocondaBullet2->speed;
		_viAmmocondaBullet2->rc = RectMakeCenter(_viAmmocondaBullet2->x, _viAmmocondaBullet2->y, _viAmmocondaBullet2->img->getWidth() / _viAmmocondaBullet2->img->getMaxFrameX(), _viAmmocondaBullet2->img->getHeight());

		//총알 이미지 프레임
		if (_count % 5 == 0)
		{
			_viAmmocondaBullet2->currentX++;
			if (_viAmmocondaBullet2->currentX >= _viAmmocondaBullet2->img->getMaxFrameX()) 	_viAmmocondaBullet2->currentX = 0;
			_count = 0;
		}
		//예외처리
		if (_viAmmocondaBullet2->rc.right < 0 || _viAmmocondaBullet2->rc.left > 2000 || _viAmmocondaBullet2->rc.bottom < 0 || _viAmmocondaBullet2->rc.top > 1000)
		{
			_viAmmocondaBullet2 = _vAmmocondaBullet2.erase(_viAmmocondaBullet2);
		}
		else ++_viAmmocondaBullet2;
	}
}

void ammocondaBullet::bulletFirePot(float x, float y, float playerX, float playerY)
{

	if (BULLETMAX < _vPotBullet.size()) return;

	tagAmmocondaBullet bullet;
	ZeroMemory(&bullet, sizeof(tagAmmocondaBullet));
	bullet.img = IMAGEMANAGER->findImage("potBullet");
	bullet.speed = 10.0f;
	bullet.angle = GetAngle(x, y, playerX, playerY);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.width = 18;
	bullet.height = 18;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
	_vPotBullet.push_back(bullet);
}

void ammocondaBullet::bulletMovePot()
{
	for (_viPotBullet = _vPotBullet.begin(); _viPotBullet != _vPotBullet.end();)
	{
		//총알이동
		_viPotBullet->x += cosf(_viPotBullet->angle) * _viPotBullet->speed;
		_viPotBullet->y += -sinf(_viPotBullet->angle) * _viPotBullet->speed;
		_viPotBullet->rc = RectMakeCenter(_viPotBullet->x, _viPotBullet->y, _viPotBullet->img->getWidth(), _viPotBullet->img->getHeight());

		//예외처리
		if (_viPotBullet->rc.right < 0 || _viPotBullet->rc.left > 2000 || _viPotBullet->rc.bottom < 0 || _viPotBullet->rc.top > 1000)
		{
			_viPotBullet = _vPotBullet.erase(_viPotBullet);
		}
		else ++_viPotBullet;
	}
}
