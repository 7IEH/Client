#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
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
//		// ���� ȣ�� �� ���
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


// �� ��Ŀ� ������ ���Ҷ� release�� ����
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


	HWND					m_hWnd;                   //���� ������ �ڵ�
	POINT					m_ptResolution;     //���� ������ �ػ�
	HDC						m_hDC;						  //���� �����쿡 Draw �� DC

	HBITMAP			m_hBit;
	HDC						m_memDC;

	// ���� ����ϴ� GDI object
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


