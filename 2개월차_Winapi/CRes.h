#pragma once



class CRes
{
private:
	wstring m_strKey; // 필요한 리소스에 대한 지징할 수 있는 변수  (리소스키)
	wstring m_strRelativePath; // 리소스 상대 경로 

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public: 
	CRes();
	virtual ~CRes();
};

