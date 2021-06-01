
#include "HttpClientInputBridge.h"

#include <QFile>

int main()
{
	BridgeInputBase* bridge = new HttpClientInputBridge;
	
	bridge->open(nlohmann::json::parse(R"(
{
    "host":"www.baidu.com",
    "port":80
})"));

	bridge->setConfig(nlohmann::json::parse(R"(
{
    "path":"/s?wd=QT_VA_ARGS_EXPAND",
    "method":"GET"
}
)"));

	auto data = bridge->read();

	QFile file("note.txt");
	file.open(QFile::WriteOnly);
	file.write(data);
	file.close();

}
