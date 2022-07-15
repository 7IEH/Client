#pragma once

class CObject;

class CCollisionMgr
{	
public:
	SINGLE(CCollisionMgr);
private:
	vector<CObject*>				m_vLeftGroup;
	vector<CObject*>				m_vRightGroup;

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);


};

