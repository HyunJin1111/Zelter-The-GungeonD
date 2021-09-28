#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	sceneSet();

	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	SCENEMANAGER->update();
}

void stageManager::render()
{
	SCENEMANAGER->render();

	
}

void stageManager::sceneSet()
{
	SCENEMANAGER->addScene("title", new testScene);
	//SCENEMANAGER->addScene("mapmap", new mapmap);
	SCENEMANAGER->addScene("openWorld", new inGame);
	SCENEMANAGER->addScene("pick", new characterPick);
	SCENEMANAGER->addScene("bulletKing", new bulletKingBattle);
	SCENEMANAGER->addScene("ammoconda", new ammocondaBattle);
	SCENEMANAGER->addScene("eggNyang", new eggNyangBattle);
	SCENEMANAGER->addScene("niflheim", new niflheimBattle);
	SCENEMANAGER->addScene("loading", new loading);
	SCENEMANAGER->addScene("startTitle", new startTitle);

	SCENEMANAGER->changeScene("startTitle");
}
