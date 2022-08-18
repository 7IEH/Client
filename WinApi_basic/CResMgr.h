#pragma once

class CRes;
class CTexture;
class CSound;

class CResMgr
{
public:
	SINGLE(CResMgr);

private:
	map<wstring, CRes*>				m_mapTex;
	map<wstring, CRes*>				m_mapSound;


public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iwidth, UINT _iHeight);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
};

