#include "pch.h"
#include "CPathMgr.h"
#include "C_Core.h"


CPathMgr::CPathMgr()
	:m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(255,m_szContentPath); // 현재 경로가 채워짐 

	int iLen = (int)wcslen(m_szContentPath);

	for(int i=iLen -1; i>=0; --i)
	{
		if('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\Release\\content\\");

	//상위 폴더로 
	// + Release\\content \\ 
	// 
	//SetWindowText(CCore::GenInst()->GetMainHwnd(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{

	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(m_szContentPath); // 절대경로
	size_t iFullLen = strFilePath.length(); // 전체길이 

	wstring strRelativePath = strFilePath.substr(iAbsLen,iFullLen-iAbsLen);


	return strRelativePath;
}

