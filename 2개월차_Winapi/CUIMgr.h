#pragma once

class CUI; 


class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI*  m_pFocusedUI;

public:
	void update();

	//특정 ui 를 키눌러서 하고싶을 때 사용 (즉시 포커스 기능) 
	void SetFocusedUI(CUI* _pUI);

private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환해주는 함수
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI); 

};

