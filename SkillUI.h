#pragma once
#include "MovableUI.h"

#define SKILL_SLOT 12

class Enrollable;
class SkillStats;
class QuickSlotUI;

class SkillUI : public MovableUI
{
    struct RenderInfo
    {
        Vec2 vIconOffset = {};
        Vec2 vSkillNameOffset = {};
        Vec2 vPointOffSet = {};
        Vec2 vButtonOffSet = {};
    };

public:
    SkillUI();
    ~SkillUI();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();
    void Release();

    void SetSkillStats(SkillStats* _pStats) { m_pSkillStats = _pStats; }
    void SetQuickSlotUI(QuickSlotUI* _pQuickSlot) { m_pQuickSlot = _pQuickSlot; }
    void Set_Picking_null() {  if (!m_bThisFramePicking) m_pPicking = nullptr;}

    Enrollable* GetPicking() { return m_pPicking; }

    bool KeyCheck() override { return KeyMgr::GetKeyDown(eKeyCode::K); }
    void OnInActive() override;
private:
    void Check_Slots();
    void Check_Button();

private:
    JoTexture* m_pActiveButtonTex;
    JoTexture* m_pInActiveButtonTex;

    SkillStats* m_pSkillStats;
    vector<RenderInfo> m_vecRenderInfo;
    Vec2 m_vRemainOffset;

    QuickSlotUI* m_pQuickSlot;

    Enrollable* m_pPicking;

    bool m_bThisFramePicking;

};

