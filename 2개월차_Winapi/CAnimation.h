#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm // 프레임 별로 기억해야 할 정보들 (1O개라면 10개의 구조체가 있어야함)
{
	Vec2 vLT;  //좌상단 정보
	Vec2 vSlice; // 짜를 값 
	Vec2 vOffset; // 
	float  fDuration; // 시간 값

};


class CAnimation
{
private:
	wstring				m_strName; 
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;  // Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;   // 모든 프레임 정보
	int					m_iCurFrm;  // 현재 프레임 
	float				m_fAccTime; // 시간 누적

	bool				m_bFinish; //재생 끝에 도달여부
public:
	
	const wstring& GetName() { return m_strName; }
	bool IsFinish()			 { return m_bFinish; }
	void SetFinish(bool _bFinish) { m_bFinish = _bFinish; }


	void SetFrame(int _iFrameIdx) 
	{
		m_bFinish = false; 
		m_iCurFrm = _iFrameIdx; 
		m_fAccTime = 0.f;
	}

	// 7월 1이후 추가하는 코드 
	int GetCurrentFrm() { return m_iCurFrm; }
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }


private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	


public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
public:

	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, 
				Vec2 _vStep, float _fDuration, UINT _iFrameCount);



	//fDuration은 애니메이션 프레임 유지 시간 
	// _vLT 는 애니메이션 좌상단 시작 지점 
	// vSliceSize는 다음 애니메이션의 사이즈 크기 
	// _vStep은 다음 애니메이션까지의 거리 ( = 간격) 
	// iFrameCount는 몇개의 애니메이션이 존재하는지 
};

