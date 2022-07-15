#include "pch.h"
#include "CCollider.h"
#include "CObject.h"

#include "CCore.h"

#include"SelectGDI.h"

CCollider::CCollider()
	:m_pOwner(nullptr)
	, m_vOffsetPos(vec2(0, 0))
	, m_vFinalPos(vec2(0, 0))

{

}

CCollider::~CCollider()
{

}

void CCollider::finalupdate()
{
	vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc,
		  (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f)
		);

}