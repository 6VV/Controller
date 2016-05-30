#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Controller.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/05/16
//  Description:	初始化数据管理器，Tcp管理器，以及主要线程
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/05/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DataManager.h"
#include "ITcp.h"
#include "DataStruct.h"
#include "TcpServer.h"
#include "NormalCommandParserAbstract.h"
#include "SpecialCommandParserAbstract.h"

class Controller:public ITcp
{
public:
	Controller();
	~Controller();

private:
	void ExecuteNormalCommand();
	void ExecuteSpecialCommand();

	tTeachCmdAttribute* GetAttribute(const char* data);

	void Init();
	void InitThread();
	void InitThreadExecuteNormalCommand();
	void InitThreadExecuteSpecialCommand();

	virtual void OnReceiveData(const char* data) override;
	void ParseCommand(const char* command);
	void StartThread();
	void StopThread();
private:
	bool m_isStartThread = false;
	TcpServer* m_tcpServer=nullptr;
	DataManager* m_dataManager=nullptr;
	NormalCommandParserAbstract* m_normalCommandParser=nullptr;
	SpecialCommandParserAbstract* m_specialCommandParser = nullptr;
};

#endif