#include "pch.h"
#include "CCore.h"

// Manager
#include "CTimeMgr.h"
#include"CKeyMgr.h"
#include"CSceneMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"

CCore::CCore() :	m_hWnd(0), 
								m_ptResolution{}, 
								m_hDC(0), 
								m_hBit(0),
								m_memDC(0),
								m_arrBrush{},
								m_arrPen{}
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC);
	
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	// 가져온 GDI object 파괴
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}
	
int CCore::init(HWND _hWnd, POINT _ptResolution) {
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	// AdjustWindowRect(윈도우 rect의 크기, 윈도우의 기본형태, 메뉴바 true/false);
	// rt에 adjustwindowrect에서 rt로 return함 윈도우에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	//setWindowPos(다룰 윈도우, x, POINT 시작위치,가로,세로,x)	
	SetWindowPos(m_hWnd,nullptr,100,100,rt.right-rt.left,rt.bottom-rt.top,0);

	m_hDC = GetDC(m_hWnd);


	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// 자주 사용 할 펜 및 브러쉬
	CreateBrushPen();


	//Manager 초기화
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;	
}


void CCore::progress() 
{
	// Manager update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CSceneMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();
	
	// =============
	// Rendering
	// =============
	// 화면 clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}

