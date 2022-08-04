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

	CTexture*						m_pTex;		   // Animation 이 사용하는 텍스처
	vector<tAnimFrm>		m_vecFrm;	   // 모든 프레임 정보
	int									m_iCurFrm;	   // 현재 프레임
	float								m_fAccTime; // 시간 누적

	bool								m_bFinsih;     // 애니메이션이 끝낫을때 finsih check

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

