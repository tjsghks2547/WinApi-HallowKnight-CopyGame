#pragma once
#include "CObject.h"

class CTexture;

class CStartCusor : public CObject
{
    CTexture* m_pCusorTex;


private:
    int       m_iCount;
    bool      m_bSoundPlay;

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CStartCusor();
    ~CStartCusor();


};


