#include "pch.h"
#include "CMissile2.h"
#include "CTimeMgr.h"


CMissile2::CMissile2()
	:m_fTheta(PI/4.F)
{
	CreateCollider();
}

CMissile2::~CMissile2()
{

}


void CMissile2::update()
{
	Vec2 vPos = GetPos();

	//대각선으로 발사.
	/*vPos.x += 600.f *cosf(m_fTheta)* fDT;
	vPos.y -= 600.f *(sqrt(2)/2) * fDT * sinf(m_fTheta);*/

	SetPos(vPos);

}

void CMissile2::render(HDC _dc) // 총알 모양 구현 
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc,
		(int)(vPos.x - vScale.x / 2.f),  // 왼쪽 상단 x
		(int)(vPos.y - vScale.y / 2.f),  // 왼쪽 상단 y
		(int)(vPos.x + vScale.x / 2.f),  // 오른쪽 하단 x
		(int)(vPos.y + vScale.y / 2.f)); // 오른쪽 하단 y
}