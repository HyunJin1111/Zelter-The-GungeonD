#pragma once
#include "gameNode.h"
//
//#define TILESIZEX 32
//#define TILESIZEY 32
//
//#define SAMPLETILEX 20
//#define SAMPLETILEY 9
//
//#define TILEX BACKGROUNDX / TILESIZEX 
//#define TILEY BACKGROUNDY / TILESIZEY 
//
//enum TILETYPE
//{
//	OPENWORLD,
//	BULLETKING,
//	AMOCONDA,
//	EGGNYANG,NIFLHEIM
//};
//
//enum TERRAIN
//{
//	CEMENT,
//	DESERT,
//	WATER,
//	TR_NONE
//};
//
//enum OBJECT
//{
//	BLOCK,
//	BLOCK_LHALF, BLOCK_RHALF,
//	BLOCK_LTRIPLE, BLOCK_RTRIPLE,
//	OBJ_Be,
//	OBJ_NONE
//};
//
//struct tagTileInfo
//{
//	TILETYPE type;
//	string name;
//	RECT rc;
//	float width, height;
//};
//
//struct tagTile
//{
//	string tileType;
//	TERRAIN terrain;
//	OBJECT object;
//	image* img;
//	RECT rc;
//	RECT checkRect;
//	int terrainX;
//	int terrainY;
//	int objX;
//	int objY;
//	int sizeX;
//	int sizeY;
//	bool isMove;
//};
//
//struct tagSampleTile
//{
//	string tileType;
//	RECT rc;
//	int frameX;
//	int frameY;
//};
//
//struct tagButton
//{
//	RECT rc;
//	image* img;
//};
//
//struct tagMapTool
//{
//	RECT rc;
//	float width, height;
//	bool isOn;
//};
//
//struct tagMouseDrag
//{
//	RECT rc;
//	POINT start;
//	POINT end;
//	int currentStartX;
//	int currentStartY;
//	int currentEndX;
//	int currentEndY;
//	bool isDrag;
//};
//
//
//class mapmap : public gameNode
//{
//private:
//	tagTileInfo		_tileInfo;
//	tagTile			_tile[TILEX * TILEY];
//
//	image*			_sampleImg;
//	tagSampleTile	_sample[SAMPLETILEX * SAMPLETILEY];
//
//	POINT			_currentTile;
//	POINT			_mapMouse;
//
//
//	tagMapTool		_tool;
//
//	tagButton		_btnSave;
//	tagButton		_btnLoad;
//	tagButton		_btnEraser;
//	tagButton		_btnObject;
//	tagButton		_btnTerrain;
//	tagButton		_btnEnter;
//	tagButton		_btnPrevios;
//	tagButton		_btnNext;
//	tagButton		_btnClear;
//
//	tagMouseDrag	_dragMouse;
//
//	RECT			_message;
//
//	bool			_dragStart;
//
//	int				_changeCount; //샘플이미지 바꾸기 위한 카운트용
//
//	//=======================================
//	POINT move;
//
//public:
//	mapmap() {};
//	~mapmap() {};
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//	//맵 초기 설정 및 맵 설정
//	void setup();
//	void setImage();
//	void setMap();
//	void setCamera(int mapSizeX, int mapSizeY);
//	void mapClipping();
//
//	//샘플 관련 함수
//	void sampleRender();
//	void changeSample();
//	void tapTool();
//	void dragField();
//
//	//세이브 로드
//	void save();
//	void load();
//	void clear();
//
//	//버튼 관련
//	void buttonRender();
//
//	//지형 관련 함수
//	TERRAIN terrainSelect(int frameX, int frameY);
//	void setTerrainRect(TERRAIN tr, int num);
//
//	//오브젝트 관련 함수
//	OBJECT objSelect(int frameX, int frameY);
//	void setObjectRect(OBJECT obj, int num);
//};
//
