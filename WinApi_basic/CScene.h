#pragma once

// ���漱��
class CObject;


class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring					  m_strName; // Scene �̸�


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

 