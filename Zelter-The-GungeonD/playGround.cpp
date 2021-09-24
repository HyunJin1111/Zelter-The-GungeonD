#include "stdafx.h"
#include "playGround.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")


playGround::playGround()
{

}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);;

	_stageManager = new stageManager;
	_stageManager->init();


	return S_OK;
}

//메모리 해제
void playGround::release()
{

}

//연산
void playGround::update()
{
	gameNode::update();

	
	_stageManager->update();

}

//그리기 전용
void playGround::render()
{
	//백버퍼 초기화
	D2DRENDER->BeginRender(D2D1::ColorF::White);


	_stageManager->render();
	CAMERAMANAGER->render();
	TIMEMANAGER->render(_hdc);

	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2DRENDER->EndRender();
}
