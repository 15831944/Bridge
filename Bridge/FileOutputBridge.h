#pragma once

#include "BridgeOutputBase.h"
class FileOutputBridge final :
	public BridgeOutputBase
{
public:
	/**
	 * @brief 打开接口
	 * @param argPackage 含有filename参数包
	 * @return 是否成功
	*/
	bool open(json argPackage) override;

	/**
	 * @brief 关闭接口
	*/
	void close() override;

	/**
	 * @brief 添加配置信息
	 * @param setting 含有mode<overwrite/skip/block>的参数包
	*/
	void setConfig(json setting) override;

	/**
	 * @brief 写入文件
	 * @param data 待写入数据
	*/
	void write(QByteArray data) override;
protected:
	QString filename;
	enum { OverWrite, Skip, Block }mode{ OverWrite };
};
