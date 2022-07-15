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

	// ������ GDI object �ı�
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}
	
int CCore::init(HWND _hWnd, POINT _ptResolution) {
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	// AdjustWindowRect(������ rect�� ũ��, �������� �⺻����, �޴��� true/false);
	// rt�� adjustwindowrect���� rt�� return�� �����쿡 �°� ������ ũ�� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	//setWindowPos(�ٷ� ������, x, POINT ������ġ,����,����,x)	
	SetWindowPos(m_hWnd,nullptr,100,100,rt.right-rt.left,rt.bottom-rt.top,0);

	m_hDC = GetDC(m_hWnd);


	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// ���� ��� �� �� �� �귯��
	CreateBrushPen();


	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CCollisionMgr::GetInst()->init();


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
	// ȭ�� clear
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
