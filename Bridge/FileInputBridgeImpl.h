#pragma once

#include "IBridgeInput.h"
class FileInputBridgeImpl final :
	public IBridgeInput
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
	 * @brief 测试能否读取
	 * @return  是否可读
	*/
	bool canRead() override;

	/**
	 * @brief 从文件读取信息
	 * @return 读取到的数据
	*/
	QByteArray read() override;

protected:
	QString filename;
};
