#pragma once
#include "BridgeIOBase.h"
class BridgeOutputBase :
    public BridgeIOBase
{
	/**
	 * @brief 发送接口
	 * @param data 数据
	*/
	virtual void write(QByteArray data) = 0;
};

