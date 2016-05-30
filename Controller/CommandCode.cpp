#include "stdafx.h"
#include "CommandCode.h"
#include "DataStruct.h"


void CommandCode::GetCommand_AskForNormarCommand(char* data)
{
	tTeachCmdAttribute attribute;
	attribute.m_ID = COMMAND_ID::NORMAL_COMMAND;
	attribute.m_length = COMMAND_HEAD_LENGTH;
	AddData(data, attribute);
}

void CommandCode::AddData(char* data, tTeachCmdAttribute& attribute)
{
	AddLock(data);
	AddAttribute(data, attribute);
}

void CommandCode::AddLock(char* data)
{
	data[0] = 0;
}

void CommandCode::AddAttribute(char* data, tTeachCmdAttribute& attribute)
{
	*(tTeachCmdAttribute*)(data+LOCK_LENGTH) = attribute;
}
