#pragma once

#include <QObject>
#include <json.hpp>

class IBridgeIO
	: public QObject
{
public:
	using json = nlohmann::json;

	/**
	 * @brief 打开接口
	 * @param argPackage 打开参数
	 * @return 是否成功
	*/
	virtual bool init(json argPackage) = 0;

	/**
	 * @brief 配置
	 * @param setting 配置信息
	*/
	virtual void setConfig(json setting) {}

	/**
	 * @brief 返回配置信息
	 * @return 配置信息
	*/
	virtual json config()const { return json(); }

	/**
	 * @brief 关闭接口
	*/
	virtual void uninit() = 0;
};
