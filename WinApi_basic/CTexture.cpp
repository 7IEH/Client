#include "pch.h"
#include "CTexture.h"
#include "CCore.h"
CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{

}

CTexture:: ~CTexture()
{
	DeleteObject(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// 비트맵과 연결할 DC
	m_dc=CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보 m_bitInfo 안에 bitmap에 대한 size 정보등을 넣음
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}