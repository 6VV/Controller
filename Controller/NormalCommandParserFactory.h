#ifndef _ALGORITHM_FACTORY_H_
#define _ALGORITHM_FACTORY_H_

#include "NormalCommandParserAbstract.h"
#include "TcpServer.h"
#include "DataManager.h"

class NormalCommandParserFactory
{
public:
	static NormalCommandParserAbstract* CreateAlgorithm(TcpServer* tcpServer,DataManager* dataManager);
};

#endif