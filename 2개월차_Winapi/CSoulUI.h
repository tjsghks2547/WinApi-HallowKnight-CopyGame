#pragma once
#include "CUI.h"

class CTexture;
class CSoulUI : public CUI
{

private:
    CTexture* m_pTex;
    CTexture* m_pSoulUiTex;

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CSoulUI();
    ~CSoulUI();

public:
    CLONE(CSoulUI);
};

