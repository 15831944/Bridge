#pragma once

#include "BridgeInputBase.h"
class FileInputBridge final :
	public BridgeInputBase
{
public:
	/**
	 * @brief 打开接口
	 * @param argPackage 含有filename参数包
	 * @return 是否成功
	*/
	bool init(json argPackage) override;

	/**
	 * @brief 关闭接口
	*/
	void uninit() override;

	/**
	 * @brief 从服务器地址读取信息
	 * @return 读取到的数据
	*/
	QByteArray read() override;

protected:
	QString filename;
};
