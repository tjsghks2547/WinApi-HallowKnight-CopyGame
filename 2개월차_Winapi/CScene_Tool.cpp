#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "C_Core.h"
#include "CResMgr.h"

#include "resource.h"
#include "CSceneMgr.h"

#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"
#include "CPathMgr.h"



void ChangeScene(DWORD_PTR, DWORD_PTR);


CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)
{

}

CScene_Tool::~CScene_Tool()
{

}



void CScene_Tool::Enter()
{

	// 툴 Scene 에서 사용할 메뉴를 붙인다. 
	CCore::GenInst()->DockMenu();
	
	//타일 생성
	CreateTile(5, 5);

	//UI 하나 만들어보기 
	Vec2 vResolution = CCore::GenInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f,150.f));
	pPanelUI->SetPos(Vec2(vResolution.x- pPanelUI->GetScale().x, 0.f));
	

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f,0.f));
	//복사본 UI만 동작하도록 설정하여 주석처리
	//pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this,(SCENE_MEMFUNC)& CScene_Tool::SaveTileData);


	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	//복사
	/*CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f,0.f));
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);
	AddObject(pClonePanel, GROUP_TYPE::UI);*/


	//m_pUI = pClonePanel;


	//// Camera Look 지정
	//Vec2 vResolution = CCore::GenInst()->GetResolution();

	//카메라가 중앙을 보도록 설정한 것 ( 해상도의 절반 위치니깐 ) 
	CCamera::GenInst()->SetLookAt(vResolution / 2.f); // 해상도 절반 위치 
}




void CScene_Tool::update()
{
	//CScene::update();
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	//이벤트 매니저를 통해서 호출하고 그 다음 SceneMgr의 Change
	//	ChangeScene(SCENE_TYPE::START);
	//}
	CScene::update();
	SetTileIdx();

	if(KEY_TAP(KEY::LSHIFT))
	{
		//CUIMgr::GenInst()->SetFocusedUI(m_pUI);
		SaveTileData();
	}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN)) 
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GenInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;


		if( vMousePos.x < 0 || iTileX <= iCol 
			|| vMousePos.y < 0.f || iTileY<= iRow)
		{
			return;
		}
		UINT iIdx = iRow * iTileX + iCol; 

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	} 


}

void CScene_Tool::SaveTileData()
{


	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GenInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GenInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal 방식 
	if (GetSaveFileName(&ofn))
	{
		//CPathMgr::GenInst()->GetRelativePath(szName);
		SaveTile(szName);

	}

	
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	
	// wstring 쓰므로 2바이트 오픈 방식을 사용
	// 커널 오브젝트 
	FILE* pFile = nullptr; 

	//L"w"는 쓰는모드라 파일을 만드는것 
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");
	assert(pFile);

	// 타일 가로세로 개수 저장 
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	
	for(size_t i =0; i<vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);

}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GenInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GenInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal 방식 
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GenInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}


void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

void CScene_Tool::Exit()
{
	CCore::GenInst()->DivideMenu();

	DeleteAll();
}

// ==========================
// Tile Count Window Proc
// ==========================


INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			//다디얼로그 안에 있는 특정 데이터를 가져옴 
			UINT iXCount = GetDlgItemInt(hDlg,IDC_EDIT1,nullptr,false); // INT는 정수를 가져오겠다는 의미
			UINT iYCount = GetDlgItemInt(hDlg,IDC_EDIT2,nullptr,false); // INT는 정수를 가져오겠다는 의미

			CScene* pCurScene = CSceneMgr::GenInst()->GetCurScene();

			// ToolScene 확인 ( ToolScene에서만 사용하게 하기 위해서 ) 
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}