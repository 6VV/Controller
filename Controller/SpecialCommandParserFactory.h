#ifndef _SPECIAL_COMMAND_FACTORY_H_
#define _SPECIAL_COMMAND_FACTORY_H_

#include "SpecialCommandParserAbstract.h"
#include "TcpServer.h"
#include "DataManager.h"

class SpecialCommandParserFactory
{
public:
	static SpecialCommandParserAbstract* CreateSpecialCommand(TcpServer* tcpServer,DataManager* dataManager);
};

#endif