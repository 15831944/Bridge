#pragma once
#include "IBridgeIO.h"
class IBridgeInput :
	public IBridgeIO
{
public:

	/**
	 * @brief 测试接口有无内容
	 * @return 是否有内容可读
	*/
	virtual bool canRead() = 0;

	/**
	 * @brief 读取接口，堵塞
	 * @return 接口字符串
	*/
	virtual QByteArray read() = 0;
};
