#include "pch.h"
#include "CPlayerMgr.h"
#include "CUI.h"


CPlayerMgr::CPlayerMgr()
	:vPlayerPos()
	, m_iPage(0)
	, m_binventoryOnOff(false)
	, m_iItemCusor(0)
	, m_bGroundHit(false)
	, m_iChangeSceneCount(0)
	, m_iGeoCount(0)
	, m_bStoreOnOff(false)
	, m_iStoreCusor(0)
	, m_bEndingOnOff(true)
	, m_i2Page(0)
{
	

}

CPlayerMgr::~CPlayerMgr()
{

}