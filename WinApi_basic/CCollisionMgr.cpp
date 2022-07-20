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
		// vecleft Ÿ���� ������Ʈ�� �浹ü�� �������
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// vecRight Ÿ���� ������Ʈ�� �浹ü�� ������� �� ���� ���� ������Ʈ�� ���
			if (nullptr == vecRight[j]->GetCollider()|| (vecLeft[i] == vecRight[j]))
				continue;

			CCollider* pLeftRow = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵�
			COLLIDER_ID ID;
			ID.Left_id = pLeftRow->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID,false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsTrigger(pLeftRow, pRightCol))
			{
				// ���� �浹��
				if (iter->second)
				{
					// ������ �浹 ���̴�.
					pLeftRow->OnCollision(vecRight[j]->GetCollider());
					pRightCol->OnCollision(vecLeft[i]->GetCollider());
				}
				else
				{
					// �������� �浹���� �ʾҴ�.
					pLeftRow->OnCollisionEnter(vecRight[j]->GetCollider());
					pRightCol->OnCollisionEnter(vecLeft[i]->GetCollider());
					iter->second = true;
				}
			}
			else
			{
				// �浹 ���� �ʾ��� ���
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���
	// (1 << iCol) ��ŭ �̵��ؼ� or�����ڸ� �ϸ� �� ��Ʈ�� �ݿ��Ǹ鼭 check�ϴ°� ��
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

