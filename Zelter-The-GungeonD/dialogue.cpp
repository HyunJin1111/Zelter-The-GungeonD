#include "stdafx.h"
#include "dialogue.h"

HRESULT dialogue::init()
{
	return S_OK;
}

void dialogue::release(int index)
{
	_vSpeech.erase(_vSpeech.begin() + index);
}

void dialogue::update()
{
	for (int i = 0; i < _vSpeech.size(); i++)
	{
		_vSpeech[i].speechCount++;
		if (_vSpeech[i].speechCount >= _vSpeech[i].speechEnd) release(i);
	}
}

void dialogue::render()
{
	for (int i = 0; i < _vSpeech.size(); i++)
	{
		_vSpeech[i].img->render(_vSpeech[i].x - CAMERAMANAGER->getX(), _vSpeech[i].y - CAMERAMANAGER->getY());

		D2DRENDER->RenderTextField(_vSpeech[i].x - CAMERAMANAGER->getX(), _vSpeech[i].y - CAMERAMANAGER->getY(), ConvertCtoWC(_vSpeech[i].speech),
			D2D1::ColorF::Black, 10, 94, 34, 1,
			DWRITE_TEXT_ALIGNMENT_CENTER);
	}
}

void dialogue::speechCreate(int enemyName, float x, float y)
{
	IMAGEMANAGER->addImage("speechBubble", L"UI/speechBubble.png");

	tagSpeech speech;
	
	if (enemyName == 0) speech.enemyName = "피쉬맨";
	else if (enemyName == 1) speech.enemyName = "다이노소어";
	speech.x = x;
	speech.y = y;
	speech.speechCount = 0;
	speech.speechEnd = 20;
	speech.img = IMAGEMANAGER->findImage("speechBubble");
	speech.maxWidth = 100;
	speech.rndSpeech = RND->getFromIntTo(0, 2);
	char speechNumber[64];
	speechNumber[32] = _itoa_s(speech.rndSpeech, speechNumber, sizeof(speechNumber), 10);
	speech.speech = INIDATA->loadDataString("몬스터대사", speech.enemyName, speechNumber);

	_vSpeech.push_back(speech);
}
