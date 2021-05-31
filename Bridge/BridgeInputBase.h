#pragma once
#include "BridgeIOBase.h"
class BridgeInputBase :
    public BridgeIOBase
{
	/**
	 * @brief 读取接口
	 * @return 接口字符串
	*/
	virtual QByteArray read() = 0;
};

