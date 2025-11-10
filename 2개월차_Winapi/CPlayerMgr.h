#pragma once

class CUI;

class CPlayerMgr
{
	SINGLE(CPlayerMgr)



public:

	void init() { ; }
	
	void SetCurPlayerPos(Vec2 _PlayerPos) { vPlayerPos = _PlayerPos; }
	Vec2 GetCurPlayerPos() { return vPlayerPos; }


	int GetPlayerHp() { return m_iHp; }
	void SetPlayerHp(int _hp) { m_iHp = _hp; }
	void DecreaseHp(int _hp) { m_iHp -= _hp; }
	void IncreaseHp(int _hp) { m_iHp += _hp; }

	int GetPlayerMp() { return m_iMp; }
	void SetPlayerMp(int _Mp) { m_iMp = _Mp; }
	void DecreaseMp(int _Mp) { m_iMp -= _Mp; }
	void IncreaseMp(int _Mp) { m_iMp += _Mp; }

	void QuestPageIncrease(int _page) { m_iPage += 1; }
	void QuestPageDecrease(int _page) { m_iPage -= 1; }

	int  GetQuestPage() { return m_iPage; }

	void SetInventoryOnOff() { m_binventoryOnOff = !m_binventoryOnOff; }
 
	bool GetInventoryStatus() { return m_binventoryOnOff; }


	vector<CUI*>&  GetItemList() { return m_vItemList;}
	vector<CUI*>& GetEquipList() { return m_vEquipList; }

	
	int	 GetItemCusor() { return m_iItemCusor; }
	
	void IncreaseItemCusor() { m_iItemCusor += 1; }
	void DecreaseItemCusor() { m_iItemCusor -= 1; }

	bool GetGroundHit() { return m_bGroundHit; }
	void SetGroundHit(bool _b) { m_bGroundHit = _b; }

	int GetChangeSceneCount() { return m_iChangeSceneCount; }
	void SetChangeSceneCount(int _i) { m_iChangeSceneCount = _i; }

	int GetGeoCount() { return m_iGeoCount; }
	void SetGeoCount(int _i) { m_iGeoCount = _i; }
	void IncreaseGeo(int _i) { m_iGeoCount += _i; }
	void DecreaseGeo(int _i) { m_iGeoCount -= _i; }


	bool GetStoreOnOff() { return m_bStoreOnOff; }
	void SetStoreOnOff() { m_bStoreOnOff = !m_bStoreOnOff; }

	
	int  GetStoreCusor() { return m_iStoreCusor; }
	void SetStoreCusor(int _i) { m_iStoreCusor = _i; }

	bool GetFinalEndingOnOff() { return m_bEndingOnOff; }
	void SetFinalEndingOnOff(bool _b) { m_bEndingOnOff = _b; }

	void QuestPage2Increase(int _page) { m_i2Page += 1; }
	void QuestPage2Decrease(int _page) { m_i2Page -= 1; }

	int  GetQuestPage2() { return m_i2Page; }

private:

	Vec2  vPlayerPos;
	int   m_iHp; 
	int   m_iMp;
	int   m_iPage;

	bool  m_binventoryOnOff; 
	bool  m_bGroundHit;

	int   m_iItemCusor;
	int   m_iChangeSceneCount;

	int   m_iGeoCount;
	bool  m_bStoreOnOff;

	int   m_iStoreCusor;

	bool  m_bEndingOnOff;

	int   m_i2Page;



private:

	vector<CUI*>  m_vItemList; // 아이템 공간 8개 
	vector<CUI*>  m_vEquipList; //장비템 공간 2개

	vector<CUI*>::iterator m_viteritem;

};

