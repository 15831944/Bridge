#include "HttpClientInputBridgeImpl.h"
#include "FileInputBridgeImpl.h"
#include "FileOutputBridgeImpl.h"

#include <QFile>

int main()
{
	IBridgeInput* inputBridge = new HttpClientInputBridgeImpl;
	IBridgeOutput* outputBridge = new FileOutputBridgeImpl;
	IBridgeOutput* out2 = new FileOutputBridgeImpl;
	IBridgeInput* in2 = new FileInputBridgeImpl;

	inputBridge->init(nlohmann::json::parse(R"(
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

	outputBridge->init(nlohmann::json::parse(R"(
{
	"filename":"output.txt"
})"));

	outputBridge->write(inputBridge->read());

	in2->init(nlohmann::json::parse(R"(
	{
		"filename":"output1.txt"
	})"));

	out2->init(nlohmann::json::parse(R"(
	{
		"filename":"output2.txt"
	})"));

	out2->write(in2->read());
}