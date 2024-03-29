﻿#include "HttpClientInputBridgeImpl.h"

bool HttpClientInputBridgeImpl::init(json argPackage)
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

void HttpClientInputBridgeImpl::uninit()
{
	client.reset();
}

bool HttpClientInputBridgeImpl::canRead()
{
	return client->is_valid();
}

QByteArray HttpClientInputBridgeImpl::read()
{
	auto res = isPostMethod
		? client->Post(path.c_str(), body, content_type.c_str())
		: client->Get(path.c_str());
	return res ? QByteArray::fromStdString(res.value().body) : QByteArray{};
}

void HttpClientInputBridgeImpl::setConfig(json setting)
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

IBridgeIO::json HttpClientInputBridgeImpl::config() const
{
	json j;
	j["method"] = isPostMethod ? "POST" : "GET";
	j["path"] = path;
	j["body"] = body;
	j["content_type"] = content_type;
	return j;
}

bool HttpClientInputBridgeImpl::open(QString host, int port)
{
	client = std::make_unique<httplib::Client>(host.toStdString(), port);
	return client->is_valid();
}