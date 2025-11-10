#pragma once
#include "CObject.h"
class CMissile2 :
    public CObject
{

private:

    float m_fTheta; // 위 아래 방향개념;

public:
    void SetDir(bool _fTheta)
    {
        m_fTheta = _fTheta;
    }

public:

    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CMissile2();
    ~CMissile2();


};

