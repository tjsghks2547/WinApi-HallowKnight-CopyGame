#include "pch.h"
#include "CPhysics.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "C_Core.h"
#include "CCollider.h"


void CPhysics::update(CObject& _Object)
{
	// 오브젝트의 현재 방향 받아옴
	Vec2 vDir = _Object.GetDir();

	// 마찰력 계산 함수
	// 최종 속력을 계산하는 Movement보다 앞에
	// 그렇지 않으면 최종속력 = (현재속력 - 마찰력)이 되기 때문에 미리 정해둔 최대 속력이 안나옴
	Friction(_Object);
	// 최종속도 계산 함수
	Movement(_Object, vDir);

	// 현재 방향을 초기화
	// 다음 입력에 영향을 주지 않기 위함
	_Object.SetDir({ 0, 0 });
}

void CPhysics::Friction(CObject& _Object)
{
	float fDelta = CTimeMgr::GenInst()->GetfDT();
	float fDecel = _Object.GetDecel();
	Vec2 LastVel = _Object.GetCurrVel();
	Vec2 PreVel;
	Vec2 vDir;

	// 현재 방향의 Normalize
	if (_Object.GetCurrVel().x != 0 || _Object.GetCurrVel().y != 0)
		vDir = _Object.GetCurrVel().Normalize();

	// 이전 속도값 저장
	PreVel = LastVel;

	// 현재 속도에서 마찰력만큼 빼줌
	LastVel.x = LastVel.x - vDir.x * fDecel * fDelta;
	LastVel.y = LastVel.y - vDir.y * fDecel * fDelta;

	// 이전 속도와 현재 속도를 곱함
	PreVel = PreVel * LastVel;

	// 곱한 값이 0보다 작다는 것은 마찰력이 적용된 이후 속도값이 0을 지나 반대가 되었다는 것이므로 속도에 0 대입
	if (PreVel.x <= 0) LastVel.x = 0;
	if (PreVel.y <= 0) LastVel.y = 0;

	// 현재 속도 갱신
	_Object.SetCurrVel(LastVel);
}

void CPhysics::Movement(CObject& _Object, Vec2 _vDir)
{
	float fDelta = CTimeMgr::GenInst()->GetfDT();
	Vec2 vLastVel;
	Vec2 PreVel;
	Vec2 vPos = _Object.GetPos();
	Vec2 vPrePos;

	// 현재 방향이 없다면 실행하지 않음
	if (_vDir.x != 0 || _vDir.y != 0)
	{
		// 방향 Normalize
		_vDir.Normalize();

		// 방향 * 가속도값을 구함
		vLastVel.x = _vDir.x * _Object.GetAccel();
		vLastVel.y = _vDir.y * _Object.GetAccel();

		// 최종 속도에 위에서 구한 값 더해줌
		vLastVel.x = _Object.GetCurrVel().x + vLastVel.x * fDelta;
		vLastVel.y = _Object.GetCurrVel().y + vLastVel.y * fDelta;

		// 지금까지 구한 속도값 저장한 뒤 Normalize하여 최종 속도의 방향 벡터 구함
		PreVel = vLastVel;
		PreVel.Normalize();

		// 최종 속도의 Length는 곧 최종 속력이므로 이 값이 미리 정해둔 최대값보다 크면 최종 속도의 방향에 최대 속력값 곱함
		if (vLastVel.Length() >= _Object.GetMaxVel())
		{
			vLastVel.x = PreVel.x * _Object.GetMaxVel();
			vLastVel.y = PreVel.y * _Object.GetMaxVel();
		}

		// 현재 속도 갱신
		_Object.SetCurrVel(vLastVel);
	}
	else // 현재 방향이 없는 경우 실행하는 구문 -> 그냥 최종 속도에 현재 속도를 넣어줌
		vLastVel = _Object.GetCurrVel();

	// 현재 위치 저장
	vPrePos = vPos;
	// 현재 위치에서 최종 속도 더한 다음 위치 저장
	vPos = vPos + vLastVel;

	// 오브젝트의 맵 충돌 변수가 true일 때 함수 실행
	if (_Object.GetMapCollidable())
		MapCollide(_Object, vLastVel, vPrePos, vPos);

	// 현재 위치에서 최종 속도 더하고 그 값을 현재 위치로 갱신
	vPos = vPos + vLastVel;
	_Object.SetPos(vPos);
}



void CPhysics::MapCollide(CObject& _Object, Vec2& _vLastVel, Vec2& _vPrePos, Vec2& _vPos)
{
	Vec2 vDistance;
	Vec2 vColHalfScale;
	Vec2 vWindow;

	// 오브젝트의 Collider의 Scale과 창 크기 받아옴
	vColHalfScale.x = _Object.GetCollider()->GetScale().x / 2.f;
	vColHalfScale.y = _Object.GetCollider()->GetScale().y / 2.f;
	vWindow.x = CCore::GenInst()->GetResolution().x;
	vWindow.y = CCore::GenInst()->GetResolution().y;

	// 최종 위치값과 창 크기의 좌표값을 비교해서 창 밖일 경우의 위치값 재계산 - x좌표의 경우
	if (_vPos.x - vColHalfScale.x <= 0)
	{
		vDistance.x = 0 - (_vPrePos.x - vColHalfScale.x);
		_vPos.x = _vPrePos.x + vDistance.x;
	}
	else if (_vPos.x + vColHalfScale.x >= vWindow.x)
	{
		vDistance.x = vWindow.x - (_vPrePos.x + vColHalfScale.x);
		_vPos.x = _vPrePos.x + vDistance.x;
	}

	// 최종 위치값과 창 크기의 좌표값을 비교해서 창 밖일 경우의 위치값 재계산 - y좌표의 경우
	if (_vPos.y - vColHalfScale.y <= 0)
	{
		vDistance.y = 0 - (_vPrePos.y - vColHalfScale.y);
		_vPos.y = _vPrePos.y + vDistance.y;
	}
	else if (_vPos.y + vColHalfScale.y >= vWindow.y)
	{
		vDistance.y = vWindow.y - (_vPrePos.y + vColHalfScale.y);
		_vPos.y = _vPrePos.y + vDistance.y;
	}
}