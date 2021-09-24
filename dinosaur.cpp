#include "stdafx.h"
#include "dinosaur.h"

dinosaur::dinosaur()
{
}

dinosaur::~dinosaur()
{
}

HRESULT dinosaur::init()
{
	IMAGEMANAGER->addFrameImage("dinosaurIdle", L"dinosaur/dinosaurIdle_1_1.png", 1, 2);
	IMAGEMANAGER->addFrameImage("dinosaurWalk", L"dinosaur/dinosaurWalk_2_2.png", 2, 2);
	IMAGEMANAGER->addFrameImage("dinosaurAttack", L"dinosaur/dinosaurAttack_2_2.png", 2, 2);
	IMAGEMANAGER->addFrameImage("dinosaurDeath", L"dinosaur/dinosaurDeath_2_2.png", 2, 2);
	_dialogue = new dialogue;

	return S_OK;
}

void dinosaur::release()
{
}

void dinosaur::update()
{

}

void dinosaur::render()
{
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			D2DRENDER->DrawRectangle(_viDinosaur->rc, D2DRenderer::DefaultBrush::White);
		}
		_viDinosaur->img->frameRender2(_viDinosaur->rc.left, _viDinosaur->rc.top, _viDinosaur->currentFrameX, _viDinosaur->currentFrameY);

		for (int i = 0; i < 2; ++i)
		{
			D2DRENDER->DrawRectangle(_viDinosaur->tileIdx[i], D2DDEFAULTBRUSH::Red);
		}
	}

	_dialogue->render();
}

void dinosaur::setEnemy()
{
	for (int i = 0; i < 1; i++)
	{
		

		tagDinosaur dinosaur;
		ZeroMemory(&dinosaur, sizeof(tagDinosaur));
		dinosaur.img = IMAGEMANAGER->findImage("dinosaurIdle");
		dinosaur.speed = 2.0f;
		dinosaur.angle = RND->getFromFloatTo(0, PI2);
		dinosaur.x = RND->getFromIntTo(0, TILEX * TILESIZEX);
		dinosaur.y = RND->getFromIntTo(0, TILEY * TILESIZEY);
		dinosaur.currentHp = dinosaur.maxHp = 100;
		dinosaur.currentFrameX = dinosaur.currentFrameY = 0;
		dinosaur.count = dinosaur.changeCount = 0;
		dinosaur.state = DINOSAUR_IDLE;
		//angle에 따라 방향지정
		if (dinosaur.angle > 0 && dinosaur.angle <= PI / 2 || dinosaur.angle >= PI + PI / 2 && dinosaur.angle <= PI2)
			dinosaur.direction_img = DINOSAUR_RIGHT;
		else if (dinosaur.angle > PI / 2 && dinosaur.angle <= PI + PI / 2)
			dinosaur.direction_img = DINOSAUR_LEFT;
		dinosaur.rc = RectMakeCenter(dinosaur.x, dinosaur.y, dinosaur.img->getWidth() / dinosaur.img->getMaxFrameX(), dinosaur.img->getHeight() / dinosaur.img->getMaxFrameY());

		_vDinosaur.push_back(dinosaur);
	}
}

void dinosaur::dinoMove(float x, float y)
{


	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		
		//공룡 앵글값에 따른 방향
		//오른쪽 정면
		if (_viDinosaur->angle < PI / 8 && _viDinosaur->angle > 0 ||
			PI + (PI / 8) * 7 < _viDinosaur->angle && PI2 > _viDinosaur->angle)					_viDinosaur->direction = 0;
		//위쪽 정면
		if (_viDinosaur->angle < (PI / 8) * 5 && (PI / 8) * 3 < _viDinosaur->angle)					_viDinosaur->direction = 2;
		//왼쪽 정면	
		if (_viDinosaur->angle < PI + (PI / 8) && (PI / 8) * 7 < _viDinosaur->angle)				_viDinosaur->direction = 1;
		//아래쪽 정면
		if (_viDinosaur->angle < PI + (PI / 8) * 5 && PI + (PI / 8) * 3 < _viDinosaur->angle)		_viDinosaur->direction = 3;
		//오른쪽 대각선 위
		if (_viDinosaur->angle < (PI / 8) * 3 && PI / 8 < _viDinosaur->angle)						_viDinosaur->direction = 5;
		//왼쪽 대각선 위
		if (_viDinosaur->angle < (PI / 8) * 7 && (PI / 8) * 5 < _viDinosaur->angle)					_viDinosaur->direction = 4;
		//왼쪽 대각선 아래
		if (_viDinosaur->angle < PI + (PI / 8) * 3 && PI + (PI / 8) < _viDinosaur->angle)			_viDinosaur->direction = 7;
		//오른쪽 대각선 아래
		if (_viDinosaur->angle < PI + (PI / 8) * 7 && PI + (PI / 8) * 5 < _viDinosaur->angle)		_viDinosaur->direction = 6;

		//랜덤값에 따라 IDLE 혹은 WALK 상태로 변경
		_viDinosaur->changeCount++;
		if (_viDinosaur->changeCount >= RND->getFromIntTo(100, 200))
		{
			_viDinosaur->angle = RND->getFromFloatTo(0, PI2);

			int changeRand = RND->getFromIntTo(0, 2);

			switch (changeRand)
			{
			case 0:
				_viDinosaur->state = DINOSAUR_IDLE;
				break;
			case 1:
				_viDinosaur->state = DINOSAUR_WALK;
				break;
			}
			_viDinosaur->changeCount = 0;
		}
		//WALK 상태인 경우 speed 값에 따라 이동
		if (_viDinosaur->state == DINOSAUR_WALK)
		{
			_viDinosaur->x += cosf(_viDinosaur->angle) * _viDinosaur->speed;
			_viDinosaur->y += -sinf(_viDinosaur->angle) * _viDinosaur->speed;

		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) < 300 && GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) > 30)
		{
			_viDinosaur->angle = GetAngle(_viDinosaur->x, _viDinosaur->y, x, y);
			_viDinosaur->speed = 3.0f;
		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) <= 30)
		{
			_viDinosaur->state = DINOSAUR_ATTACK;
			_viDinosaur->angle = GetAngle(_viDinosaur->x, _viDinosaur->y, x, y);
		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) > 300)
		{
			_viDinosaur->state = DINOSAUR_WALK;
			_viDinosaur->speed = 2.0f;
		}
		if (_viDinosaur->currentHp <= 0)
		{
			_viDinosaur->state = DINOSAUR_DEATH;

		}
		//angle에 따라 이미지의 방향지정
		if (_viDinosaur->angle > 0 && _viDinosaur->angle <= PI / 2 || _viDinosaur->angle >= PI + PI / 2 && _viDinosaur->angle <= PI2)_viDinosaur->direction_img = DINOSAUR_RIGHT;
		else if (_viDinosaur->angle > PI / 2 && _viDinosaur->angle <= PI + PI / 2)_viDinosaur->direction_img = DINOSAUR_LEFT;
		//angle 예외처리
		if (_viDinosaur->angle >= PI2)_viDinosaur->angle -= PI2;
		if (_viDinosaur->angle <= 0) _viDinosaur->angle += PI2;
		//화면 밖 예외처리
		if (_viDinosaur->rc.left < 0) _viDinosaur->x = (_viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX()) / 2;
		if (_viDinosaur->rc.right > TILEX * TILESIZEX) _viDinosaur->x = TILEX * TILESIZEX - (_viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX()) / 2;
		if (_viDinosaur->rc.top < 0) _viDinosaur->y = (_viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY()) / 2;
		if (_viDinosaur->rc.bottom > TILEY * TILESIZEY) _viDinosaur->y = TILEY * TILESIZEY - (_viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY()) / 2;
		//렉트 
		_viDinosaur->rc = RectMakeCenter(_viDinosaur->x, _viDinosaur->y, _viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX(), _viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY());
	}

	_dialogue->update();
	tileCheck();
}

void dinosaur::dinoState()
{
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		//이미지 프레임 전환
		_viDinosaur->count++;
		if (_viDinosaur->count % 15 == 0)
		{
			_viDinosaur->currentFrameX++;
			switch (_viDinosaur->direction_img)
			{
			case DINOSAUR_RIGHT:
				_viDinosaur->currentFrameY = 0;
				break;
			case DINOSAUR_LEFT:
				_viDinosaur->currentFrameY = 1;
				break;
			}
		}
		//상태별 예외처리
		switch (_viDinosaur->state)
		{
			//IDLE 상태일 경우
		case DINOSAUR_IDLE:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurIdle");
			if (_viDinosaur->currentFrameX > 0)_viDinosaur->currentFrameX = 0;
			break;
			//WALK 상태일 경우
		case DINOSAUR_WALK:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurWalk");
			if (_viDinosaur->currentFrameX > 1)_viDinosaur->currentFrameX = 0;
			break;
			//ATTACK 상태일 경우
		case DINOSAUR_ATTACK:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurAttack");
			if (_viDinosaur->currentFrameX > 1)
			{
				//공격할 때 대사 출력신호 보내줍니다
				_dialogue->speechCreate(DINOSAUR, _viDinosaur->x - 60, _viDinosaur->y - 60);

				_viDinosaur->currentFrameX = 0;
			}
			break;
			//DEATH 상태일 경우
		case DINOSAUR_DEATH:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurDeath");
			if (_viDinosaur->currentFrameX > 1)
			{
				_viDinosaur->currentFrameX = 0;
				_viDinosaur = _vDinosaur.erase(_viDinosaur);
			}
			break;
		}
	}
}

void dinosaur::tileCheck()
{
	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성


	int	tileIndex[2];	//타일 검출에 필요한 인덱스
	int tileX, tileY;	//공룡이 밟고 있는 타일의 인덱스
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		//가상의 판정렉트에 현재 렉트를 대입해주자
		rcCollision = _viDinosaur->rc;

		rcCollision = RectMakeCenter(_viDinosaur->x, _viDinosaur->y, _viDinosaur->img->getFrameWidth(), _viDinosaur->img->getFrameHeight());

		tileX = rcCollision.left / 48;
		tileY = rcCollision.top / 48;

		switch (_viDinosaur->direction)
		{
		case 4:
			tileIndex[0] = (tileX - 1) + (tileY*TILEX);
			tileIndex[1] = tileX + (tileY*TILEX);
			break;
		case 2:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 1:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1)*TILEX;
			break;
		case 0:
			tileIndex[0] = tileX + 1 + tileY * TILEX;
			tileIndex[1] = (tileX + 1) + (tileY + 1) * TILEX;
			break;
		case 7:
			tileIndex[0] = (tileX - 1) + (tileY * TILEX);
			tileIndex[1] = (tileX - 1) + (tileY + 1) * TILEX;
			break;
		case 3:
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = (tileX + 1) + (tileY + 1) * TILEX;
			break;
		case 6:
			tileIndex[0] = tileX + 1 + (tileY * TILEX);
			tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
			break;
		}

		for (int i = 0; i < 2; ++i)
		{
			RECT rc;

			if (/*((_inGame->getTileAtt()[tileIndex[i]] == NONEMOVE)) &&*/
				IntersectRect(&rc, &_inGame->getTile()[tileIndex[i]].checkRect, &rcCollision))
			{
				switch (_viDinosaur->direction)
				{
				case 1:
					_viDinosaur->rc.left = _inGame->getTile()[tileIndex[i]].checkRect.right;
					_viDinosaur->rc.right = _viDinosaur->rc.left + _viDinosaur->img->getFrameWidth();

					_viDinosaur->x = (_viDinosaur->rc.left + _viDinosaur->rc.right) / 2;

					break;
				case 2:
					_viDinosaur->rc.top = _inGame->getTile()[tileIndex[i]].checkRect.bottom;
					_viDinosaur->rc.bottom = _viDinosaur->rc.top + _viDinosaur->img->getFrameHeight();

					_viDinosaur->y = (_viDinosaur->rc.top + _viDinosaur->rc.bottom) / 2;
					break;
				case 0:
					_viDinosaur->rc.right = _inGame->getTile()[tileIndex[i]].checkRect.left;
					_viDinosaur->rc.left = _viDinosaur->rc.right - _viDinosaur->img->getFrameWidth();

					_viDinosaur->x = (_viDinosaur->rc.left + _viDinosaur->rc.right) / 2;
					break;
				case 3:
					_viDinosaur->rc.bottom = _inGame->getTile()[tileIndex[i]].checkRect.top;
					_viDinosaur->rc.top = _viDinosaur->rc.bottom - _viDinosaur->img->getFrameHeight();

					_viDinosaur->y = (_viDinosaur->rc.top + _viDinosaur->rc.bottom) / 2;
					break;
				}
			}
		}
		for (int i = 0; i < 2; ++i)
		{
			_viDinosaur->tileIdx[i] = RectMake(_inGame->getTile()[tileIndex[i]].rc.left, _inGame->getTile()[tileIndex[i]].rc.top, 48, 48);
		}

		_viDinosaur->rc = RectMakeCenter(_viDinosaur->x, _viDinosaur->y, _viDinosaur->img->getFrameWidth(), _viDinosaur->img->getFrameHeight());
	}


}
