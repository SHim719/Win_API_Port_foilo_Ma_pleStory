#include "UIMgr.h"
#include "SkillUI.h"
#include "HudUI.h"
#include "QuickSlotUI.h"
#include "InvenUI.h"
#include "EquipUI.h"
#include "StatUI.h"
#include "ShopUI.h"
#include "MyDialogBox.h"
#include "DeathUI.h"
#include "QuestMgr.h"
#include "DamageNumUI.h"


UI* UIMgr::m_arrUIs[] = {};
list<UI*> UIMgr::m_ActiveUIList = {};
list<UI*> UIMgr::m_inActiveUIList = {};
bool UIMgr::m_bMouseUsed = false;
bool UIMgr::m_bCanUseUI = false;

void UIMgr::Initialize()
{
	SkillUI* pSkillUI = new SkillUI;
	pSkillUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Skill] = pSkillUI;

	HudUI* hud = new HudUI;
	hud->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_HUD] = hud;

	InvenUI* pInvenUI = new InvenUI;
	pInvenUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Inven] = pInvenUI;

	QuickSlotUI* pQuickSlotUI = new QuickSlotUI;
	pQuickSlotUI->Initialize();
	pQuickSlotUI->SetSkillUI(pSkillUI);
	pQuickSlotUI->SetInvenUI(pInvenUI);
	m_arrUIs[(UINT)UI_Enums::UI_QuickSlot] = pQuickSlotUI;

	EquipUI* pEquipUI = new EquipUI;
	pEquipUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Equip] = pEquipUI;

	pInvenUI->SetEquipUI(pEquipUI);
	pEquipUI->SetInvenUI(pInvenUI);

	StatUI* pStatUI = new StatUI;
	pStatUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Stat] = pStatUI;

	ShopUI* pShopUI = new ShopUI;
	pShopUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Shop] = pShopUI;

	MyDialogBox* pDialBox = new MyDialogBox;
	pDialBox->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Dialog] = pDialBox;

	DeathUI* pDeathUI = new DeathUI;
	pDeathUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_Death] = pDeathUI;

	DamageNumUI* pDamageNumUI = new DamageNumUI;
	pDamageNumUI->Initialize();
	m_arrUIs[(UINT)UI_Enums::UI_DamageNum] = pDamageNumUI;

	m_inActiveUIList.push_back(pSkillUI);
	m_inActiveUIList.push_back(pInvenUI);
	m_inActiveUIList.push_back(pEquipUI);
	m_inActiveUIList.push_back(pStatUI);
	m_inActiveUIList.push_back(pDamageNumUI);
}

void UIMgr::Update()
{
	if (!m_bCanUseUI)
		return;

	UIkeyCheck();

	auto focusUiIter = m_ActiveUIList.rend();

	for (auto it = m_ActiveUIList.rbegin(); it != m_ActiveUIList.rend(); ++it)
	{
		UI* ui = *it;
		ui->Update();

		if (m_bMouseUsed && focusUiIter == m_ActiveUIList.rend())
			focusUiIter = it;
	}

	if (focusUiIter != m_ActiveUIList.rend())
	{
		UI* focusUI = *focusUiIter;
		m_ActiveUIList.erase(--focusUiIter.base());
		m_ActiveUIList.push_back(focusUI);
	}

	
	m_arrUIs[(UINT)UI_Enums::UI_QuickSlot]->Update();
	m_arrUIs[(UINT)UI_Enums::UI_Shop]->Update();
	m_arrUIs[(UINT)UI_Enums::UI_HUD]->Update();
	m_arrUIs[(UINT)UI_Enums::UI_Dialog]->Update();
	m_arrUIs[(UINT)UI_Enums::UI_Death]->Update();

	m_bMouseUsed = false;
}

void UIMgr::Render()
{
	if (!m_bCanUseUI)
		return;

	m_arrUIs[(UINT)UI_Enums::UI_HUD]->Render();
	m_arrUIs[(UINT)UI_Enums::UI_QuickSlot]->Render();
	m_arrUIs[(UINT)UI_Enums::UI_Shop]->Render();
	m_arrUIs[(UINT)UI_Enums::UI_Dialog]->Render();
	m_arrUIs[(UINT)UI_Enums::UI_Death]->Render();

	Quest* pQuest = QuestMgr::Get_NowQuest();
	if (pQuest)
		pQuest->Render();
	

	for (UI* ui : m_ActiveUIList)
		ui->Render();
}

void UIMgr::Release()
{
	for (auto& ui : m_arrUIs)
		Safe_Delete<UI*>(ui);
}

bool UIMgr::IsActiveUIs()
{
	return	!m_ActiveUIList.empty() 
		|| static_cast<ShopUI*>(m_arrUIs[(UINT)UI_Enums::UI_Shop])->IsActive()
		|| static_cast<MyDialogBox*>(m_arrUIs[(UINT)UI_Enums::UI_Dialog])->IsActive();
}

void UIMgr::UIkeyCheck()
{
	UI* activeUI = nullptr;

	for (auto it = m_inActiveUIList.begin(); it != m_inActiveUIList.end(); )
	{
		if ((*it)->KeyCheck())
		{
			(*it)->OnActive();
			activeUI = *it;
			it = m_inActiveUIList.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}

	for (auto it = m_ActiveUIList.begin(); it != m_ActiveUIList.end(); )
	{
		if ((*it)->KeyCheck())
		{
			(*it)->OnInActive();
			m_inActiveUIList.push_back(*it);
			it = m_ActiveUIList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (activeUI)
	{
		m_ActiveUIList.push_back(activeUI);
	}
		

}
