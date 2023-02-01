#pragma once
#include "D:\work\program\EncryptModules\CommonLib\include\CipherManager\PluginClass.h"
class SamHashPlugin :
    public CPlugin
{
	DECLARE_PLUGIN(SamHashPlugin)

private:
	SamHashPlugin() {}

public:
	virtual void Init();

	virtual void Query(CPluginInfo& plugininfo);
};

