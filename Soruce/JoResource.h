#pragma once

#include "CommonInclude.h"
#include "Entity.h"

class JoResource abstract : public Entity
{
public:
	JoResource(const eResourceType& type);
	virtual ~JoResource();

	virtual HRESULT Load(const wstring& path) = 0;

	const wstring& GetPath() const { return m_sPath; }
	void SetPath(const wstring& path) { m_sPath = path; }

private:
	const eResourceType m_eType;
	wstring m_sPath;
};
