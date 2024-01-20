#pragma once

#include "CommonInclude.h"


class Entity
{
public:
	Entity();
	virtual ~Entity();

	wstring& GetName() { return m_sName; }
	void SetName(const wstring& _name) { m_sName = _name; }

private:
	wstring m_sName;
};

