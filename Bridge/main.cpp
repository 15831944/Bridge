#include "HttpClientInputBridge.h"
#include "FileInputBridge.h"
#include "FileOutputBridge.h"

#include <QFile>

int main()
{
	BridgeInputBase* inputBridge = new HttpClientInputBridge;
	BridgeOutputBase* outputBridge = new FileOutputBridge;
	BridgeOutputBase* out2 = new FileOutputBridge;
	BridgeInputBase* in2 = new FileInputBridge;

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

	in2->open(nlohmann::json::parse(R"(
	{
		"filename":"output1.txt"
	})"));

	out2->open(nlohmann::json::parse(R"(
	{
		"filename":"output2.txt"
	})"));

	out2->write(in2->read());
	
}