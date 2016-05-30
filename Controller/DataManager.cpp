#include "stdafx.h"
#include "DataManager.h"
#include <memory.h>
#include "DataStruct.h"
#include <mutex>
#include "CommandCode.h"


tTeachCmdAttribute* DataManager::GetAttribute(char* commandHead)
{
	return (tTeachCmdAttribute*)(commandHead + LOCK_LENGTH);
}

DataManager::DataManager(TcpServer* tcpServer)
{
	m_tcpServer = tcpServer;
}

DataManager::~DataManager()
{
	for (auto data:m_normalCommands)
	{
		delete[]data;
	}
	for (auto data:m_specialCommands)
	{
		delete[]data;
	}
}

void DataManager::ClearNormalCommand()
{
	std::lock_guard<std::mutex> lockGuard(m_mutexNormalCommand);

	m_normalCommands.clear();
}

bool DataManager::IsHaveNormalCommand()
{
	std::lock_guard<std::mutex> lockGuard(m_mutexNormalCommand);

	return m_normalCommands.size() > 0;
}

bool DataManager::IsHaveSpecialCommand()
{
	std::lock_guard<std::mutex> lockGuard(m_mutexSpecialCommand);

	return m_specialCommands.size() > 0;
}

void DataManager::OperateNormalCommand(char* data, OPERATOR operate)
{
	std::lock_guard<std::mutex> lockGuard(m_mutexNormalCommand);

	switch (operate)
	{
	case DataManager::ADD:
	{
		AddNormalCommand(data);
	}
	break;
	case DataManager::POP:
	{
		PopNormalCommand(data);
	}
	break;
	default:
		break;
	}

	GetNextCommandThroughTcp();
}

void DataManager::GetNextCommandThroughTcp()
{
	if (!m_isMeetEof && m_normalCommands.size() < COLLECTION_SIZE)
	{
		char data[COMMAND_MAX_LENGTH];
		CommandCode::GetCommand_AskForNormarCommand(data);
		m_tcpServer->SendData(data, COMMAND_MAX_LENGTH);
	}
}

void DataManager::PopNormalCommand(char* data)
{
	char* cmd = m_normalCommands.front();
	memcpy(data, cmd, COMMAND_MAX_LENGTH);
	m_normalCommands.pop_front();
	delete[]cmd;
}

void DataManager::AddNormalCommand(char* data)
{
	char* cmd = new char[COMMAND_MAX_LENGTH];
	memcpy(cmd, data, COMMAND_MAX_LENGTH);
	m_normalCommands.push_back(cmd);
	if (GetAttribute(data)->m_ID == STOP_EXECUTE)
	{
		m_isMeetEof = true;
	}
}

void DataManager::OperateSpecialCommand(char* data, OPERATOR operate)
{
	std::lock_guard<std::mutex> lockGuard(m_mutexSpecialCommand);

	switch (operate)
	{
	case DataManager::ADD:
	{
		AddSpecialCommand(data);
	}
	break;
	case DataManager::POP:
	{
		PopSpecialCommand(data);
	}
	break;
	default:
		break;
	}
}

void DataManager::PopSpecialCommand(char* data)
{
	char* cmd = m_specialCommands.front();
	memcpy(data, cmd, COMMAND_MAX_LENGTH);
	m_specialCommands.pop_front();
	delete[]cmd;
}

void DataManager::AddSpecialCommand(char* data)
{
	char* cmd = new char[COMMAND_MAX_LENGTH];
	memcpy(cmd, data, COMMAND_MAX_LENGTH);
	m_specialCommands.push_back(cmd);
}

