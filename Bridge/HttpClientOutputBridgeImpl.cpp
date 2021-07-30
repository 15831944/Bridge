#include "HttpClientOutputBridgeImpl.h"

bool HttpClientOutputBridgeImpl::init(json argPackage)
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

void HttpClientOutputBridgeImpl::uninit()
{
	client.reset();
}

void HttpClientOutputBridgeImpl::write(QByteArray data)
{
	if (isPostMethod)
		client->Post(path.c_str(), body, content_type.c_str());
	else
		client->Get(path.c_str());
}

void HttpClientOutputBridgeImpl::setConfig(json setting)
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

IBridgeIO::json HttpClientOutputBridgeImpl::config() const
{
	json j;
	j["method"] = isPostMethod ? "POST" : "GET";
	j["path"] = path;
	j["body"] = body;
	j["content_type"] = content_type;
	return j;
}

bool HttpClientOutputBridgeImpl::open(QString host, int port)
{
	client = std::make_unique<httplib::Client>(host.toStdString(), port);
	return client->is_valid();
}