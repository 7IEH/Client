#include "pch.h"
#include "CObject_Player.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CObject_Missile.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include"CTexture.h"
#include"CResMgr.h"
#include"CCollider.h"
#include "CEventMgr.h"

// 컴포넌트
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"



CObject_Player::CObject_Player()
{
	// Texture 로딩하기
	//m_pTex=CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player.bmp");

	 // Collider 생성
	 CreateCollider();
	 GetCollider()->SetScale(vec2(100.f, 100.f));

	 CreateRigidBody();

	 CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player_ani.bmp");
	 CreateAnimator();
	 GetAnimator()->CreateAnimation(L"WALK_DOWN",pTex, vec2(0.f, 0.f), vec2(94.5f, 133.f), vec2(94.5f, 0.f),0.2f, 4);
	 GetAnimator()->Play(L"WALK_DOWN", true);

	 CAnimation* pAnim=GetAnimator()->FindAnimation(L"WALK_DOWN");
	 for(UINT i=0;i<pAnim->GetMaxFrame();++i)
	 pAnim->GetFrame(i).vOffset=vec2(0.f,-20.f);
}

CObject_Player::~CObject_Player()
{
}

void CObject_Player::update()
{
	CRigidBody* pRigid = GetRigidBody();

	pRigid->AddForce();

	if (KEY_CHECK(W,HOLD))
	{
		SetPos(vec2(GetPos().x,GetPos().y- 200.f * fDT));
	}
	if (KEY_CHECK(S, HOLD))
	{
		SetPos(vec2(GetPos().x, GetPos().y + 200.f * fDT));
	}
	if (KEY_CHECK(A, HOLD))
	{
		SetPos(vec2(GetPos().x - 200.f * fDT, GetPos().y));	
	}
	if (KEY_CHECK(D, HOLD))
	{
		SetPos(vec2(GetPos().x + 200.f * fDT, GetPos().y));
	}
	if (KEY_CHECK(Q, TAP))
	{
		createMissile();
	}
}

void CObject_Player::render(HDC _dc)
{
	//m_pAnimator


	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		,0,0,SRCCOPY);*/

	   /*TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(165,72,201));*/

	// 컴포넌트(충돌체, etc ...) 가 있는 경우 렌더
		//component_Render(_dc);

		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\player_A.bmp");

		vec2 vPos = GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

		float width = (float)pTex->Width();
		float height = (float)pTex->Height();


		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 127;

		AlphaBlend(_dc
			, (int)(vPos.x - width/2.f)
			, (int)(vPos.y - height / 2.f)
			, (int)(width), int(height)
			, pTex->GetDC()
			, 0, 0, (int)width, (int)height
			, bf);
}


void CObject_Player::createMissile()
{
	vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CObject_Missile* miObj = new CObject_Missile;
	miObj->SetPos(vMissilePos);
	miObj->SetScale(vec2(30.f, 30.f));
	miObj->SetTheta(10.f);
	miObj->SetName(L"Missile_Player");

	CreateObject(miObj, GROUP_TYPE::PROJ_PLAYER);

	/*CScene *pCurScene=CSceneMgr::GetInst()->GetCurScene();
	pCurScene->pushObject((UINT)GROUP_TYPE::PROJ_PLAYER, miObj);*/
}
