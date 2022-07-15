#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr() :m_llCurCount{}, m_llPrevCount{}, m_llFrequency{}, m_dDT(0.), m_iCallCount(0), m_dAcc(0.)
{

}

CTimeMgr::~CTimeMgr() 
{

}

void CTimeMgr::init() 
{
	
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update() 
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT=(double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llFrequency.QuadPart;
	 
	
	// 이전 카운터를 현재 카운터로 바꿔준다.(prevcount는 처음 CTimeMgr이 생성되고 나서 들어간 값이기 때문)	
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render()
{

	++m_iCallCount;
	m_dAcc += m_dDT;//DT 누적

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->getHWND(), szBuffer);
	}
}