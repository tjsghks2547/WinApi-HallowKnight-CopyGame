#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CCamera.h"




CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	,m_pTex(nullptr)
	,m_iCurFrm(0)
	,m_fAccTime(0.f)
	,m_bFinish(false)
{

}

CAnimation::~CAnimation()
{
	
}

void CAnimation::update()
{
	if (m_bFinish)
		return; 


	m_fAccTime += fDT; // 누적 시간 (실제 흘러간 시간)

	if(m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		


		if(m_vecFrm.size() <= m_iCurFrm)
		{
			//애니메이션이 한번 쭉 됬을 때 
			m_iCurFrm = -1;
			m_bFinish = true; 
			m_fAccTime = 0.f;
			return;
		}


		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
		
		
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;
	CObject* pObj =  m_pAnimator->GetObj();

	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Postition에서 Offset 만큼 추가 이동위치 
	

	// 렌더링 좌표로 변환 (카메라 기준) 
	vPos = CCamera::GenInst()->GetRenderPos(vPos);

	/*TransparentBlt(_dc
					, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
					, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
					, (int)m_vecFrm[m_iCurFrm].vSlice.x
					, (int)m_vecFrm[m_iCurFrm].vSlice.y
					, m_pTex->GetDc()
					, (int)m_vecFrm[m_iCurFrm].vLT.x
					, (int)m_vecFrm[m_iCurFrm].vLT.y
					, (int)m_vecFrm[m_iCurFrm].vSlice.x
					, (int)m_vecFrm[m_iCurFrm].vSlice.y
					, RGB(255, 0, 255)
				   );
	 */
	//// 알파블랜딩 예시 
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255; // 전역적으로 적용되는 알파값  (투명도)




	// 카메라 영향받는지 안받는지를 적는곳 
	if(pObj->GetCamAff()==false)
	{
		Vec2 vPos2 = pObj->GetPos();
		Vec2 vScale2 = pObj->GetScale();

		AlphaBlend(_dc
			, (int)(vPos2.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
			, (int)(vPos2.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, m_pTex->GetDc()
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, bf);

	}
	else
	{
		AlphaBlend(_dc
			, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
			, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, m_pTex->GetDc()
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, bf);
	}

	

}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	
	for(UINT i=0; i<_iFrameCount; ++i)
	{
		frm.fDuration = _fDuration; 
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);


	}

}


