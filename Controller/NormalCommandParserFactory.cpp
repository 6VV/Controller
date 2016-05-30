#include "stdafx.h"
#include "NormalCommandParserFactory.h"
#include "NormalCommandParserTest.h"


NormalCommandParserAbstract* NormalCommandParserFactory::CreateAlgorithm(TcpServer* tcpServer,
	DataManager* dataManager)
{
	return new NormalCommandParserTest(tcpServer,dataManager);
}
