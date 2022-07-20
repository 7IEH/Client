#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CCollider.h"



CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene=CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft=pCurScene->vGetObject(_eLeft);
	const vector<CObject*>& vecRight=pCurScene->vGetObject(_eRight);
	map< ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// vecleft 타입의 오브젝트에 충돌체가 없을경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// vecRight 타입의 오브젝트에 충돌체가 없을경우 와 서로 같은 오브젝트일 경우
			if (nullptr == vecRight[j]->GetCollider()|| (vecLeft[i] == vecRight[j]))
				continue;

			CCollider* pLeftRow = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디
			COLLIDER_ID ID;
			ID.Left_id = pLeftRow->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID,false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsTrigger(pLeftRow, pRightCol))
			{
				// 현재 충돌중
				if (iter->second)
				{
					// 여전히 충돌 중이다.
					pLeftRow->OnCollision(vecRight[j]->GetCollider());
					pRightCol->OnCollision(vecLeft[i]->GetCollider());
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					pLeftRow->OnCollisionEnter(vecRight[j]->GetCollider());
					pRightCol->OnCollisionEnter(vecLeft[i]->GetCollider());
					iter->second = true;
				}
			}
			else
			{
				// 충돌 하지 않았을 경우
				if (iter->second)
				{
					pLeftRow->OnCollisionExit(vecRight[j]->GetCollider());
					pRightCol->OnCollisionExit(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::IsTrigger(CCollider* _pLeftRow, CCollider* _pRightCol)
{
	vec2 LeftFPos = _pLeftRow->GetFinalPos();
	vec2 RightFPos = _pRightCol->GetFinalPos();

	vec2 LeftScale = _pLeftRow->GetScale();
	vec2 RightScale = _pRightCol->GetScale();


	if ((abs(LeftFPos.x - RightFPos.x) < (LeftScale.x / 2.f + RightScale.x / 2.f)) 
		&& (abs(LeftFPos.y - RightFPos.y) < (LeftScale.y / 2.f + RightScale.y / 2.f)))
		return true;

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값은 열(비트) 로 사용
	// (1 << iCol) 만큼 이동해서 or연산자를 하면 그 비트에 반영되면서 check하는게 됨
	// 00000000 0000000 00000000 00000000 

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

