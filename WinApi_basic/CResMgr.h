#pragma once

class CRes;
class CTexture;

class CResMgr
{
public:
	SINGLE(CResMgr);

private:
	map<wstring, CRes*> m_mapTex;


public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iwidth, UINT _iHeight);
	CTexture* FindTexture(const wstring& _strKey);

	void init();
};

