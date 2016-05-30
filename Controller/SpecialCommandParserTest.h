#ifndef _SPECIAL_COMMAND_TEST_H_
#define _SPECIAL_COMMAND_TEST_H_

#include "SpecialCommandParserAbstract.h"
#include "DataStruct.h"
#include "TcpServer.h"
#include "DataManager.h"

class SpecialCommandParserTest:public SpecialCommandParserAbstract
{
public:
	SpecialCommandParserTest(TcpServer* tcpServer, DataManager* dataManager);
	virtual void Execute() override;

private:
	tTeachCmdAttribute* GetAttribute(char* head);
	void Execute(char* command);
	void ExecuteStopInterprete();
	void ExecuteRobotPosition(char* command);
	void ExecutePlusAxis1();
	void ExecutePlusAxis2();
	void ExecutePlusAxis3();
	void ExecutePlusAxis4();
	void ExecutePlusAxis5();
	void ExecutePlusAxis6();
	void ExecuteMinusAxis1();
	void ExecuteMinusAxis2();
	void ExecuteMinusAxis3();
	void ExecuteMinusAxis4();
	void ExecuteMinusAxis5();
	void ExecuteMinusAxis6();
	void ExecuteStopMove();

private:
	TcpServer* m_tcpServer=nullptr;
	DataManager* m_dataManager=nullptr;
};

#endif