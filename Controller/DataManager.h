#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <list>
#include <mutex>
#include "TcpServer.h"
#include "DataStruct.h"

class DataManager
{
public:
	enum OPERATOR
	{
		ADD,
		POP,
	};
	static 	tTeachCmdAttribute* GetAttribute(char* commandHead);

	DataManager(TcpServer* tcpServer);
	~DataManager();

	void ClearNormalCommand();
	bool IsHaveNormalCommand();
	bool IsHaveSpecialCommand();
	void OperateNormalCommand(char* data,OPERATOR operate);
	void OperateSpecialCommand(char* data, OPERATOR operate);

private:
	void AddNormalCommand(char* data);
	void AddSpecialCommand(char* data);
	void GetNextCommandThroughTcp();
	void PopNormalCommand(char* data);
	void PopSpecialCommand(char* data);

private:
	static const int COLLECTION_SIZE = 10;

	TcpServer* m_tcpServer = nullptr;

	std::mutex m_mutexNormalCommand;
	std::mutex m_mutexSpecialCommand;
	std::list<char*> m_normalCommands;
	std::list<char*> m_specialCommands;
	bool m_isMeetEof = false;
};

#endif