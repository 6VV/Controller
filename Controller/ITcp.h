#ifndef _I_TCP_H_
#define _I_TCP_H_

class ITcp
{
public:
	virtual void OnReceiveData(const char* data)=0;
};

#endif