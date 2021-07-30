#include "HttpClientInputBridge.h"

bool HttpClientInputBridge::init(json argPackage)
{
	try
	{
		return open(QString::fromStdString(argPackage["host"]), argPackage["port"]);
	}
	catch (...)
	{
	}
	return false;
}

void HttpClientInputBridge::uninit()
{
	client.reset();
}

QByteArray HttpClientInputBridge::read()
{
	auto res = isPostMethod
		? client->Post(path.c_str(), body, content_type.c_str())
		: client->Get(path.c_str());
	return res ? QByteArray::fromStdString(res.value().body) : QByteArray{};
}

void HttpClientInputBridge::setConfig(json setting)
{
	try
	{
		isPostMethod = setting["method"] == "POST";
		path = setting["path"];
		if (setting.contains("body"))
			body = setting["body"];
		if (setting.contains("content_type"))
			content_type = setting["content_type"];
	}
	catch (...)
	{
	}
}

BridgeIOBase::json HttpClientInputBridge::config() const
{
	json j;
	j["method"] = isPostMethod ? "POST" : "GET";
	j["path"] = path;
	j["body"] = body;
	j["content_type"] = content_type;
	return j;
}

bool HttpClientInputBridge::open(QString host, int port)
{
	client = std::make_unique<httplib::Client>(host.toStdString(), port);
	return client->is_valid();
}