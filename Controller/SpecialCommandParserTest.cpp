#include "stdafx.h"
#include "SpecialCommandParserTest.h"
#include "DataStruct.h"
#include <windows.h>
#include "DataManager.h"
#include <iostream>


SpecialCommandParserTest::SpecialCommandParserTest(TcpServer* tcpServer, DataManager* dataManager)
{
	m_tcpServer = tcpServer;
	m_dataManager = dataManager;
}

void SpecialCommandParserTest::Execute()
{
	if (m_dataManager->IsHaveSpecialCommand())
	{
		char data[COMMAND_MAX_LENGTH];
		m_dataManager->OperateSpecialCommand(data, DataManager::POP);
		Execute(data);
	}
}

void SpecialCommandParserTest::Execute(char* command)
{
	system("cls");

	switch (GetAttribute(command)->m_ID)
	{
	case COMMAND_ID::STOP_EXECUTE:
	{
		ExecuteStopInterprete();
	}break;
	case COMMAND_ID::ROBOT_POSITION:
	{
		ExecuteRobotPosition(command);
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_1:
	{
		ExecutePlusAxis1();
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_2:
	{
		ExecutePlusAxis2();
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_3:
	{
		ExecutePlusAxis3();
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_4:
	{
		ExecutePlusAxis4();
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_5:
	{
		ExecutePlusAxis5();
	}break;
	case COMMAND_ID::MOVE_AXIS_PLUS_6:
	{
		ExecutePlusAxis6();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_1:
	{
		ExecuteMinusAxis1();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_2:
	{
		ExecuteMinusAxis2();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_3:
	{
		ExecuteMinusAxis3();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_4:
	{
		ExecuteMinusAxis4();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_5:
	{
		ExecuteMinusAxis5();
	}break;
	case COMMAND_ID::MOVE_AXIS_MINUS_6:
	{
		ExecuteMinusAxis6();
	}break;
	case COMMAND_ID::STOP_MOVE:
	{
		ExecuteStopMove();
	}break;
	default:
		break;
	}
}

tTeachCmdAttribute* SpecialCommandParserTest::GetAttribute(char* head)
{
	return (tTeachCmdAttribute*)(head + LOCK_LENGTH);
}

void SpecialCommandParserTest::ExecuteStopInterprete()
{
	m_dataManager->ClearNormalCommand();
	std::cout << "Stop" << std::endl;
}

void SpecialCommandParserTest::ExecuteRobotPosition(char* command)
{
	tAxesAllPositions position;
	position.m_AxisPosition[0] = 3;
	position.m_AxisPosition[1] = 4;
	position.m_AxisPosition[2] = 5;
	position.m_AxisPosition[3] = 6;
	position.m_AxisPosition[4] = 7;
	position.m_AxisPosition[5] = 8;

	*(tAxesAllPositions*)(command + COMMAND_HEAD_LENGTH) = position;
	int length = sizeof(tAxesAllPositions) + COMMAND_HEAD_LENGTH;
	((tTeachCmdAttribute*)(command + LOCK_LENGTH))->m_length = length;
	m_tcpServer->SendData(command, length);
	std::cout << "position" << std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis1()
{
	std::cout << "plus axis1"<<std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis2()
{
	std::cout << "plus axis2" << std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis3()
{
	std::cout << "plus axis3" << std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis4()
{
	std::cout << "plus axis4" << std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis5()
{
	std::cout << "plus axis5" << std::endl;
}

void SpecialCommandParserTest::ExecutePlusAxis6()
{
	std::cout << "plus axis6" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis1()
{
	std::cout << "minus axis1" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis2()
{
	std::cout << "minus axis2" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis3()
{
	std::cout << "minus axis3" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis4()
{
	std::cout << "minus axis4" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis5()
{
	std::cout << "minus axis5" << std::endl;
}

void SpecialCommandParserTest::ExecuteMinusAxis6()
{
	std::cout << "minus axis6" << std::endl;
}

void SpecialCommandParserTest::ExecuteStopMove()
{
	std::cout << "stop move" << std::endl;
}

