#include "pch.h"
#include "CAnimator.h"

#include "CObject.h"
#include "CAnimation.h"


CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delte_Map(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName,CTexture* _pTex, vec2 _vLT, vec2 _vSliceSize, vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim=FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim=new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim=FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator::update()
{
	
}

void CAnimator::finalupdate()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}
