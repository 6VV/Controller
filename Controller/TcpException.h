#ifndef _TCP_EXCEPTION_H_
#define _TCP_EXCEPTION_H_

class TcpException
{
public:
	TcpException(const std::string& text);

	std::string& GetText();

private:
	std::string m_text;
};

#endif