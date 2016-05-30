#include "stdafx.h"
#include "Controller.h"
#include <thread>
#include "NormalCommandParserFactory.h"
#include "SpecialCommandParserFactory.h"



Controller::Controller()
{
	Init();
}

Controller::~Controller()
{
	StopThread();

	delete m_normalCommandParser;
	m_normalCommandParser = nullptr;

	delete m_specialCommandParser;
	m_specialCommandParser = nullptr;

	delete m_dataManager;
	m_dataManager = nullptr;

	delete m_tcpServer;
	m_tcpServer = nullptr;
}

void Controller::Init()
{
	m_tcpServer = new TcpServer;
	m_tcpServer->AddListenerReceiveData(this);
	m_dataManager = new DataManager(m_tcpServer);

	m_normalCommandParser = NormalCommandParserFactory::CreateAlgorithm(m_tcpServer,m_dataManager);
	m_specialCommandParser = SpecialCommandParserFactory::CreateSpecialCommand(m_tcpServer, m_dataManager);
	InitThread();
}

void Controller::InitThread()
{
	StartThread();
	InitThreadExecuteNormalCommand();
	InitThreadExecuteSpecialCommand();
}

void Controller::InitThreadExecuteNormalCommand()
{
	std::thread thread(&Controller::ExecuteNormalCommand, this);
	thread.detach();
}

void Controller::InitThreadExecuteSpecialCommand()
{
	std::thread thread(&Controller::ExecuteSpecialCommand, this);
	thread.detach();
}

void Controller::ExecuteNormalCommand()
{
	while (m_isStartThread)
	{
		if (m_normalCommandParser)
		{
			m_normalCommandParser->Execute();
		}
		Sleep(5);
	}
}

void Controller::ExecuteSpecialCommand()
{
	while (m_isStartThread)
	{
		if (m_specialCommandParser)
		{
			m_specialCommandParser->Execute();
		}
		Sleep(5);
	}
}

tTeachCmdAttribute* Controller::GetAttribute(const char* data)
{
	return (tTeachCmdAttribute*)(data + LOCK_LENGTH);
}

void Controller::OnReceiveData(const char* data)
{
	ParseCommand(data);
}

void Controller::ParseCommand(const char* command)
{
		switch (GetAttribute(command)->m_type)
		{
		case CMD_ATTRIBUTE_NORMAL_COMMAND:
		{
			m_dataManager->OperateNormalCommand(const_cast<char*>(command), DataManager::ADD);
		}break;
		case CMD_ATTRIBUTE_SPECIAL_COMMAND:
		{
			m_dataManager->OperateSpecialCommand(const_cast<char*>(command), DataManager::ADD);
		}break;
		default:
			break;
		}
}

void Controller::StartThread()
{
	m_isStartThread = true;
}

void Controller::StopThread()
{
	m_isStartThread = false;
}
