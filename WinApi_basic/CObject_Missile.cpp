#include "pch.h"
#include "CObject_Missile.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CObject_Missile::CObject_Missile()
	:mi_fTheta(1.f)
	,mi_fSpeed(100.f)
	,mi_vDir(vec2(1.f,1.f))
	,mi_miTex(nullptr)
{
	mi_miTex = CResMgr::GetInst()->LoadTexture(L"MissileTex", L"texture\\missile.bmp");
}

CObject_Missile::~CObject_Missile()
{

}

void CObject_Missile::render(HDC _dc)
{
	int iWidth = (int)mi_miTex->Width();
	int iHeight = (int)mi_miTex->Height();

	BitBlt(_dc
		, (int)(GetPos().x - (float)(iWidth / 2))
		, (int)(GetPos().y - (float)(iHeight / 2))
		, iWidth, iHeight, mi_miTex->GetDC()     
		, 0, 0, SRCCOPY);
}

void CObject_Missile::update()
{
	vec2 vCurPos = GetPos();
	//vCurPos.x += cosf(mi_fTheta) * mi_fSpeed * fDT;
	//vCurPos.y += sinf(mi_fTheta) *mi_fSpeed * fDT;

	vCurPos.x += mi_vDir.x * mi_fSpeed * fDT;
	vCurPos.y += mi_vDir.y *mi_fSpeed * fDT;


	SetPos(vCurPos);
}