#pragma once
#include "CObject.h"
class CHornetDashEffect :
    public CObject
{
	int				i_Count; // 7월 1일 추가한 내용
	int				m_iDir; // 플레이어 방향
	int				m_iPrevDir; // 이전 플레이어 방향 

public:
	CHornetDashEffect();
	~CHornetDashEffect();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();

public:

	void SetDir(int _iDir) { m_iDir = _iDir; }
};

