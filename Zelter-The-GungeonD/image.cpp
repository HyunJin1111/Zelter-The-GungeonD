#include "stdafx.h"
#include "image.h"

image::image()
	:_fileName(NULL)
{
}

image::~image()
{
}

/*
================================================
## 기본 이미지(프레임 이미지X)
@@ bitmap	: 비트맵
================================================
*/
HRESULT image::init(ID2D1Bitmap * const bitmap)
{

	_bitmap = bitmap;

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = bitmap->GetPixelSize().width;
	_imageInfo->height = bitmap->GetPixelSize().height;

	ResetRenderOption();

	return S_OK;
}

HRESULT image::init(int width, int height)
{
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;

	ResetRenderOption();

	return S_OK;
}

/*
================================================
## 기본 이미지(프레임 이미지X)
@@ bitmap	: 비트맵
@@ fileName : 파일 이름
@@ widht	: type(0) - 너비  type(1) maxFrameX
@@ height	: type(0) - 높이  type(1) maxFrameY
@@ type		: 일반이미지(0) , 프레임이미지(1)
================================================
*/
HRESULT image::init(ID2D1Bitmap*const bitmap, int width, int height, bool type)
{

	_bitmap = bitmap;

	if (!type)
	{
		_imageInfo = new IMAGE_INFO;
		_imageInfo->width = width;
		_imageInfo->height = height;
	}
	else
	{
		_imageInfo = new IMAGE_INFO;
		_imageInfo->width = bitmap->GetPixelSize().width;
		_imageInfo->height = bitmap->GetPixelSize().height;
		_imageInfo->maxFrameX = width;
		_imageInfo->maxFrameY = height;
		_imageInfo->currentFrameX = 0;
		_imageInfo->currentFrameY = 0;
		_imageInfo->frameWidth = _imageInfo->width / width;
		_imageInfo->frameHeight = _imageInfo->height / height;
	}

	ResetRenderOption();

	return S_OK;
}

/*
================================================
## 프레임 이미지
@@ bitmap	: 비트맵
@@ fileName : 파일 이름
@@ widht	: 너비
@@ height	: 높이
@@ frameX	: 최대 가로 축 프레임 갯수
@@ frameY	: 최대 세로 축 프레임 갯수
================================================
*/
HRESULT image::init(ID2D1Bitmap*const bitmap, int width, int height, int frameX, int frameY)
{

	_bitmap = bitmap;

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = bitmap->GetPixelSize().width;
	_imageInfo->height = bitmap->GetPixelSize().height;
	_imageInfo->maxFrameX = frameX;
	_imageInfo->maxFrameY = frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;

	_count = 0;

	ResetRenderOption();

	return S_OK;
}

void image::release()
{
	SAFE_DELETE(_bitmap);
	SAFE_DELETE(_fileName);
}

/*
================================================
## 기본 렌더
@@ x, y				: 이미지가 찍힐 left,top
@@ scaleW, scaleH	: 이미지 스케일 조정(기본 1.f)
@@ degreeAngle		: 우리가 평상시 쓰는 각도 ex) 180도 (기본 0.f)
@@ rotateX, rotateY	: 이미지가 회전 할 기준 점 (기본 0.f)
@@ transX, transY	: 이미지 이동 시키기 (기본 0.f)
================================================
*/
void image::render(const float x, const float y,
	const float scaleW, const float scaleH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scaleW, scaleH, D2D1::Point2F(x, y));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(-degreeAngle, D2D1::Point2F(x + rotateX, y + rotateY));
	D2D1::Matrix3x2F transMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	D2D1_RECT_F viewArea = D2D1::RectF(x, y, x + _imageInfo->width, y + _imageInfo->height);

	D2DRENDERTARGET->SetTransform(scaleMatrix * rotateMatrix * transMatrix);
	D2DRENDERTARGET->DrawBitmap(_bitmap, viewArea, _alpha);

	if (_alpha <= 0)ResetRenderOption();

}
 
/*
================================================
## 기본 렌더(이미지 내 특정 구역 잘라서 사용 가능)
@@ x, y				: 이미지가 찍힐 left,top
@@ sourX, sourY		: 이미지 자를 위치
@@ sourW, sourH		: 자를 이미지 너비, 높이
@@ alpha			: 투명도 조정(기본 1.f)
@@ scaleW, scaleH	: 이미지 스케일 조정(기본 1.f)
@@ degreeAngle		: 우리가 평상시 쓰는 각도 ex) 180도 (기본 0.f)
@@ rotateX, rotateY	: 이미지가 회전 할 기준 점 (기본 0.f)
@@ transX, transY	: 이미지 이동 시키기 (기본 0.f)
================================================
*/
void image::cutRender(const float x, const float y,
	const float sourX, const float sourY,
	const float sourW, const float sourH,
	const float alpha,
	const float scaleW, const float scaleH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scaleW, scaleH, D2D1::Point2F(x, y));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(-degreeAngle, D2D1::Point2F(x + rotateX, y + rotateY));
	D2D1::Matrix3x2F transMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	int cutX = sourX * _imageInfo->frameWidth;
	int cutY = sourY * _imageInfo->frameHeight;

	D2D1_RECT_F viewArea = D2D1::RectF(x, y, x + sourW, y + sourH);						//보이는 영역
	D2D1_RECT_F sourArea = D2D1::RectF(cutX, cutY, cutX+ _imageInfo->frameWidth,cutY+ _imageInfo->frameHeight);			//자른 영역

	D2DRENDERTARGET->SetTransform(scaleMatrix * rotateMatrix * transMatrix);
	D2DRENDERTARGET->DrawBitmap(_bitmap, viewArea, alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourArea);

	if (alpha <= 0)ResetRenderOption();
}
/*
================================================
## 기본 프레임 렌더
@@ x, y				: 이미지가 찍힐 left,top
@@ scaleW, scaleH	: 이미지 스케일 조정(기본 1.f)
@@ degreeAngle		: 우리가 평상시 쓰는 각도 ex) 180도 (기본 0.f)
@@ rotateX, rotateY	: 이미지가 회전 할 기준 점 (기본 0.f)
@@ transX, transY	: 이미지 이동 시키기 (기본 0.f)
================================================
*/
void image::frameRender(const float x, const float y,
	const int speed, const bool loop,
	const float scaleW, const float scaleH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{
	int& frameX = _imageInfo->currentFrameX;
	int& frameY = _imageInfo->currentFrameY;
	int& maxFrameX = _imageInfo->maxFrameX;
	int& maxFrameY = _imageInfo->maxFrameY;

	//현재 프레임인덱스 
	_count++;
	if (_count%speed == 0)
	{
		frameX++;
		if (frameX >= maxFrameX && loop)frameX = 0;
		else if (frameX >= maxFrameX && !loop)
		{
			frameX = maxFrameX - 1;
		}
		_count = 0;
	}

	int currentX = frameX * _imageInfo->frameWidth;
	int currentY = frameY * _imageInfo->frameHeight;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scaleW, scaleH, D2D1::Point2F(x, y));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(-degreeAngle, D2D1::Point2F(x + rotateX, y + rotateY));
	D2D1::Matrix3x2F transMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	//수정 필요

	D2D1_RECT_F viewArea = D2D1::RectF(x,y,x+_imageInfo->frameWidth,y+ _imageInfo->frameHeight);
	D2D1_RECT_F sourArea = D2D1::RectF(currentX, currentY,
		currentX + _imageInfo->frameWidth, currentY + _imageInfo->frameHeight);


	D2DRENDERTARGET->SetTransform(scaleMatrix * rotateMatrix * transMatrix);
	D2DRENDERTARGET->DrawBitmap(_bitmap, viewArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourArea);

	if (_alpha <= 0)ResetRenderOption();
}

void image::frameRender2(const float x, const float y, const int frameX, const int frameY,
	const float scaleW, const float scaleH,
	const float degreeAngle, const float rotateX, const float rotateY,
	const float transX, const float transY)
{
	int currentFrameX = frameX * _imageInfo->frameWidth;
	int currentFrameY = frameY * _imageInfo->frameHeight;

	int cameraX = CAMERAMANAGER->getX();
	int cameraY = CAMERAMANAGER->getY();

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scaleW, scaleH, D2D1::Point2F(x, y));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(-degreeAngle, D2D1::Point2F(x + rotateX, y + rotateY));
	D2D1::Matrix3x2F transMatrix = D2D1::Matrix3x2F::Translation(transX, transY);

	D2D1_RECT_F viewArea = D2D1::RectF(x- cameraX, y - cameraY, x-cameraX + _imageInfo->frameWidth, y - cameraY + _imageInfo->frameHeight);
	D2D1_RECT_F sourArea = D2D1::RectF(currentFrameX, currentFrameY,
		currentFrameX + _imageInfo->frameWidth, currentFrameY + _imageInfo->frameHeight);

	D2DRENDERTARGET->SetTransform(scaleMatrix * rotateMatrix * transMatrix);
	D2DRENDERTARGET->DrawBitmap(_bitmap, viewArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourArea);

	if (_alpha <= 0)ResetRenderOption();
}


void image::mainRender(const float x, const float y)
{

}

void image::miniRender(const float x, const float y, const float sourX, const float sourY, const float sourW, const float sourH)
{
	D2D1_RECT_F viewArea = D2D1::RectF(x, y, x + sourW, y + sourH);
	
	D2DRENDERTARGET->DrawBitmap(_bitmap, viewArea, _alpha);

	D2D1_RECT_F sourArea = D2D1::RectF(sourX, sourY, sourX + sourW, sourY + sourH);
	D2D1_RECT_F backArea = D2D1::RectF(0, 0, BACKGROUNDX, BACKGROUNDY);

	D2DRENDER->GetBackBuffer()->GetBitmap(&_backBufferBitmap);

	D2DRENDERTARGET->DrawBitmap(_backBufferBitmap, sourArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, backArea);

}

//추가했습니다
void image::barRender(const float X, const float Y, const float sourX)
{
	D2D1_RECT_F sourArea = D2D1::RectF(X, Y, X + sourX, Y + _imageInfo->height);
	D2D1_RECT_F backArea = D2D1::RectF(X, Y, X + _imageInfo->width, Y + _imageInfo->height);

	D2DRENDERTARGET->DrawBitmap(_bitmap, sourArea, _alpha);

	ResetRenderOption();
}
//================

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void image::ResetRenderOption()
{
	_alpha = 1.0f;
	_scale = 1.0f;
	_angle = 0.f;
	//if (_imageInfo->.size() <= 1)
	//{
	//	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	//	this->mSize.y = (float)mBitmap->GetPixelSize().height;
	//}
	//else
	//{
	//	this->mSize.x = mFrameInfo[0].width;
	//	this->mSize.y = mFrameInfo[0].height;
	//}
}
