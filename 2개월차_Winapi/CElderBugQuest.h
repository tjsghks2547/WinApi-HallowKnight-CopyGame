#pragma once
#include "CUI.h"

class CTexture;

class CElderBugQuest :
    public CUI
{
private:

    CTexture* m_pTex; 

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CElderBugQuest();
    ~CElderBugQuest();

public:
    CLONE(CElderBugQuest);
};

