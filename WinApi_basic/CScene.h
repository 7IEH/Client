#pragma once

// 전방선언
class CObject;


class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring					  m_strName; // Scene 이름


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& getName() { return m_strName; }

	void update();
	void finalupdate();
	void render(HDC _dc);

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

public:
	CScene();
	virtual ~CScene();
};

 