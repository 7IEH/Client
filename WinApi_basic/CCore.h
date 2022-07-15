#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// public? private? extern!
//class CCore
//{
//private:
//	static CCore* pcore;
//	CCore();
//	~CCore();
//
//public:
//	static CCore* GetInstance() 
//	{	
//		// 최초 호출 된 경우
//		if (nullptr == pcore) {
//			pcore	= new CCore;
//		}
//		return pcore;
//	}
//
//	static void Release() 
//	{	
//		if (nullptr != pcore) {
//			delete pcore;
//			pcore = nullptr;
//		}
//	}
//};


// 이 방식에 단점은 원할때 release를 못함
#include "pch.h"

class CCore {
public:
	SINGLE(CCore);
	/* define.h -> SINGLE(type)
	static CCore* GetInst()
	{
		static CCore core;

		return &core;
	}
	*/
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();	

private:
	void update();
	void render();


	HWND					m_hWnd;                   //메인 윈도우 핸들
	POINT					m_ptResolution;     //메인 윈도우 해상도
	HDC						m_hDC;						  //메인 윈도우에 Draw 할 DC

	HBITMAP			m_hBit;
	HDC						m_memDC;

	// 자주 사용하는 GDI object
	HBRUSH				m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN					m_arrPen[(UINT)PEN_TYPE::END];

public:
	HWND getHWND() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }


private:
	void CreateBrushPen();
};


