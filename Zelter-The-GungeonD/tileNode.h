#pragma once

#define TILESIZEX 32
#define TILESIZEY 32

#define SAMPLETILEX 20
#define SAMPLETILEY 9

#define TILEX 225
#define TILEY 120

#define ATTR_UNMOVE 0x00000001	//못가는 타일
#define NONEMOVE 1
//#define ATTR_SWAMP	0x00000002	//밟으면 느려지는 타일
//#define ATTR_POISON	0x00000004	//유 아 마 포이즌~
//#define ATTR_FROZEN 0x00000008	//레릿꼬~

enum TILETYPE
{
	OPENWORLD,
	BULLETKING,
	AMOCONDA,
	DUNBOSS
};

enum TERRAIN
{
	CEMENT,
	DESERT,
	WATER,
	TR_NONE
};

enum OBJECT
{
	BLOCK,
	BLOCK_BHALF,
	BLOCK_LHALF, BLOCK_RHALF,
	BLOCK_LTRIPLE, BLOCK_RTRIPLE,
	OBJ_Be,
	OBJ_NONE
};

struct tagTileInfo
{
	TILETYPE type;
	string name;
	RECT rc;
	float width, height;
};

struct tagTile
{
	string tileType;
	TERRAIN terrain;
	OBJECT object;
	image* img;
	RECT rc;
	//RECT obj;
	RECT checkRect;
	int terrainX;
	int terrainY;
	int objX;
	int objY;
	int sizeX;
	int sizeY;
	bool isMove;
	bool colChk;
};

struct tagSampleTile
{
	string tileType;
	RECT rc;
	int frameX;
	int frameY;
};

struct tagButton
{
	RECT rc;
	image* img;
};

struct tagMapTool
{
	RECT rc;
	float width, height;
	bool isOn;
};

struct tagMouseDrag
{
	RECT rc;
	POINT start;
	POINT end;
	int currentStartX;
	int currentStartY;
	int currentEndX;
	int currentEndY;
	bool isDrag;
};