#pragma once
#include <vector>
using std::vector;

#include <string>

using std::string;
using std::wstring;


// static 키워드가 붙어 한번만 초기화를진행 객체를 생성하는 static type mgr에서 볼 수 있음
#define SINGLE(type) public:\
							 static type* GenInst()\
							 {\
								static type mgr;\
								 return &mgr;\
							}\
							private:\
								type();\
								~type();


#define fDT CTimeMgr:: GenInst()->GetfDT()
#define DT CTimeMgr:: GenInst()->GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key,state) CKeyMgr::GenInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key,KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key,KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GenInst()->GetMousePos()

#define TILE_SIZE 64


#define PI 3.1454765f


enum class GROUP_TYPE
{
	DEFAULT,
	

	GROUND,
	BACKGROUND,
	
	
	

	TILE,
	
	
	
	
	SKILLEFFECT,
	MONSTER,
	ITEM,

	NPC,
	PLAYER,

	PROJ_PLAYER, // 플레이어의 투사체 
	PROJ_MONSTER, // 몬스터의 투사체

	UI = 31,
	END = 32, 
};

enum class SCENE_TYPE
{
	GAME_START,
	TOOL,
	START,
	TOWN,
	THIRD,
	FINAL,
	STAGE_01,
	STAGE_02,
	FINAL_BOSS_CUT_SCENE,
	END_SCEEN,

	END
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	WHITE,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,

	END,
};

enum class MON_STATE
{
	IDLE,
	STARTLE,
	PATROL,
	TRACE,
	ATTACK_ANTICIAPTE,
	ATTACK,
	TURN,
	RUSH,
	RUN,
	WALK,
	DEAD,
};