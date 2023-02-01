#include "pch.h"
#include "SamHashPlugin.h"

IMPLEMENT_PLUGIN(SamHashPlugin)

void SamHashPlugin::Init()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// merge menu
	CMenu append;
	append.LoadMenu(IDR_MENU1);
	MergeMenu(&append, TRUE);
}

void SamHashPlugin::Query(CPluginInfo& plugininfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	plugininfo.m_strName = _T("Reg SAM HASH Get");
	plugininfo.m_strBlurb = _T("注册表SAM HASH提取");
	plugininfo.m_strHelp = _T("暂无");
	plugininfo.m_strAuthor = _T("wangzha");
	plugininfo.m_strCopyRight = _T("Copyright wangzha");
	plugininfo.m_strDate = _T("2023.2.1");
	plugininfo.m_strMenuLabel = "插件";
}