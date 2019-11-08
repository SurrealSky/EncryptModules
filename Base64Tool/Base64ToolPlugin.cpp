#include "stdafx.h"
#include "Base64ToolPlugin.h"


IMPLEMENT_PLUGIN(Base64ToolPlugin)

void Base64ToolPlugin::Init()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// merge menu
	CMenu append;
	append.LoadMenu(IDR_MENU1);
	MergeMenu(&append, TRUE);
}

void Base64ToolPlugin::Query(CPluginInfo& plugininfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	plugininfo.m_strName = _T("Base64 Encode/Decode");
	plugininfo.m_strBlurb = _T("Base64编解码工具");
	plugininfo.m_strHelp = _T("暂无");
	plugininfo.m_strAuthor = _T("wangzha");
	plugininfo.m_strCopyRight = _T("Copyright wangzha");
	plugininfo.m_strDate = _T("2019.9.02");
	plugininfo.m_strMenuLabel = "插件";
}

