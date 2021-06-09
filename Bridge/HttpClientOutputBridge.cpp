#include "HttpClientOutputBridge.h"


#define NLOHMANN_EXCEPTION_CATCHED_FLAG _nlohmann_catched_flag
#define NLOHMANN_EXCEPTION_CATCHED static_cast<const bool>(NLOHMANN_EXCEPTION_CATCHED_FLAG)
#define NLOHMANN_TRY \
{\
	bool NLOHMANN_EXCEPTION_CATCHED_FLAG{ false };\
	try\
	{
#define NLOHMANN_CATCH \
	}\
	catch (nlohmann::detail::type_error)\
	{\
		NLOHMANN_EXCEPTION_CATCHED_FLAG = true;\
	}\
	catch (nlohmann::detail::out_of_range)\
	{\
		NLOHMANN_EXCEPTION_CATCHED_FLAG = true;\
	}\
	catch (nlohmann::detail::parse_error)\
	{\
		NLOHMANN_EXCEPTION_CATCHED_FLAG = true;\
	}\
	catch (nlohmann::detail::invalid_iterator)\
	{\
		NLOHMANN_EXCEPTION_CATCHED_FLAG = true;\
	}\
	catch (nlohmann::detail::other_error)\
	{\
		NLOHMANN_EXCEPTION_CATCHED_FLAG = true;\
	}
#define NLOHMANN_CATCH_END \
}

#undef NLOHMANN_EXCEPTION_CATCHED_FLAG


bool HttpClientOutputBridge::open(json argPackage)
{
	NLOHMANN_TRY
		return open(QString::fromStdString(argPackage["host"]), argPackage["port"]);
	NLOHMANN_CATCH
		if (NLOHMANN_EXCEPTION_CATCHED)
		{
			return false;
		}
	NLOHMANN_CATCH_END
		return false;
}

void HttpClientOutputBridge::close()
{
	client.reset();
}

void HttpClientOutputBridge::write(QByteArray data)
{
	if (isPostMethod)
		client->Post(path.c_str(), body, content_type.c_str());
	else
		client->Get(path.c_str());
}

void HttpClientOutputBridge::setConfig(json setting)
{
	NLOHMANN_TRY
		isPostMethod = setting["method"] == "POST";
	path = setting["path"];
	if (setting.contains("body"))
		body = setting["body"];
	if (setting.contains("content_type"))
		content_type = setting["content_type"];
	NLOHMANN_CATCH
		NLOHMANN_CATCH_END
}

BridgeIOBase::json HttpClientOutputBridge::config() const
{
	json j;
	j["method"] = isPostMethod ? "POST" : "GET";
	j["path"] = path;
	j["body"] = body;
	j["content_type"] = content_type;
	return j;
}

bool HttpClientOutputBridge::open(QString host, int port)
{
	client = std::make_unique<httplib::Client>(host.toStdString(), port);
	return client->is_valid();
}


#undef NLOHMANN_EXCEPTION_CATCHED
#undef NLOHMANN_TRY
#undef NLOHMANN_CATCH
#undef NLOHMANN_CATCH_END