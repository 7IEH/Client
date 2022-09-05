#include "pch.h"
#include "CObject_Tile.h"

#include "CTexture.h"

CObject_Tile::CObject_Tile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(vec2(TILE_SIZE, TILE_SIZE));
}

CObject_Tile::~CObject_Tile()
{
}


void CObject_Tile::update()
{
}

void CObject_Tile::render(HDC _dc)
{

	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / 64;
	UINT iMaxRow = iHeight / 64;
	
	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	// 이미지를 범위를 벗어난 인덱스
	if (iMaxRow <= iCurRow)
		m_iImgIdx = 0;

	vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	vec2 vScale = GetScale();

	BitBlt(_dc
		, (int)(vRenderPos.x - iWidth/2)
		, (int)(vRenderPos.y - iHeight/2)
		, 64
		, 64
		, m_pTileTex->GetDC()
		, (int)(iCurCol * 64)
		, (int)(iCurRow * 64)
		, SRCCOPY
	);
	component_Render(_dc);
}


void CObject_Tile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CObject_Tile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
