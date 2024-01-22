#pragma once

#include "UI.h"

class QuickStats;
class SkillUI;
class InvenUI;

class QuickSlotUI :
    public UI
{
public:
    QuickSlotUI();
    ~QuickSlotUI();

	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;
	void Release()		override;

	void SetQuickStats(QuickStats* const pQuickStats) { m_pQuickStats = pQuickStats; }
	void SetSkillUI(SkillUI* const pSkillUI) { m_pSkillUI = pSkillUI; }
	void SetInvenUI(InvenUI* const _pInvenUI) { m_pInvenUI = _pInvenUI; }
	void Set_Picking_null() { 
		if (!m_bThisFramePicking)
			m_pPicking = nullptr; 
	}

private:
	void Check_Slots();

private:
	QuickStats* m_pQuickStats;
	vector<Vec2> m_vecRenderPos;
	vector<JoTexture*> m_vecKeyTex;

	SkillUI* m_pSkillUI;
	InvenUI* m_pInvenUI;

	Enrollable* m_pPicking;
	int m_iNowPickingIdx;
	bool m_bThisFramePicking;
};

