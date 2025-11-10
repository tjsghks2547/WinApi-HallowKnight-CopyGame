#include "pch.h"
#include "CItemCusor.h"
#include "CPlayerMgr.h"
#include "SelectGDI.h"


CItemCusor::CItemCusor()
	:CUI(false)
{

}

CItemCusor::~CItemCusor()
{

}


void CItemCusor::update()
{

}

void CItemCusor::render(HDC _dc)
{
	SelectGDI select1(_dc, PEN_TYPE::WHITE);
	SelectGDI select2(_dc, BRUSH_TYPE::HOLLOW);

	
	if(CPlayerMgr::GenInst()->GetInventoryStatus())
	{
		switch (CPlayerMgr::GenInst()->GetItemCusor())
		{
		
		case -1:
			Rectangle(_dc
				, (int)(250)
				, (int)(200)
				, (int)(350)
				, (int)(300));
			break;


		case 0:
			Rectangle(_dc
				, (int)(100)
				, (int)(200)
				, (int)(200)
				, (int)(300));
			break;

		case 1:
			Rectangle(_dc
				, (int)(170)
				, (int)(360)
				, (int)(270)
				, (int)(460));
			break;
		case 2:
			Rectangle(_dc
				, (int)(290)
				, (int)(360)
				, (int)(390)
				, (int)(460));
			break;

		case 3:
			Rectangle(_dc
				, (int)(410)
				, (int)(360)
				, (int)(510)
				, (int)(460));
			break;

		case 4:
			Rectangle(_dc
				, (int)(530)
				, (int)(360)
				, (int)(630)
				, (int)(460));
			break;
		}
	}

}


