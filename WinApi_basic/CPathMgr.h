#pragma once


class CPathMgr
{
public:
	SINGLE(CPathMgr);
	
private:
	wchar_t				m_szContentPath[256];
	wchar_t				m_szRelativePath[256];

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

	wstring GetRelativePath(const wchar_t* _filePath);

};

