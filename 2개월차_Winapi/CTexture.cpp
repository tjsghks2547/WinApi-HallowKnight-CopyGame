#include "pch.h"
#include "CTexture.h"
#include "C_Core.h"



CTexture::CTexture()
	:m_dc(0)
	,m_hBit(0)
	,m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	//파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit =(HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//LoadImageA가 JPG 파일 

	assert(m_hBit);

	//비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(CCore::GenInst()->GetMainDC());
	
	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);


	//가로 세로 길이 (비트맵정보)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	//가로 세로 길이
	/*tInfo.bmWidth;
	tInfo.bmHeight;*/

	
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{

	HDC maindc = CCore::GenInst()->GetMainDC();
	m_hBit = CreateCompatibleBitmap(maindc,_iWidth ,_iHeight); // m_hDC와 호환성이 되는 비트맵 만들기.
	m_dc = CreateCompatibleDC(maindc); // 비트맵에 그릴 DC 설정 

	HBITMAP holdbit = (HBITMAP)SelectObject(m_dc, m_hBit);
	// 그림을 그릴 DC를 비트맵과 연결해주는게 SelectObject이고 holdBit는 디폴트값 1픽셀 비트맵을 가지고 있으므로 삭제를 진행함.
	DeleteObject(holdbit); // 삭제 코드

	//비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
