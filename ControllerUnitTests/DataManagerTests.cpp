#include "stdafx.h"
#include "CppUnitTest.h"
#include "DataManager.h"
#include "DataStruct.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControllerUnitTests
{
	TEST_CLASS(DataManagerTests)
	{
	private:
		DataManager* m_dataManager;
		TcpServer* m_tcpServer;

	private:
		TEST_METHOD_INITIALIZE(Init)
		{
			m_tcpServer = new TcpServer;
			m_dataManager = new DataManager(m_tcpServer);
		}
		TEST_METHOD_CLEANUP(CleanUp)
		{
			delete m_dataManager;
			delete m_tcpServer;
		}

	public:
		TEST_METHOD(OperateNormalCommand_AddPop_AreEqual)
		{
			char src[COMMAND_MAX_LENGTH] = { 1, 2, 3, 4, 5 };
			m_dataManager->OperateNormalCommand(src, DataManager::ADD);
			char des[ COMMAND_MAX_LENGTH];
			m_dataManager->OperateNormalCommand(des, DataManager::POP);
			Assert::AreEqual(src, des);
		}
		
		TEST_METHOD(OperateSpecialCommand_AddPop_AreEqual)
		{
			char src[COMMAND_MAX_LENGTH] = { 1, 2, 3, 4, 5 };
			m_dataManager->OperateSpecialCommand(src, DataManager::ADD);
			char des[COMMAND_MAX_LENGTH];
			m_dataManager->OperateSpecialCommand(des, DataManager::POP);
			Assert::AreEqual(src, des);
		}

		TEST_METHOD(IsHaveNormalCommand_AddCommand_ReturnTrue)
		{
			char src[COMMAND_MAX_LENGTH] = { 1, 2, 3, 4, 5 };
			m_dataManager->OperateNormalCommand(src, DataManager::ADD);
			Assert::IsTrue(m_dataManager->IsHaveNormalCommand());
		}

		TEST_METHOD(IsHaveNormalCommand_HaveNoCommand_ReturnFalse)
		{
			Assert::IsFalse(m_dataManager->IsHaveNormalCommand());
		}

		TEST_METHOD(IsHaveSpecialCommand_AddCommand_ReturnTrue)
		{
			char src[COMMAND_MAX_LENGTH] = { 1, 2, 3, 4, 5 };
			m_dataManager->OperateSpecialCommand(src, DataManager::ADD);
			Assert::IsTrue(m_dataManager->IsHaveSpecialCommand());
		}

		TEST_METHOD(IsHaveSpecialCommand_HaveNoCommand_ReturnFalse)
		{
			Assert::IsFalse(m_dataManager->IsHaveSpecialCommand());
		}

		TEST_METHOD(ClearNormalCommand_Clear_IsEmpty)
		{
			char src[COMMAND_MAX_LENGTH] = { 1, 2, 3, 4, 5 };
			m_dataManager->OperateSpecialCommand(src, DataManager::ADD);
			m_dataManager->ClearNormalCommand();
			Assert::IsFalse(m_dataManager->IsHaveNormalCommand());
		}
	};
}