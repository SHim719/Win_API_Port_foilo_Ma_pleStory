#pragma once
#include "GameObject.h"

class JoTexture;


enum class Num_State
{
	Normal,
	Physics,
};

class DamageNum :
    public GameObject
{
public:
	DamageNum();
	~DamageNum();

	void Initialize() override;
	void Update() override;
	void Render() override;

	void Init_Number(const string& _sNum);

	void SetCritical(const bool& b) { m_bCritical = b; }
	const bool& IsCritical() const { return m_bCritical; }

	void SetPlayerHit(const bool& b) { m_bPlayerHit = b; }
	const bool& IsPlayerHit() const { return m_bPlayerHit; }

	JoTexture* GetDamageTex() 
	{ 
		if (m_bCritical)
			return m_pCriticalTex;
		else if (!m_bPlayerHit)
			return m_pDamageTex;
		else
			return m_pPlayerDamageTex;
	}

	static void Init_DamageTex();
	static void Select_DamageTex(const size_t _iIdx) { m_iIdx = _iIdx; }
	static void Select_Option(const Num_State& _state) { m_eState = _state; };
private:
	static vector<JoTexture*> m_vecNormalDamageTex;
	static vector<JoTexture*> m_vecCriDamageTex;
	static size_t m_iIdx;
	static Num_State m_eState;



	JoTexture* m_pDamageTex;
	JoTexture* m_pCriticalTex;
	JoTexture* m_pPlayerDamageTex;
	vector<int> m_vecRenderNum;

	bool m_bCritical;
	bool m_bPlayerHit;

	float m_fNowTime;
	float m_fSpeed; 
	float m_fAlpha;
};

