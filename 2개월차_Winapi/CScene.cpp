#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CPathMgr.h"

#include "CCamera.h"
#include "C_Core.h"


CScene::CScene()
	:m_iTileX(0)
	,m_iTileY(0)
	,m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for(UINT i = 0; i<(UINT)GROUP_TYPE::END; ++i)
	{
		for(size_t j = 0; j < m_arrObj[i].size(); ++j)
			{
				// m_arrObj[i] 그룹 벡터의 j 물체 삭제
				delete m_arrObj[i][j];
			}
	}
}


void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for(UINT i =0 ; i< (UINT)GROUP_TYPE::END; ++i)
	{
		for(size_t j = 0; j< m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead()) // 죽은 상태가 아닌것만 업데이트
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate() // 작업을 마무리 하는 시점
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// 파이널 업데이트는 논리적인 마무리 작업이기 때문에  if (m_arrObj[i][j]->IsDead()) 문장을 뺌
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}


void CScene::render(HDC _dc) // 해당 장면에 들어가있는 오브젝트 전부 렌더 하는 코드
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if((UINT)GROUP_TYPE::TILE == i)
		{
			render_tile(_dc);
			continue;
		}

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter!= m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}

			else
			{
				iter = m_arrObj[i].erase(iter);
				
			}
		}
	}
}

void CScene::render_tile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	
	Vec2 vCamLook = CCamera::GenInst()->GetLookAt();
	Vec2 vResolution = CCore::GenInst()->GetResolution();
	Vec2 vLeftTop  = vCamLook  - (vResolution / 2.f);

	int iTileSize = TILE_SIZE; 

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;




	// 화면에서 뽑아낼 타일들의 가로와 높이 전체 길이 
	int iClientWidth = ((int)vResolution.x / iTileSize) + 1; 
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;

	for(int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for(int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			//영역이서 삐져 나가는 경우 예외처리 
			if(iCurCol < 0 || (int)m_iTileX <= iCurCol
				|| iCurRow <0 || (int)m_iTileY <= iCurRow)
			{
				continue;
			}

			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			vecTile[iIdx]->render(_dc);
		}
	}

}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i =0; i<(UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);
	
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;
	
	CTexture* pTileTex = CResMgr::GenInst()->LoadTexture(L"Tile", L"texture\\Tile\\Tile64.bmp");



	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j <_iXCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);


		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GenInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// wstring 쓰므로 2바이트 오픈 방식을 사용
	// 커널 오브젝트 
	FILE* pFile = nullptr;

	//L"rb"는 읽는모드로 파일을 로드하는것 
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile들 만들어두기 
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);

}

