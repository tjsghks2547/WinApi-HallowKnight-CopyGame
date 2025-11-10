#pragma once
#include "Define.h"

class CPathMgr
{
	SINGLE(CPathMgr);

private:

	wchar_t m_szContentPath[255];
	wchar_t m_szRelativePath[255];

public:


public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } // const 준 이유는 수정을 불가능하게 하기 위해서
	wstring GetRelativePath(const wchar_t* _filepath);

};

