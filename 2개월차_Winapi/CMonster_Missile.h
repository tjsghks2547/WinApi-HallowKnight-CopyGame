#pragma once
#include "CObject.h"

class CTexture;

class CMonster_Missile : public CObject
{
private:
    //6월 16일 추가코드
    CTexture* m_pTex;

    float m_fTheta; // 위 아래 방향개념;

    Vec2  m_vDir;

public:
    void SetDir(bool _fTheta)
    {
        m_fTheta = _fTheta;
    }
public:

    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
public:

    virtual void update() override;
    virtual void render(HDC _dc) override;

    virtual void OnCollisionEnter(CCollider* _pOther);


public:
    CMonster_Missile();
    ~CMonster_Missile();
};

