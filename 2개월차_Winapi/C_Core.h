#pragma once

class CTexture;

class CCore 
{

	SINGLE(CCore); //객체 생성하고 주소 반환 

private:
	HWND			m_hWnd; // 메인 윈도우 핸들
	POINT			m_ptResolution; // 메인 윈도후 해상도
	HDC				m_hDC; // 메인 윈도우에 Draw 할 DC (Draw context) 
	
	CTexture*		m_pMemTex;  // 백버퍼 텍스처

	//자주 사용하는 GDI Object
	HBRUSH			m_arrBrsuh[(UINT)BRUSH_TYPE::END];
	HPEN			m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU  m_hMenu; //Tool Scene 에서만 사용

public:
	
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreatBrsuhPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);


public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrsuh[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType];}


	
private:
	bool   m_bRender;

};