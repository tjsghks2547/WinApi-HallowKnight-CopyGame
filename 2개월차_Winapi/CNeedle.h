#pragma once
#include "CObject.h"

enum class NEEDLE_STATE
{
	THROW_NEEDLE,
	GETBACK_NEEDLE,
};

class CNeedle :
    public CObject
{
	int				i_Count; // 7월 1일 추가한 내용
	int				m_iDir; // 플레이어 방향
	int				m_iPrevDir; // 이전 플레이어 방향 

	NEEDLE_STATE    m_eCurState;
	NEEDLE_STATE    m_ePreState;

public:
	CNeedle();
	~CNeedle();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_animation();

public:
	void SetDir(int _iDir) { m_iDir = _iDir; }

};

