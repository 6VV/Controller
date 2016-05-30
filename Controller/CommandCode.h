#ifndef _COMMAND_CODE_H_
#define _COMMAND_CODE_H_

#include <vector>
#include "DataStruct.h"

class CommandCode
{
public:
	static void GetCommand_AskForNormarCommand(char* data);	/*获取申请命令的指令*/

private:
	static void AddData(char* data, tTeachCmdAttribute& attribute);
	static void AddLock(char* data);
	static void AddAttribute(char* data, tTeachCmdAttribute& attribute);

};

#endif