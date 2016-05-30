#include "stdafx.h"
#include "TcpServer.h"
#include <stdio.h>
#include <thread>
#include <vector>
#include <exception>
#include "TcpException.h"
#include "DataStruct.h"


TcpServer::TcpServer()
{
	Init();
}

TcpServer::~TcpServer()
{
	m_isListenConnection = false;
	m_isConnect = false;
	WSACleanup();
}

void TcpServer::AddListenerReceiveData(ITcp* iTcp)
{
	m_tcpListener.push_back(iTcp);
}

void TcpServer::SendData(const char* data, const int length)
{
	send(m_socket, data, length, 0);
}

void TcpServer::StopListenConnection()
{
	m_isListenConnection = false;
}

void TcpServer::Init()
{
	try
	{
		InitWinSocket();
		CreateServerSocket();
		Bind(GetServerAddr());
		StartListenConnection();
	}
	catch (TcpException& e)
	{
		printf(e.GetText().data());
	}
}

void TcpServer::ListenConnection()
{
	int len = sizeof(sockaddr);
	sockaddr_in serverAddrFrom;
	while (m_isListenConnection)
	{
		listen(m_serverSocket, 0);
		m_socket = accept(m_serverSocket, (sockaddr*)&serverAddrFrom, &len);
		if (m_socket != INVALID_SOCKET)
		{
			m_isConnect = true;
			std::thread thrd(&TcpServer::ThreadReceiveData, this);
			thrd.detach();
			break;
		}
	}
}

void TcpServer::StartListenConnection()
{
	m_isListenConnection = true;
	std::thread thrd(&TcpServer::ListenConnection, this);
	thrd.detach();
}

void TcpServer::Bind(sockaddr_in serverAddr)
{
	if (bind(m_serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		//绑定失败
		throw TcpException("Bind failed");
	}
}

void TcpServer::CreateServerSocket()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_serverSocket == INVALID_SOCKET)
	{
		//创建Socket异常
		throw TcpException("Create server socket failed");
	}
}

void TcpServer::InitWinSocket()
{
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		//初始化WinSock失败
		throw TcpException("WSAStartup failed");
	}
}

void TcpServer::ThreadReceiveData()
{
	char bufferReceive[COMMAND_MAX_LENGTH];

	if (m_socket != INVALID_SOCKET)
	{
		printf("start receive\n");
		while (m_isConnect)
		{
			int num = recv(m_socket, bufferReceive, COMMAND_MAX_LENGTH, 0);
			if (num >= 0)
			{
				for (auto iTcp:m_tcpListener)
				{
					iTcp->OnReceiveData(bufferReceive);
				}
			}
		}
	}
}

sockaddr_in TcpServer::GetServerAddr()
{
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

#pragma warning(disable:4996)
	char ip[256];
	GetLocalIp(ip);
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ip);
#pragma warning(default:4996)

	return serverAddr;
}

void TcpServer::GetLocalIp(char * ip)
{
#pragma warning(disable:4996)
	char hostname[256];
	gethostname(hostname, sizeof(hostname));
	HOSTENT* host = gethostbyname(hostname);
	strcpy_s(ip,256, inet_ntoa(*(in_addr*)*host->h_addr_list));
#pragma warning(default:4996)
}
