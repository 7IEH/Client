#include "pch.h"
#include "CCore.h"

// Manager
#include "CTimeMgr.h"
#include"CKeyMgr.h"
#include"CSceneMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CSound.h"

CCore::CCore() 
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC);
	
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

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 자주 사용 할 펜 및 브러쉬
	CreateBrushPen();


	//Manager 초기화
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	

	// Sound 로드 테스트
	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

	pNewSound->SetVolume(2.f);
	pNewSound->Play();

	return S_OK;	
}


void CCore::progress() 
{	
	// =============
	// Manager update
	// =============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// =============
	// Scene Update
	// =============
	CSceneMgr::GetInst()->update();

	// 충돌 체크
	CCollisionMgr::GetInst()->update();
	
	// UI 이벤트 체크
	CUIMgr::GetInst()->update();

	// =============
	// Rendering
	// =============
	// 화면 clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	// =============
	// 이벤트 지연처리
	// =============
	CEventMgr::GetInst()->update();
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

