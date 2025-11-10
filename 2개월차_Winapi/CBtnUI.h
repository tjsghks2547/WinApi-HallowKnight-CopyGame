#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

//함수 포인터 쓸때는 전방선언 하면 안됨! 그냥 include 해야함!
typedef  void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef  void(CScene::*SCENE_MEMFUNC)(void);
typedef  void(CObject::*OBJECT_MEMFUNC)(void);


class CBtnUI :
    public CUI
{
private:
    BTN_FUNC         m_pFunc; 
    DWORD_PTR        m_param1;
    DWORD_PTR        m_param2;

    SCENE_MEMFUNC    m_pSceneFunc;
    CScene*          m_pSceneInst; 

public:
    virtual void MouseOn(); // ui에 마우스 위가 올라올때
    virtual void MouseLbtnDown(); // ui를 마우스 버튼으로 눌렀을때
    virtual void MouseLbtnUp(); // 마우스 누름이 떼졌을 때 
    virtual void MouseLbtnClicked(); // 마우스 클릭을 했을 때 

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI);

public:

    CBtnUI();
    ~CBtnUI();
};

