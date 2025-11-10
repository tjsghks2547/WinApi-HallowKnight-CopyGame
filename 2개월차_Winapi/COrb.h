#pragma once
#include "CObject.h"
class COrb :public CObject
{

	int				i_Count; // 7월 1일 추가한 내용

public:
	COrb();
	~COrb();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_sound();
	void update_animation();
};

