#pragma once
#include "IBridgeIO.h"
class IBridgeOutput :
	public IBridgeIO
{
public:
	/**
	 * @brief 发送接口
	 * @param data 数据
	*/
	virtual void write(QByteArray data) = 0;
};
