#pragma once

class CTimeMgr
{
public:
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFrequency;


	double						m_dDT; //델타 타임
	double						m_dAcc; //1초 체크를 위한 누적 시간
	UINT							m_iCallCount; // 초당 호출 횟수
	UINT                           m_iFPS; // 초당 호출 횟수

	// FPS
	// 1 프레임당 시간 (Delta Time)
public:
	void init();
	void update();

	void render();

public:
	double GetDT() { return m_dDT; }
	float GETfDT() { return (float)m_dDT; }
};

