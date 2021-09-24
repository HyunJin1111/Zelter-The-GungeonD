#include "stdafx.h"
#include "quickSlot.h"

HRESULT quickSlot::init()
{
	_quickSlotBack.rc = RectMake(0, WINSIZEY - 91, 480, 64);
	_quickSlotBack.img = IMAGEMANAGER->findImage("quickslotback");

	_quickSlotFront.rc = RectMake(75, WINSIZEY - 35,358, 32);
	_quickSlotFront.img = IMAGEMANAGER->findImage("quickslotfront");

	for (int i = 0; i < QUICKSLOTBASEMAX; i++)
	{
		_quickSlotBase[i].rc = RectMake(65*(1+i) +16, WINSIZEY-78, 61, 55);
		_quickSlotBase[i].img = IMAGEMANAGER->findImage("quickslotbase");
		_quickSlotBase[i].isOn = false;
	}
	_quickSlotBase[0].isOn = true;


	_quickSlotBase[0].gunimg = IMAGEMANAGER->findImage("GUN1");
	_quickSlotBase[1].gunimg = IMAGEMANAGER->findImage("GUN2");
	_quickSlotBase[2].gunimg = IMAGEMANAGER->findImage("GUN3");
	_quickSlotBase[3].gunimg = IMAGEMANAGER->findImage("GUN4");
	_quickSlotBase[4].gunimg = IMAGEMANAGER->findImage("GUN5");

	return S_OK;
}

void quickSlot::release()
{

}

void quickSlot::update()
{

	for (int i = 0; i < QUICKSLOTBASEMAX; i++)
	{
		if (_quickSlotBase[i].isOn)
		{
			if (_quickSlotBase[i].rc.top > WINSIZEY - 77)
			{
				_quickSlotBase[i].rc.bottom -= 5;
				_quickSlotBase[i].rc.top -= 5;
				
			}
		}
		else
		{
			_quickSlotBase[i].rc = RectMake(65 * (1 + i) + 16, WINSIZEY - 67, 61, 55);
		
		}
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_quickSlotBase[0].isOn = true;
		for (int i = 1; i < 5; i++)
		{
			_quickSlotBase[i].isOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotBase[1].isOn = true;

		_quickSlotBase[0].isOn = false;
		for (int i = 2; i < 5; i++)
		{
			_quickSlotBase[i].isOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotBase[2].isOn = true;
		_quickSlotBase[0].isOn = false;
		_quickSlotBase[1].isOn = false;
		for (int i = 3; i < 5; i++)
		{
			_quickSlotBase[i].isOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotBase[3].isOn = true;
		_quickSlotBase[0].isOn = false;
		_quickSlotBase[1].isOn = false;
		_quickSlotBase[2].isOn = false;
		for (int i = 4; i < 5; i++)
		{
			_quickSlotBase[i].isOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotBase[4].isOn = true;
		for (int i = 0; i < 4; i++)
		{
			_quickSlotBase[i].isOn = false;
		}
	}
}

void quickSlot::render()
{
	_quickSlotBack.img->render(_quickSlotBack.rc.left, _quickSlotBack.rc.top);

	for (int i = 0; i < QUICKSLOTBASEMAX; i++)
	{
		_quickSlotBase[i].img->render(_quickSlotBase[i].rc.left, _quickSlotBase[i].rc.top);
	}
	_quickSlotBase[0].gunimg->render(_quickSlotBase[0].rc.left + 25, _quickSlotBase[0].rc.top + 20);
	_quickSlotBase[1].gunimg->render(_quickSlotBase[1].rc.left + 5, _quickSlotBase[1].rc.top + 20);
	_quickSlotBase[2].gunimg->render(_quickSlotBase[2].rc.left + 10, _quickSlotBase[2].rc.top + 20);
	_quickSlotBase[3].gunimg->render(_quickSlotBase[3].rc.left + 20, _quickSlotBase[3].rc.top + 20);
	_quickSlotBase[4].gunimg->render(_quickSlotBase[4].rc.left + 5, _quickSlotBase[4].rc.top + 20);


	_quickSlotFront.img->render(_quickSlotFront.rc.left, _quickSlotFront.rc.top);


}
