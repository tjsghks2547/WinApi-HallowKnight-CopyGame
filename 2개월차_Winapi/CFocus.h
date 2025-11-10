#pragma once
#include "CObject.h"
class CFocus :
    public CObject
{

	int				i_Count; // 7월 1일 추가한 내용

public:
	CFocus();
	~CFocus();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();

};

