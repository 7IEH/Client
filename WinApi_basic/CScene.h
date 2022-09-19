#pragma once

#include "global.h"

// 전방선언
class CObject;


class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring					  m_strName; // Scene 이름

	UINT						  m_iTileX;	// 타일 가로 개수
	UINT                         m_iTileY;	// 타일 새로 개수

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& getName() { return m_strName; }


	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	void render_tile(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void pushObject(UINT _GROUP_TYPE, CObject* _pObj)
	{
		m_arrObj[_GROUP_TYPE].push_back(_pObj);
	}

	const vector<CObject*>& vGetObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);
	void LoadMap(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

 