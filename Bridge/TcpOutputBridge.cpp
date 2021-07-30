#include <QTcpSocket>
#include <QTcpServer>
#include <QCoreApplication>
#include "TcpOutputBridge.h"

bool TcpOutputBridge::init(json argPackage)
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

void TcpOutputBridge::uninit()
{
	// todo: Insert uninit code here.
}

void TcpOutputBridge::setConfig(json setting)
{
	// todo: Insert config code here.
}

BridgeIOBase::json TcpOutputBridge::config() const
{
	// todo: Insert get config code here.
}

void TcpOutputBridge::write(QByteArray data)
{
	// todo: Insert write code here.
}
