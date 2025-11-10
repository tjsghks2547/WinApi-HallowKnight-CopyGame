#include "pch.h"
#include "CKeyMgr.h"


int g_arrVK[(int)KEY::LAST]
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'N',

	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,


};


CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{

	for(int i = 0; i<(int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE,false });
	}

	//m_vecKey[(int)KEY::LEFT].eState;
	//m_vecKey[(int)KEY::LEFT].bPrevPush;
}

void CKeyMgr::update()

{

	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GenInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); //반환 값은 키보드 포커스가 있는 창에 대한 핸들입니다

	//윈도우 포커싱 중일 때 키 이벤트 동작
	if(hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				//이전에도 눌려있었다 일때
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}

				// 이전에 눌려있지 않았다 일때
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}


				m_vecKey[i].bPrevPush = true; // 다음 프레임 업데이트 될 때 비교할때 쓸 조건을 주기위해
			}

			//키가 안눌여있을때
			else
			{

				if (m_vecKey[i].bPrevPush)
				{
					//이전에 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}


				else
				{
					// 이전에도 안눌려있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;

			}

		}
		// 마우스 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GenInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}

	// 윈도우 포커싱이 아닐 때 
	else
	{
		for (int i =0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			
			else if (KEY_STATE::TAP == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
		}
	}
	
}

