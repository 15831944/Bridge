#include "HttpClientInputBridge.h"
#include "FileInputBridge.h"
#include "FileOutputBridge.h"

#include <QFile>

int main()
{
	BridgeInputBase* inputBridge = new HttpClientInputBridge;
	BridgeOutputBase* outputBridge = new FileOutputBridge;

	inputBridge->open(nlohmann::json::parse(R"(
{
    "host":"www.baidu.com",
    "port":80,
	"filename":"demo.txt"
})"));

	inputBridge->setConfig(nlohmann::json::parse(R"(
{
    "path":"/s?wd=QT_VA_ARGS_EXPAND",
    "method":"GET"
}
)"));

	outputBridge->open(nlohmann::json::parse(R"(
{
	"filename":"output.txt"
})"));

	outputBridge->write(inputBridge->read());
}