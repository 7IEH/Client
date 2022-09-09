#include "pch.h"
#include "CObject_ScoreBox.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CObject_ScoreBox::CObject_ScoreBox()
	: m_bSlide(false)
{
	CreateCollider();
	GetCollider()->SetScale(vec2(100.f, 100.f));
}

CObject_ScoreBox::~CObject_ScoreBox()
{
}

void CObject_ScoreBox::update()
{
	if (m_bSlide)
	{
		vec2 vCurPos = GetPos();
		vCurPos.x -= 100.f * fDT;
		SetPos(vCurPos);
	}
}

void CObject_ScoreBox::OnCollisionEnter(CCollider* _pOther)
{
}