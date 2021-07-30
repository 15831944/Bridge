#pragma once
#include <httplib.h>
#include "BridgeInputBase.h"
class HttpClientInputBridge final :
	public BridgeInputBase
{
public:
	/**
	 * @brief 打开接口
	 * @param argPackage 含有host port参数包
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

	/**
	 * @brief 使用path、method、body、content_type设定网站信息
	 * @param setting 含有 path method[POST/GET] body[可选] content_type[可选]
	*/
	void setConfig(json setting) override;

	/**
	 * @brief 获取配置信息
	 * @return 配置信息
	*/
	json config() const override;

protected:
	bool open(QString host, int port);

	// config
	std::unique_ptr<httplib::Client> client;
	std::string path;
	std::string body;
	std::string content_type;
	bool isPostMethod{};
};
