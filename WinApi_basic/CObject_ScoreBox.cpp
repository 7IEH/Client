#include "pch.h"
#include "CObject_ScoreBox.h"
#include "CCollider.h"

CObject_ScoreBox::CObject_ScoreBox()
{
	CreateCollider();
	GetCollider()->SetScale(vec2(100.f, 100.f));
}

CObject_ScoreBox::~CObject_ScoreBox()
{
}

void CObject_ScoreBox::OnCollisionEnter(CCollider* _pOther)
{
}