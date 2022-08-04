#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>		m_mapAnim;		// 모든 Animation
	CAnimation*									m_pCurAnim;		// 현재 Animation
	CObject*										m_pOwner;
	bool												m_bRepeat;		//반복 재생 여부

public:
	void CreateAnimation(const wstring& _strName,CTexture* _pTex,vec2 _vLT,vec2 _vSliceSize,vec2 _vStep, float _fDuration,UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void  Play(const wstring& _strName,bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

	CObject* GetObj() { return m_pOwner; }
public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

