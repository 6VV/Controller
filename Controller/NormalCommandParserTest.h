#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include "NormalCommandParserAbstract.h"
#include "DataStruct.h"
#include "TcpServer.h"
#include "DataManager.h"

class NormalCommandParserTest:public NormalCommandParserAbstract
{
public:
	NormalCommandParserTest(TcpServer* tcpServer,DataManager* dataManager);
	~NormalCommandParserTest();

	virtual void Execute() override;

private:
	void ExecuteMovl(char* commandHead);
	void ExecuteMovc(char* commandHead);

private:
	void DisplayHead(const int lock, const int length, const tTeachCmdAttribute& attribute);
	void DisplayPosition(const tAxesAllPositions& position);
	void DisplayDynamic(const tDynamicConstraint& dynamic);
	void DisplayOverlap(const tOverlapConstraint& overlap);
	void ExecuteCommand(char* commandHead);

	void SendFeedback(char* commandHead);
	void SetCommandFeedbackAttribute(char* commandHead);

private:
	TcpServer* m_tcpServer;
	DataManager* m_dataManager;
};

#endif