#pragma once

#define PI 3.141592f
#define PI2 PI*2

#define RECT_WIDTH(rc) static_cast<float>(rc.right - rc.left)
#define RECT_HEIGHT(rc) static_cast<float>(rc.bottom - rc.top)
#define RECT_CENTER_X(rc) static_cast<float>((rc.left + rc.right) * 0.5f)
#define RECT_CENTER_Y(rc) static_cast<float>((rc.top + rc.bottom) * 0.5f)

namespace UJN_UTIL
{
	//거리가져오는 함수
	float GetDistance(float startX, float startY, float endX, float endY);

	float GetAngle(float x1, float y1, float x2, float y2);

	
	//사각형 구조체
	typedef struct tagENEMYRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		tagENEMYRECT() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
		tagENEMYRECT(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		void Move(float dx, float dy)
		{
			left += dx;
			right += dx;
			top += dy;
			bottom += dy;
		}

		void Set(float _left, float _top, float _right, float _bottom)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}

		//레프트 탑으로 셋팅
		void SetLeftTopPos(float _left, float _top)
		{
			float width = getWidth();
			float height = getHeight();

			left = _left;
			top = _top;
			right = _left + width;
			bottom = _top + height;
		}

		void SetCenterPos(float centerX, float centerY)
		{
			float halfW = getWidth() * 0.5f;
			float halfH = getHeight() * 0.5f;

			left = centerX - halfW;
			top = centerY - halfH;
			right = centerX + halfW;
			bottom = centerY + halfH;
		}

		float getWidth(void) { return right - left; }
		float getHeight(void) { return bottom - top; }
	}ENEMYRECT, * LPENEMYRECT;

	//사각형이 사각형과 충돌했니?
	bool IsCollision(const RECT& rc1, const ENEMYRECT& rc2);
	bool IsCollision(const RECT& rc1, const RECT& rc2);

	//wchar_t 에서 char 로의 형변환 함수
	char * ConvertWCtoC(wchar_t * str);
	const char * ConvertWCtoC(const wchar_t * str);
	//char 에서 wchar_t 로의 형변환 함수
	wchar_t *ConvertCtoWC(char * str);
	const wchar_t *ConvertCtoWC(const char * str);
	//stirng 에서 wstring 으로 형 변환 함수
	wstring ConvertStoWS(string str);
	string ConvertWStoS(wstring w_str);

	// OBB충돌
	// 실질적으로 사용해주는 건 SHAPE 와 OBB입니다.
	// interSectRect를 위해 rect를 만들어주는 것처럼 SHAPE를 만들고
	// OBB로 체크하면 됩니다.
	typedef struct VECTOR
	{
		double x, y;
	};

	typedef struct SHAPE //회전충돌::실질적 사용
	{
		double left, top, width, height, degreeAngle;
	};

	VECTOR addVector(VECTOR& a, VECTOR& b);
	float absDotVector(VECTOR& a, VECTOR& b);
	float degreeToRadian(float degreeAngle);
	float radianToDegree(float radianAngle);
	VECTOR getDistanceVector(SHAPE& a, SHAPE& b);
	VECTOR getHeightVector(SHAPE& a);
	VECTOR getWidthVector(SHAPE& a);
	VECTOR getUnitVector(VECTOR& a);
	bool OBB(SHAPE& a, SHAPE& b); //회전충돌::실질적 사용
}