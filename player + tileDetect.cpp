#include "stdafx.h"
#include "player.h"

void player::tileDetect(string sceneName)
{
	if (sceneName == "openWorld")
	{

		RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


		int	tileNormal[2];	//타일 검출에 필요한 인덱스
		int	tileTriple[3];	//타일 검출에 필요한 인덱스
		int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

		//가상의 판정렉트에 현재 렉트를 대입해주자
		rcCollision = _player.rc;

		rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

		//STEP 3
		////판정렉트를 사알짝 깍아주자
		/*rcCollision.left += 4;
		rcCollision.top += 4;
		rcCollision.right -= 4;
		rcCollision.bottom -= 4;*/

		tileX = rcCollision.left / 48;
		tileY = rcCollision.top / 48;


		//STEP 04
		//가장 메인이지 싶으요
		//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

		/*
		-----------------
		4	|	2	|	5
		-----------------
		1	| player|	0
		-----------------
		7	|	3	|	6
		*/
		switch (_player.movingDirection)
		{
		case 4:
			tileTriple[0] = (tileX) + (tileY*TILEX);
			tileTriple[1] = tileX + (tileY+1)*TILEX;
			tileTriple[2] = tileX+1 + (tileY)*TILEX;
			break;
		case 2:
			tileNormal[0] = tileX + (tileY * TILEX);
			tileNormal[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileTriple[0] = tileX+(tileY * TILEX);
			tileTriple[1] = tileX + 1 + (tileY * TILEX);
			tileTriple[2] = tileX+1  + (tileY+1) * TILEX;
			break;
		case 1:
			tileNormal[0] = tileX + tileY * TILEX;
			tileNormal[1] = tileX + (tileY + 1)*TILEX;
break;
		case 0:
			tileNormal[0] = tileX + 1 + tileY * TILEX;
			tileNormal[1] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 7:
			tileTriple[0] = (tileX)+(tileY*TILEX);
			tileTriple[1] = tileX + (tileY + 1) * TILEX;
			tileTriple[2] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 3:
			tileNormal[0] = tileX + (tileY + 1) * TILEX;
			tileNormal[1] = tileX + 1 + (tileY + 1)*TILEX;
			break;
		case 6:
			tileTriple[0] = tileX + 1 + (tileY * TILEX);
			tileTriple[1] = (tileX + 1 + (tileY + 1) * TILEX);
			tileTriple[2] = tileX + (tileY + 1) * TILEX;
			break;
		}
		cout << _player.movingDirection << endl;

		if (_player.movingDirection == 1 || _player.movingDirection == 2 || _player.movingDirection == 0 || _player.movingDirection == 3)
		{
			for (int i = 0; i < 2; ++i)
			{
				//if (_inGame->getTileAtt()[tileIndex[i]] != NONEMOVE)continue;
				RECT rc;

				if (((_inGame->getTileAttribute()[tileNormal[i]] == NONEMOVE)) &&
					IntersectRect(&rc, &_inGame->getTile()[tileNormal[i]].checkRect, &rcCollision))
				{
					switch (_player.movingDirection)
					{
					case 1:
						_player.rc.left = _inGame->getTile()[tileNormal[i]].rc.right;
						_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

						_player.x = (_player.rc.left + _player.rc.right) / 2;

						break;
					case 2:
						_player.rc.top = _inGame->getTile()[tileNormal[i]].rc.bottom;
						_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					case 0:
						_player.rc.right = _inGame->getTile()[tileNormal[i]].rc.left;
						_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

						_player.x = (_player.rc.left + _player.rc.right) / 2;
						break;
					case 3:
						_player.rc.bottom = _inGame->getTile()[tileNormal[i]].rc.top;
						_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;

						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					}
				}
				_rcc[i] = _inGame->getTile()[tileNormal[i]].rc;

			}
		}

		if (_player.movingDirection == 4 || _player.movingDirection == 5 || _player.movingDirection == 7 || _player.movingDirection == 6)
		{
			for (int i = 0; i < 3; ++i)
			{
				//if (_inGame->getTileAtt()[tileIndex[i]] != NONEMOVE)continue;
				RECT rc;

				if (((_inGame->getTileAttribute()[tileTriple[i]] == NONEMOVE)) &&
					IntersectRect(&rc, &_inGame->getTile()[tileTriple[i]].checkRect, &rcCollision))
				{
					switch (_player.movingDirection)
					{
					case 4:
						if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
						{
							if (_inGame->getTileAttribute()[tileTriple[1]] == NONEMOVE)
							{
								_player.rc.left = _inGame->getTile()[tileTriple[1]].rc.right;
								_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
							}
							else if (_inGame->getTileAttribute()[tileTriple[2]] == NONEMOVE)
							{
								_player.rc.top = _inGame->getTile()[tileTriple[2]].rc.bottom;
								_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
							}
							else
							{
								_player.rc.left = _inGame->getTile()[tileTriple[1]].rc.right;
								_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
								_player.rc.top = _inGame->getTile()[tileTriple[2]].rc.bottom;
								_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
							}
						}
						else if (_inGame->getTileAttribute()[tileTriple[1]] == NONEMOVE)
						{
								_player.rc.left = _inGame->getTile()[tileTriple[1]].rc.right;
								_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
						}
						else
						{
							_player.rc.top = _inGame->getTile()[tileTriple[2]].rc.bottom;
							_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
						}
						_player.x = (_player.rc.right + _player.rc.left) / 2;
						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					case 5:
						if (_inGame->getTileAttribute()[tileTriple[1]] == NONEMOVE)
						{
							if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
							{
								_player.rc.top = _inGame->getTile()[tileTriple[0]].rc.bottom;
								_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
							}
							else if (_inGame->getTileAttribute()[tileTriple[2]] == NONEMOVE)
							{
								_player.rc.right = _inGame->getTile()[tileTriple[2]].rc.left;
								_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
							}
							else
							{
								_player.rc.top = _inGame->getTile()[tileTriple[0]].rc.bottom;
								_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
								_player.rc.right = _inGame->getTile()[tileTriple[2]].rc.left;
								_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
							}
						}
						else if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
						{
							_player.rc.top = _inGame->getTile()[tileTriple[0]].rc.bottom;
							_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();
						}
						else
						{
							_player.rc.right = _inGame->getTile()[tileTriple[2]].rc.left;
							_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
						}
						_player.x = (_player.rc.right + _player.rc.left) / 2;
						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					case 7:
						if (_inGame->getTileAttribute()[tileTriple[1]] == NONEMOVE)
						{
							if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
							{
								_player.rc.left = _inGame->getTile()[tileTriple[0]].rc.right;
								_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
							}
							else if (_inGame->getTileAttribute()[tileTriple[2]] == NONEMOVE)
							{
								_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
								_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
							}
							else
							{
								_player.rc.left = _inGame->getTile()[tileTriple[0]].rc.right;
								_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
								_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
								_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
							}
						}
						else if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
						{
							_player.rc.left = _inGame->getTile()[tileTriple[0]].rc.right;
							_player.rc.right = _player.rc.left + _player.img->getFrameWidth();
						}
						else
						{
							_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
							_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
						}
						_player.x = (_player.rc.right + _player.rc.left) / 2;
						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					case 6:
						if (_inGame->getTileAttribute()[tileTriple[1]] == NONEMOVE)
						{
							if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
							{
								_player.rc.right = _inGame->getTile()[tileTriple[0]].rc.left;
								_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
							}
							else if (_inGame->getTileAttribute()[tileTriple[2]] == NONEMOVE)
							{
								_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
								_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
							}
							else
							{
								_player.rc.right = _inGame->getTile()[tileTriple[0]].rc.left;
								_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
								_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
								_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
							}
						}
						else if (_inGame->getTileAttribute()[tileTriple[0]] == NONEMOVE)
						{
							_player.rc.right = _inGame->getTile()[tileTriple[0]].rc.left;
							_player.rc.left = _player.rc.right - _player.img->getFrameWidth();
						}
						else
						{
							_player.rc.bottom = _inGame->getTile()[tileTriple[2]].rc.top;
							_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight()+11;
						}
						_player.x = (_player.rc.right + _player.rc.left) / 2;
						_player.y = (_player.rc.top + _player.rc.bottom) / 2;
						break;
					}
				}
				_rcc2[i] = _inGame->getTile()[tileTriple[i]].rc;
			}
		}
		//_player.rc = rcCollision;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "bulletKing")
	{
		RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


		int	tileIndex[2];	//타일 검출에 필요한 인덱스
		int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

		//가상의 판정렉트에 현재 렉트를 대입해주자
		rcCollision = _player.rc;

		rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

		//STEP 3
		////판정렉트를 사알짝 깍아주자
		/*rcCollision.left += 4;
		rcCollision.top += 4;
		rcCollision.right -= 4;
		rcCollision.bottom -= 4;*/

		tileX = rcCollision.left / 64;
		tileY = rcCollision.top / 64;


		//STEP 04
		//가장 메인이지 싶으요
		//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

		/*
		-----------------
		4	|	2	|	5
		-----------------
		1	| player|	0
		-----------------
		7	|	3	|	6
		*/
		switch (_player.movingDirection)
		{
		case 4:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX + (tileY*TILEY);
			break;
		case 2:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileIndex[0] = (tileX)+(tileY * TILEX);
			tileIndex[1] = tileX + 1 + (tileY * TILEX);
			break;
		case 1:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1)*TILEX;
			break;
		case 0:
			tileIndex[0] = tileX + 1 + tileY * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 7:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
			break;
		case 3:
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
			break;
		case 6:
			tileIndex[0] = tileX + 1 + (tileY * TILEX);
			tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
			break;
		}

		for (int i = 0; i < 2; ++i)
		{
			RECT rc;

			if (((_bulletKingMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
				IntersectRect(&rc, &_bulletKingMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
			{
				switch (_player.movingDirection)
				{
				case 1:
					_player.rc.left = _bulletKingMap->getTile()[tileIndex[i]].checkRect.right;
					_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;

					break;
				case 2:
					_player.rc.top = _bulletKingMap->getTile()[tileIndex[i]].checkRect.bottom;
					_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				case 0:
					_player.rc.right = _bulletKingMap->getTile()[tileIndex[i]].checkRect.left;
					_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;
					break;
				case 3:
					_player.rc.bottom = _bulletKingMap->getTile()[tileIndex[i]].checkRect.top;
					_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				}
			}
		}
		
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "ammoconda")
	{
	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


	int	tileIndex[2];	//타일 검출에 필요한 인덱스
	int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

	//가상의 판정렉트에 현재 렉트를 대입해주자
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////판정렉트를 사알짝 깍아주자
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 64;
	tileY = rcCollision.top / 64;


	//STEP 04
	//가장 메인이지 싶으요
	//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_ammocondaMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_ammocondaMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _ammocondaMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _ammocondaMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _ammocondaMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _ammocondaMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "eggNyang")
	{
	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


	int	tileIndex[2];	//타일 검출에 필요한 인덱스
	int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

	//가상의 판정렉트에 현재 렉트를 대입해주자
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////판정렉트를 사알짝 깍아주자
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 64;
	tileY = rcCollision.top / 64;


	//STEP 04
	//가장 메인이지 싶으요
	//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_eggNyangMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_eggNyangMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _eggNyangMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _eggNyangMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _eggNyangMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _eggNyangMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "niflheim")
	{
	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


	int	tileIndex[2];	//타일 검출에 필요한 인덱스
	int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

	//가상의 판정렉트에 현재 렉트를 대입해주자
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////판정렉트를 사알짝 깍아주자
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 32;
	tileY = rcCollision.top / 32;
	 

	//STEP 04
	//가장 메인이지 싶으요
	//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_niflheimMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_niflheimMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _niflheimMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _niflheimMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _niflheimMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _niflheimMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}
	
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
}