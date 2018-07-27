#pragma once

#include "resource.h"
#include "MainWnd.h"


void InitResource()
{
#ifdef _DEBUG
	CPaintManagerUI::SetResourceType(UILIB_FILE);
	//CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
#else
	//CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
	CPaintManagerUI::SetResourceType(UILIB_FILE);
#endif

	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();

	switch (CPaintManagerUI::GetResourceType())
	{
	case UILIB_FILE:
	{
		strResourcePath += _T("skin\\");
		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
		break;
	}
	case UILIB_RESOURCE:
	{
		strResourcePath += _T("skin\\");
		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
		CResourceManager::GetInstance()->LoadResource(_T("IDR_RES"), _T("xml"));
		break;
	}
	case UILIB_ZIP:
	{
		strResourcePath += _T("skin\\");
		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
		CPaintManagerUI::SetResourceZip(_T("skin.zip"), true);
		break;
	}
	case UILIB_ZIPRESOURCE:
	{
		/*	strResourcePath += _T("skin\\");
		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
		*/
		HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), _T("IDR_ZIPRES"), _T("ZIPRES"));

		if (hResource != NULL)
		{
			DWORD dwSize = 0;
			HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
			if (hGlobal != NULL)
			{
				dwSize = ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
				if (dwSize > 0)
				{
					CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);
				}
			}
			::FreeResource(hResource);
		}

		break;
	}
	}
}

int ShowMainWnd(HINSTANCE hInstance)
{
	//MessageBox(NULL, _T("ʹ��ʱ�������ļ�(*.xml)�ϵ�DuilibPreview.exe�ϼ���Ԥ����\r\n��\"Esc\"����\"Alt+F4\"�˳���\r\n\r\n����readme�ò����� ^_*"), _T("����Ԥ������"), MB_OK);
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	// ��ʼ��UI������
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	// ��ʼ����Դ
	InitResource();

	CMainWnd* pFrame = new CMainWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("Duilib Preview"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 600, 700);
	pFrame->CenterWindow();
	pFrame->ShowModal();

	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}