#pragma once
#include "UI.h"



class MyDialogBox :
    public UI
{
public:
    MyDialogBox();
    ~MyDialogBox();

    void Initialize()   override;
    void Update()       override;
    void LateUpdate()   override;
    void Render()       override;
    void Release()      override;

    void Set_NpcNameTex(JoTexture* _pNpcNameTex) { m_pNpcNameTex = _pNpcNameTex; }
    void Set_NpcTex(JoTexture* _pNpcTex) { m_pNpcTex = _pNpcTex; }
    void Set_Dialog(vector<pair<wstring, int>>* _pVecDialog) { m_pVecDialog = _pVecDialog; }

    void SetActive(const bool& _b) { m_bActive = _b; }
    const bool& IsActive() const { return m_bActive; }

private:
    JoTexture* m_pPlayerNameTex;
    JoTexture* m_pNpcNameTex;
    JoTexture* m_pPlayerTex;
    JoTexture* m_pNpcTex;

    vector<pair<wstring, int>>* m_pVecDialog;
    wstring         m_wsNowDialog;
    size_t          m_iNowIdx;
    size_t          m_iRenderIdx;

    Vec2            m_vPlayerRenderPos;
    Vec2            m_vPlayerNameRenderPos;
    Vec2            m_vNpcRenderPos;
    Vec2            m_vNpcNameRenderPos;

    float           m_fNowTime;
    float           m_fTextRenderGap;

    bool            m_bActive;
};

