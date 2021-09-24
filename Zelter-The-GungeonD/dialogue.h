#pragma once
#include "gameNode.h"
#include <vector>

enum ENEMYNAME
{
	FISHMAN,
	DINOSAUR
};
struct tagSpeech
{
	image*			img;		//말풍선 이미지
	RECT			rc;			//쓸 줄 알았는데 안쓰는 렉트
	const char*		enemyName;	//int 값을 받아서 char로 적 이름 설정
	const char*		speech;		//대사 (여기에 대사가 들어감)
	int				rndSpeech;	//랜덤한 대사를 위한 랜덤값
	float			x, y;		//출력될 위치
	float			maxWidth;	//쓸 줄 알았는데 안쓰는 최대 가로 값
	int				speechCount;//대사가 띄워진 시간 카운트용
	int				speechEnd;	//이 값보다 count값이 커지면 벡터에 들어간 대사 지워짐
};
class dialogue : public gameNode
{
	vector<tagSpeech>		_vSpeech;	//speechCreate에서 대사가 생성되면 벡터에 집어 넣음

public :
	virtual HRESULT init();
	virtual void release(int index);
	virtual void update();
	virtual void render();

	void speechCreate(int enemyName, float x, float y);

};

