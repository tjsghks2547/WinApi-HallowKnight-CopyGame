#pragma once
#include "CObject.h"
class CDownSlash : public CObject
{
private:

	int				m_iCount; // 7월 1일 추가한 내용

public:
	CDownSlash();
	~CDownSlash();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();

	void CreateHitEffect();


};

