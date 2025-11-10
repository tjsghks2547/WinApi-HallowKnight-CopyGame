#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{
}



void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로, 
	// 큰 값을 열(비트) 로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if(iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if(m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}

	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
	
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{

		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}





}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GenInst()->GetCurScene();

	//지역 변수들 (레퍼런스를 안하면 복사해서 할당되기때문에 복사하는 것의 메모리를 아끼기위해 레퍼런스를 넣어줌)
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for(size_t i = 0; i<vecLeft.size(); ++i)
	{	
		//충돌체 create 안한거 거르기.(즉 CreateCollider를 보유하지않은것들)
		if(vecLeft[i]->GetCollider() == nullptr)
		{
			continue; // i가 증가해서 다음으로감
		}
		for(size_t j =0; j <vecRight.size(); ++j)
		{	//충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (vecRight[j]->GetCollider() == nullptr|| vecLeft[i] == vecRight[j])
			{
				continue; //다시 증감자 문으로 감.아래로안가고
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			//두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			
			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록 (충돌하지 않았다로) 즉 처음 맵에 insert되는경우 이미 insert 되어 있으면 건너뜀
			if(m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// vecLeft[i] == vecRight[i] 이거는 eLeft eRight에 복사되는 값이 같을 때 (ex 몬스터끼리 서로 겹칠때)
			if(isCollision(pLeftCol, pRightCol))
			{
				//현재 충돌 중이다.

				if(iter->second)
				{
					//이전에도 충돌 하고 있었다.
					
					//여기서 충돌처리 다시 처리 (06/15) eventmgr 때 이 코드 추가
					if(vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//근데 둘중 하나가 삭제 예정이라면, 충돌 해제 시켜준다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false; 
					}
					
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// 이전에는 충돌하지 않았다.(맞닥뜨린 상황)
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()) // 둘 다 삭제처리가 아닐경우 충돌하지 않는것으로 하는것
					{
						// 사실 상 충돌이 없었던걸로 취급
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}

					
				}
			}

			else
			{
				// 현재 충돌하고 있지 않다. 
				if (iter->second)
				{
					//이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false; 
				}
			}
			
		}
	}


}

//실제로 충돌하는지 안하는지를 따지는 코드 
bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if(abs(vRightPos.x - vLeftPos.x) <= (vRightScale.x + vLeftScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) <= (vRightScale.y + vLeftScale.y) / 2.f)
	{
		return true;
	}

	return false;
}



