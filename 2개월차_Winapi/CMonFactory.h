#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,

};

class CMonFactory
{

public:
	//정적 맴버 함수로 객체 없어도 호출할 수 있게 해줌 
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);


private:
	CMonFactory() {}
	~CMonFactory() {}

};

