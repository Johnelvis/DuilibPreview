#include "stdafx.h"
#include "App.h"
#include "PreviewWnd.h"
#include "StringTools.h"

#include <iostream>

//����̨
//#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")

//������ڼ�Duilib��ʼ������ 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{ 
	ShowMainWnd(hInstance);
	
	//CMainWnd mainPtr;
	//mainPtr.previewXmlLayout(lpCmdLine);
    
	return 0; 
} 