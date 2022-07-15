#pragma once

class CTimeMgr
{
public:
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFrequency;


	double						m_dDT; //��Ÿ Ÿ��
	double						m_dAcc; //1�� üũ�� ���� ���� �ð�
	UINT							m_iCallCount; // �ʴ� ȣ�� Ƚ��
	UINT                           m_iFPS; // �ʴ� ȣ�� Ƚ��

	// FPS
	// 1 �����Ӵ� �ð� (Delta Time)
public:
	void init();
	void update();

	void render();

public:
	double GetDT() { return m_dDT; }
	float GETfDT() { return (float)m_dDT; }
};

