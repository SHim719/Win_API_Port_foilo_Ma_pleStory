#pragma once
#include "GameObject.h"

class JoTexture;

class DamageNum :
    public GameObject
{
public:
public:
	DamageNum();
	~DamageNum();

	void Initialize() override;
	void Update() override;
	void Render() override;

	void Init_Number(const string& _sNum);

	void SetCritical(const bool& b) { m_bCritical = b; }
	const bool& IsCritical() const { return m_bCritical; }

	JoTexture* GetDamageTex() 
	{ 
		if (m_bCritical)
			return m_pCriticalTex;
		else
			return m_pDamageTex;
	}


private:
	JoTexture* m_pDamageTex;
	JoTexture* m_pCriticalTex;
	vector<int> m_vecRenderNum;
	bool m_bCritical;

	float m_fNowTime;
	float m_fSpeed; 
	float m_fAlpha;
};

