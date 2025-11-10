#include "pch.h"
#include "CSceneFinalbossVideo.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CObject.h"
#include "C_Core.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CStartBackGround.h"
#include "CStartCusor.h"
#include "CResMgr.h"

CSceneFinalbossVideo::CSceneFinalbossVideo()
{
	m_hVideo = MCIWndCreate(CCore::GenInst()->GetMainHwnd(), nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR
		, L"C:\\Users\\tjsgh\\Desktop\\7_18\\7_18\\x64\\Release\\content\\sound\\final_boss_cut_scene.wmv");
}

CSceneFinalbossVideo::~CSceneFinalbossVideo()
{

}


void CSceneFinalbossVideo::update()
{

	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
	{
		ChangeScene(SCENE_TYPE::FINAL);
		return;
	}

}

void CSceneFinalbossVideo::Enter()
{
	

	MoveWindow(m_hVideo, 0, 0, 1280, 760, FALSE);
	MCIWndPlay(m_hVideo);

	
}

void CSceneFinalbossVideo::Exit()
{

}

