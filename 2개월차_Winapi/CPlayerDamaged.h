#pragma once
#include "CObject.h"
class CPlayerDamaged :
    public CObject
{

private:
	int		m_iCount;
public:
	CPlayerDamaged();
	~CPlayerDamaged();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();
};

