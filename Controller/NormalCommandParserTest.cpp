#include "stdafx.h"
#include "NormalCommandParserTest.h"
#include <iostream>

using namespace std;


NormalCommandParserTest::NormalCommandParserTest(TcpServer* tcpServer, DataManager* dataManager)
{
	m_tcpServer = tcpServer;
	m_dataManager = dataManager;
}

NormalCommandParserTest::~NormalCommandParserTest()
{
}

void NormalCommandParserTest::Execute()
{
	if (m_dataManager->IsHaveNormalCommand())
	{
		char data[COMMAND_MAX_LENGTH];
		m_dataManager->OperateNormalCommand(data, DataManager::POP);

		system("cls");
		ExecuteCommand(data);
		Sleep(1000);
	}
}

void NormalCommandParserTest::ExecuteCommand(char* commandHead)
{
	SendFeedback(commandHead);

	char lock = *commandHead;
	tTeachCmdAttribute* attribute = DataManager::GetAttribute(commandHead);

	DisplayHead(lock, attribute->m_length, *attribute);

	switch (attribute->m_ID)
	{
	case COMMAND_ID::MOVL:
	{
		ExecuteMovl(commandHead);
	}break;
	case COMMAND_ID::MOVC:
	{
		ExecuteMovc(commandHead);
	}break;
	}
}

void NormalCommandParserTest::ExecuteMovl(char* commandHead)
{
	tMovLParam movlPara = *(tMovLParam*)(commandHead+sizeof(tTeachCmdAttribute)+LOCK_LENGTH);

	cout << "MovlPara:" << endl;
	DisplayPosition(movlPara.m_Destination);
	DisplayDynamic(movlPara.m_Dynamic);
	DisplayOverlap(movlPara.m_Overlap);
}

void NormalCommandParserTest::ExecuteMovc(char* commandHead)
{
	tMovCParam movcPara = *(tMovCParam*)(commandHead + sizeof(tTeachCmdAttribute)+LOCK_LENGTH);

	cout << "MovcPara:" << endl;
	DisplayPosition(movcPara.m_AuxPoint);
	DisplayPosition(movcPara.m_EndPoint);
	DisplayDynamic(movcPara.m_Dynamic);
	DisplayOverlap(movcPara.m_Overlap);
}


void NormalCommandParserTest::DisplayHead(const int lock, const int length, const tTeachCmdAttribute& attribute)
{
	cout << "lock:" << lock << endl;
	cout << "attribute:" << endl;
	cout << "\t" << "ID:" << attribute.m_ID << endl;
	cout << "\t" << "LineNumber:" << attribute.m_LineNumber << endl;
}

void NormalCommandParserTest::DisplayPosition(const tAxesAllPositions& position)
{
	cout << "\t" << "Destination:" << endl;
	cout << "\t\t" << "Axis1:" << position.m_AxisPosition[0] << endl;
	cout << "\t\t" << "Axis2:" << position.m_AxisPosition[1] << endl;
	cout << "\t\t" << "Axis3:" << position.m_AxisPosition[2] << endl;
	cout << "\t\t" << "Axis4:" << position.m_AxisPosition[3] << endl;
	cout << "\t\t" << "Axis5:" << position.m_AxisPosition[4] << endl;
	cout << "\t\t" << "Axis6:" << position.m_AxisPosition[5] << endl;
}

void NormalCommandParserTest::DisplayDynamic(const tDynamicConstraint& dynamic)
{
	cout << "\t" << "Dynamic:" << endl;
	cout << "\t\t" << "Velocity:" << dynamic.m_Velocity << endl;
	cout << "\t\t" << "Acceleration:" << dynamic.m_Acceleration << endl;
	cout << "\t\t" << "Deceleration:" << dynamic.m_Deceleration << endl;
	//姿态约束
	cout << "\t\t" << "PostureVelocity:" << dynamic.m_PostureVelocity << endl;
	cout << "\t\t" << "PostureAcceleration:" << dynamic.m_PostureAcceleration << endl;
	cout << "\t\t" << "PostureDeceleration:" << dynamic.m_PostureDeceleration << endl;
}

void NormalCommandParserTest::DisplayOverlap(const tOverlapConstraint& overlap)
{
	cout << "\t" << "overlap:" << endl;
	//过渡模式和参数
	cout << "\t\t" << "TransitionMode:" << overlap.m_TransitionMode << endl;
	cout << "\t\t" << "TransitionParameter:" << overlap.m_TransitionParameter << endl;
}

void NormalCommandParserTest::SendFeedback(char* commandHead)
{
	char command[LOCK_LENGTH+sizeof(tTeachCmdAttribute)];
	memcpy(command, commandHead, COMMAND_HEAD_LENGTH);
	tTeachCmdAttribute* attribute = DataManager::GetAttribute(command);
	attribute->m_ID = NORMAL_COMMAND_FEEDBACK;
	attribute->m_length = COMMAND_HEAD_LENGTH;

	m_tcpServer->SendData(command, sizeof(command));
}
