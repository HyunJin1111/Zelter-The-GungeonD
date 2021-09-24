#include "stdafx.h"
#include "niflheimAttack3.h"

#include "niflheim.h"

#include "niflheimDie.h"
#include "niflheimIdle.h"

state * niflheimAttack3::inputHandle(niflheim * niflheim)
{
	if (_stateEnd) return new niflheimIdle();
	if (niflheim->getNiflheim().currentHP <= 0) return new niflheimDie();

	return nullptr;
}

void niflheimAttack3::update(niflheim * niflheim)
{
	_count++;
	if (_count % 12 == 0)
	{
		if (_currentFrameY == 0)
		{
			_currentFrameX++;
			if (_currentFrameX >= niflheim->getNiflheim().img->getMaxFrameX())
			{
				_stateEnd = true;

				_targetX = niflheim->getPlayer()->getPlayer().x;
				_targetY = niflheim->getPlayer()->getPlayer().y;

				niflheim->getNiflheim().icePillar->fireBullet1(_targetX, _targetY, _icePillar1);
				niflheim->getNiflheim().icePillar->fireBullet2(_targetX, _targetY, _icePillar2);
				SOUNDMANAGER->play("니플헤임공격2");
			}
		}
		else
		{
			_currentFrameX--;
			if (_currentFrameX <= 0)
			{
				_stateEnd = true;

				_targetX = niflheim->getPlayer()->getPlayer().x;
				_targetY = niflheim->getPlayer()->getPlayer().y;

				niflheim->getNiflheim().icePillar->fireBullet1(_targetX, _targetY, _icePillar1);
				niflheim->getNiflheim().icePillar->fireBullet2(_targetX, _targetY, _icePillar2);
				SOUNDMANAGER->play("니플헤임공격2");
			}
		}
	}
}

void niflheimAttack3::enter(niflheim * niflheim)
{
	SOUNDMANAGER->addSound("니플헤임공격2", "sound/니플헤임공격2.wav", false, false);
	_currentStateName = "niflheimIcePillar";
	niflheim->setImg(IMAGEMANAGER->findImage("niflheimAttack"));
	if (niflheim->getNiflheim().direction == 0)
	{
		_currentFrameY = 0;
		_currentFrameX = 0;
	}
	else
	{
		_currentFrameY = 1;
		_currentFrameX = 10;
	}
	_count = 0;
	_stateEnd = false;

	_icePillar1 = RND->getFromIntTo(0, 3);
	_icePillar2 = RND->getFromIntTo(0, 3);
	if (_icePillar1 == _icePillar2) _icePillar2 = RND->getFromIntTo(0, 3);


}

void niflheimAttack3::exit(niflheim * niflheim)
{
}

void niflheimAttack3::render(niflheim * niflheim)
{
	niflheim->getNiflheim().img->frameRender2(niflheim->getNiflheim().rc.left, niflheim->getNiflheim().rc.top, _currentFrameX, _currentFrameY);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		D2DRENDER->DrawRectangle(niflheim->getNiflheim().rc, D2DDEFAULTBRUSH::Red);
	}
}

void niflheimAttack3::iceBulletFire(niflheim* niflheim, float targetX, float targetY)
{
	//	for (int i = 0; i < 100; i++)
	//	{
	//		/*_bulletCount++;
	//	if (_bulletCount % 10 == 0 && _fireBullet <= 20)
	//	{
	//*/		if (i % 5 == 0)
	//		{
	//			niflheim->getNiflheim().icePillar->fireBullet1(_targetX, _targetY, _icePillar1);
	//			niflheim->getNiflheim().icePillar->fireBullet2(_targetX, _targetY, _icePillar2);
	//		}
	//		
	//		/*_fireBullet++;
	//	}*/
	//	}

}
