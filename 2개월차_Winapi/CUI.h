#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:


    vector<CUI*>  m_vecChildUI; 
    CUI*          m_pParentUI;
    Vec2          m_vFinalPos;

    bool          m_bCamAffected; // UI가 카메라에 영향을 받는 유무 
    bool          m_bMouseOn;     // UI 위에 마우스가 있는지 유무 
    bool          m_bLbtnDown;    // UI에 왼쪽 버튼이 눌린적이 있는지 유무
    
public:

    Vec2 GetFinalpos()  { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void AddChild(CUI* _pUI) 
    { m_vecChildUI.push_back(_pUI);
      _pUI->m_pParentUI = this; 
    }
    
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }


private:
    void update_child();
    void finalupdate_child();
    //7월 17일 수정 
    //virtual void render_child(HDC _dc);

    void MouseOnCheck();

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);
    virtual void render_child(HDC _dc);

public:
    virtual void MouseOn(); // ui에 마우스 위가 올라올때

    virtual void MouseLbtnDown(); // ui를 마우스 버튼으로 눌렀을때
    virtual void MouseLbtnUp(); // 마우스 누름이 떼졌을 때 
    virtual void MouseLbtnClicked(); // 마우스 클릭을 했을 때 

    //계산기 프로그램에서 
    //
   
    virtual CUI* Clone() = 0;

public:
  
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();


    friend class CUIMgr;

};

