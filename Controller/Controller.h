#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Controller.h
//  Author:			��Ρ      
//  Version: 		1.0     
//  Date: 			2016/05/16
//  Description:	��ʼ�����ݹ�������Tcp���������Լ���Ҫ�߳�
//  Others:
//  History:
//    <author>      ��Ρ 
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