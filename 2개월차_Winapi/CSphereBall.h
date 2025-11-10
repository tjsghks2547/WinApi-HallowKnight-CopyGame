#pragma once
#include "CObject.h"
class CSphereBall :
    public CObject
{
	int				i_Count; // 7월 1일 추가한 내용

public:
	CSphereBall();
	~CSphereBall();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();
};

