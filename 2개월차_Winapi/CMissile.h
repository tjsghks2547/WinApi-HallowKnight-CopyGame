#pragma once
#include "CObject.h"
#include "CTexture.h"

class CMissile :
    public CObject
{

private:

    //6월 16일 이후 추가한 코드 
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
    //virtual void OnCollision(CCollider* _pOther);
    //virtual void OnCollisionExit(CCollider* _pOther);
   
public:
    CMissile();
    ~CMissile();

};

