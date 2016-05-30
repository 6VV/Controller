#include "stdafx.h"
#include "TcpException.h"



TcpException::TcpException(const std::string& text)
{
	m_text = text;
}

std::string& TcpException::GetText()
{
	return m_text;
}
