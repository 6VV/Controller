#ifndef _CONTROLLER_TCPSERVER_H_
#define _CONTROLLER_TCPSERVER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TcpServer.h
//  Author:			��Ρ      
//  Version: 		1.0     
//  Date: 			2016/05/09
//  Description:	ͨ��TcpЭ����п�������ʾ����֮���ͨ��
//  Others:			�����windowsϵͳ����Ҫ����ϵͳ����Դ�������ع�
//  History:
//    <author>      ��Ρ 
//    <time>        2016/05/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/


#include "ITcp.h"
#include <list>
#include <winsock.h>

class TcpServer
{
public:
	TcpServer();
	~TcpServer();

	void AddListenerReceiveData(ITcp* iTcp);
	void SendData(const char* data, const int length);
	void StopListenConnection();

private:
	void Bind(sockaddr_in serverAddr);
	void CreateServerSocket();
	sockaddr_in GetServerAddr();

	void GetLocalIp(char * ip);

	void Init();
	void InitWinSocket();
	void ListenConnection();
	void StartListenConnection();
	void ThreadReceiveData();
	
private:
	static const int PORT = 1234;
	bool m_isConnect=false;
	bool m_isListenConnection = false;
	SOCKET m_serverSocket;
	SOCKET m_socket;
	std::list<ITcp*> m_tcpListener;
};

#endif

