// TestGCSRTNet.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "time.h"
#include "WebsockService.h"


//���տͻ��˵���������Ļص�����
void WINAPI AcceptCallBack(HANDLE handle, char* pszIP, WORD wPort);
//�Ͽ��ͻ������ӵĻص�����s
void WINAPI DissconnectCallBack(HANDLE handle);
//���յ����ݰ�ʱ�Ļص�����
void WINAPI RecvDataCallBack(HANDLE handle, int nLen, char* pData);

//���տͻ��˵���������Ļص�����
void WINAPI AcceptCallBack(HANDLE handle, char *pszIP, WORD wPort)
{
	_tprintf(_T("AcceptCallBack-->handle=%p, pszIP=%s, wPort=%04d \n"), handle, pszIP, wPort);	
	return;
}
//�Ͽ��ͻ������ӵĻص�����
void WINAPI DissconnectCallBack(HANDLE handle)
{	
	//ֱ���˳�,�����������
	_tprintf(_T("DissconnectCallBack-->handle=%p\n"), handle);
	return;
}

//���յ����ݰ�ʱ�Ļص�����
void WINAPI RecvDataCallBack(HANDLE handle, int nLen, char* pData)
{
	TCHAR ip[32];
	WebsockServiceGetPeerIP(handle,ip);

	pData[nLen]=0;
	_tprintf(_T("Recv Socket=%p  ip=%s , nLen=%d, %s , time=%d\n\n"),handle,ip, nLen,pData,time(NULL));

	//���ص��ͻ���
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

