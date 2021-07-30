#include <QTcpSocket>
#include <QTcpServer>
#include <QCoreApplication>
#include "TcpOutputBridgeImpl.h"

bool TcpOutputBridgeImpl::init(json argPackage)
{
	try
	{
		// todo: Insert init bridge code here.
		return true;
	}
	catch (...)
	{
	}
	return false;
}

void TcpOutputBridgeImpl::uninit()
{
	// todo: Insert uninit code here.
}

void TcpOutputBridgeImpl::setConfig(json setting)
{
	// todo: Insert config code here.
}

IBridgeIO::json TcpOutputBridgeImpl::config() const
{
	// todo: Insert get config code here.
	return json();
}

void TcpOutputBridgeImpl::write(QByteArray data)
{
	// todo: Insert write code here.
}