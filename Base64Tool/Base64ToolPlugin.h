#pragma once
#include "stdafx.h"
class Base64ToolPlugin :
	public CPlugin
{
	DECLARE_PLUGIN(Base64ToolPlugin)

private:
	Base64ToolPlugin() {}

public:
	virtual void Init();

	virtual void Query(CPluginInfo& plugininfo);
};

