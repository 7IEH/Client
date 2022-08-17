#include "pch.h"
#include "CPathMgr.h"
#include	"CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
	, m_szRelativePath{}
{

}

CPathMgr::~CPathMgr()
{

}


void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);
	// 상위 폴더
	int iLen = (int)wcslen(m_szContentPath);
	
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	} 
	
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
	// window title에 표시
	SetWindowText(CCore::GetInst()->getHWND(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = (wstring)_filePath;

	size_t iPos = wcslen(m_szContentPath);
	size_t iEnd = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iPos, iEnd-iPos);

	return strRelativePath;
}
