#pragma once
#include "CObject.h"
class CAttackWave :
    public CObject
{

	int				m_iDir; // 보스  방향
	int				m_iPrevDir; // 이전 보스 방향 
	int				m_iCount; // 7월 1일 추가한 내용

public:
	CAttackWave();
	~CAttackWave();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();
	
public:
	void SetDir(int _iDir) { m_iDir = _iDir; }

	ULONGLONG dwtime;
};

