#include "pch.h"
#include "CBackGround.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "C_Core.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CBackGround::CBackGround()
	
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"BackGround_1", L"texture\\Map\\stage1.bmp");
}

CBackGround::~CBackGround()
{

}


void CBackGround::update()
{

}

void CBackGround::render(HDC _dc)
{
	Vec2 vPos = CPlayerMgr::GenInst()->GetCurPlayerPos(); // 배경 좌표 0,0 


	//if(CCamera::GenInst()->GetTarget()!=nullptr)
	//{
	//	vPos = CCamera::GenInst()->GetLookAt();
	//}
	
	

	//렌더링 좌표로 변환 (카메라 기준) 
	//vPos = CCamera::GenInst()->GetRenderPos(vPos);
	
	
	//Vec2 vPos = CCamera::GenInst()->GetTarget()->GetPos();
	

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();


	//CCamera::GenInst()->SetLookAt(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 1000, CPlayerMgr::GenInst()->GetCurPlayerPos().y));

	if((8056.f <CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& 11110.f > CPlayerMgr::GenInst()->GetCurPlayerPos().x)
		&& 2210 > CPlayerMgr::GenInst()->GetCurPlayerPos().y)
	{

		BitBlt(_dc
			, 0
			, 0
			, 1280
			, 760
			, m_pTex->GetDc()
			, (int)(vPos.x-760) //(vPos.x - 760)
			, (int)(CCamera::GenInst()->GetLookAt().y-390) // 1500 
			, SRCCOPY);

	}

	

	else
	{
		BitBlt(_dc
			, 0
			, 0
			, 1500
			, 1500
			, m_pTex->GetDc()
			, (int)(vPos.x - 760)
			, (int)(vPos.y - 380)
			, SRCCOPY);
	}
	
	
	
	
	///*TransparentBlt(_dc
	//	, (int)((vPos.x - (float)(iWidth / 2)))
	//	, (int)((vPos.y - (float)(iHeight / 2)))
	//	, iWidth
	//	, iHeight
	//	, m_pTex->GetDc()
	//	, 0, 0, iWidth, iHeight, RGB(255, 255, 255));*/

	//Vec2 vRenderPos = CCamera::GenInst()->GetRenderPos(GetPos());
	//Vec2 vScale = GetScale();


	//BitBlt(_dc
	//	, (int)vRenderPos.x-640
	//	, (int)vRenderPos.y-380
	//	, 1280
	//	, 2000
	//	, m_pTex->GetDc()
	//	, (int)vRenderPos.x
	//	, (int)vRenderPos.y
	//	,SRCCOPY);


	/*BitBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, (int)vScale.x
		, (int)vScale.y
		, m_pTileTex->GetDc()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);*/

}

