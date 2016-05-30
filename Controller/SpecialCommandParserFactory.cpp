#include "stdafx.h"
#include "SpecialCommandParserFactory.h"
#include "SpecialCommandParserTest.h"


SpecialCommandParserAbstract* SpecialCommandParserFactory::CreateSpecialCommand(TcpServer* tcpServer, DataManager* dataManager)
{
	return new SpecialCommandParserTest(tcpServer,dataManager);
}
