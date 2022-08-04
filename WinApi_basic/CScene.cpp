#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CObject_Tile.h"

#include "CResMgr.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
{

}
CScene::~CScene() 
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
				m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (;iter!=m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]);
	for (size_t i = 0; i < m_arrObj[(UINT)_eTarget].size(); ++i)
	{
		if (nullptr != m_arrObj[(UINT)_eTarget][i])
		{
			delete m_arrObj[(UINT)_eTarget][i];
		}
	}
	m_arrObj[(UINT)_eTarget].clear();
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"TILE", L"texture\\TILE.bmp");

	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CObject_Tile* pTile = new CObject_Tile();

			// j * tile 가로 + i * tile 세로
			pTile->SetPos(vec2((float)(j * 60), (float)(i * 80)));
			pTile->SetTexture(pTileTex);

			pushObject((UINT)GROUP_TYPE::TILE, pTile);
		}
	}
}
