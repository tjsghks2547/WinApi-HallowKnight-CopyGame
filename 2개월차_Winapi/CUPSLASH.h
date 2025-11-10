#pragma once
#include "CObject.h"
class CUPSLASH :
    public CObject
{
private:

	int				m_iCount; // 7월 1일 추가한 내용

public:
	CUPSLASH();
	~CUPSLASH();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();
};

