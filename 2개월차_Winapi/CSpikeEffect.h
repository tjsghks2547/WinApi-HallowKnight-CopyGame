#pragma once
#include "CObject.h"

enum class SPIKE_STATE
{
	SPIKE_EFFECT_ANTICIPATE,
	SPIKE_EFFECT_ATTACK,
};


class CSpikeEffect : public CObject
{
	int				i_Count; // 7월 1일 추가한 내용
	bool			m_bSoundPlayed;


	SPIKE_STATE     m_eCurState;
	SPIKE_STATE		m_ePreState;

	

public:
	CSpikeEffect();
	~CSpikeEffect();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

private:
	void update_state();
	void update_sound();
	void update_animation();
};

