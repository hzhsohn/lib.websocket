// TestGCSRTNet.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "time.h"
#include "WebsockService.h"


//接收客户端的连接请求的回调函数
void WINAPI AcceptCallBack(HANDLE handle, char* pszIP, WORD wPort);
//断开客户端连接的回调函数s
void WINAPI DissconnectCallBack(HANDLE handle);
//接收到数据包时的回调函数
void WINAPI RecvDataCallBack(HANDLE handle, int nLen, char* pData);

//接收客户端的连接请求的回调函数
void WINAPI AcceptCallBack(HANDLE handle, char *pszIP, WORD wPort)
{
	_tprintf(_T("AcceptCallBack-->handle=%p, pszIP=%s, wPort=%04d \n"), handle, pszIP, wPort);	
	return;
}
//断开客户端连接的回调函数
void WINAPI DissconnectCallBack(HANDLE handle)
{	
	//直接退出,或放入重链表
	_tprintf(_T("DissconnectCallBack-->handle=%p\n"), handle);
	return;
}

//接收到数据包时的回调函数
void WINAPI RecvDataCallBack(HANDLE handle, int nLen, char* pData)
{
	TCHAR ip[32];
	WebsockServiceGetPeerIP(handle,ip);

	pData[nLen]=0;
	_tprintf(_T("Recv Socket=%p  ip=%s , nLen=%d, %s , time=%d\n\n"),handle,ip, nLen,pData,time(NULL));

	//返回到客户端
	WebsockServiceSend(handle, "abn");
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("The application is server.\n"));
	if(!WebsockServiceInit(AcceptCallBack,RecvDataCallBack,DissconnectCallBack, 1000))
	{
		_tprintf(_T("WebsockNetInit failed as server.\n"));
		getchar();
		return 0;
	}

	int nExitCode;
	while(true)
	{
		scanf( "%d", &nExitCode);
		if(nExitCode == 0)
		{
			break;
		}
	}

	WebsockServiceDestory();

	return 0;
}

