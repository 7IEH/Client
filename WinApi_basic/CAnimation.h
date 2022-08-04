#pragma once

#include "global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	vec2		vLT;
	vec2		vSlice;
	vec2		vOffset;
	float		fDuration;
};

class CAnimation
{
private:
	wstring							m_strName;
	CAnimator*					m_pAnimator;

	CTexture*						m_pTex;		   // Animation �� ����ϴ� �ؽ�ó
	vector<tAnimFrm>		m_vecFrm;	   // ��� ������ ����
	int									m_iCurFrm;	   // ���� ������
	float								m_fAccTime; // �ð� ����

	bool								m_bFinsih;     // �ִϸ��̼��� �������� finsih check

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void Create(CTexture* _pTex, vec2 _vLT, vec2 _vSliceSize, vec2 _vStep, float _fDuration, UINT _iFrameCount);
	void render(HDC _dc);
	void update();
	//CAnimator* GetAnimator

	
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinsih; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinsih = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

