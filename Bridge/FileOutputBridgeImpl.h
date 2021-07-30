#pragma once

#include "IBridgeOutput.h"
class FileOutputBridgeImpl final :
	public IBridgeOutput
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
	 * @brief 添加配置信息
	 * @param setting 含有mode<overwrite/skip/block>的参数包
	*/
	void setConfig(json setting) override;

	/**
	 * @brief 获取配置信息
	 * @return 配置信息
	*/
	json config() const override;

	/**
	 * @brief 写入文件
	 * @param data 待写入数据
	*/
	void write(QByteArray data) override;
protected:
	QString filename;

	// config
	enum { OverWrite, Skip, Block }mode{ OverWrite };
};
